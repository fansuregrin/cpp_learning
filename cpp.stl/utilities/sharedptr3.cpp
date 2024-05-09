#include <memory>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>  // strerror
#include <cerrno>   // errno
#include <string>
#include <iostream>


class SharedMemoryDetacher {
public:
    void operator()(int *ptr) {
        std::cout << "unlink /tmp1234" << std::endl;
        if (shm_unlink("/tmp1234") != 0) {
            std::cerr << "OOPS: shm_unlink() failed" << std::endl;
        }
    }
};

std::shared_ptr<int> get_shared_int_memory(size_t n) {
    void *mem = nullptr;
    int shmfd = shm_open("/tmp1234", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
    if (shmfd < 0) {
        throw std::string(strerror(errno));
    }
    if (ftruncate(shmfd, n*sizeof(int)) == -1) {
        throw std::string(strerror(errno));
    }
    mem = mmap(nullptr, n*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED,
        shmfd, 0);
    if (mem == MAP_FAILED) {
        throw std::string(strerror(errno));
    }
    return std::shared_ptr<int>(static_cast<int*>(mem), SharedMemoryDetacher());
}

int main() {
    // get and attach shared memory for 100 `int`s
    std::shared_ptr<int> smp(get_shared_int_memory(100));

    // initialize the shared memory
    for (int i=0; i<100; ++i) {
        smp.get()[i] = i * 42;
    }

    // deal with shared memory somewhere else...
    // ...

    std::cout << "enter any key to continue:";
    std::cin.get();

    // release shared memory
    smp.reset();
}