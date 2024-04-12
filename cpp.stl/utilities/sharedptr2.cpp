#include <memory>
#include <fstream>
#include <cstdio>
#include <string>


class FileDeleter {
public:
    FileDeleter(const std::string &fn): filename(fn) {}
    
    void operator()(std::ofstream *fp) {
        fp->close(); // 关闭文件流
        std::remove(filename.c_str());  // 删除文件
    }
private:
    std::string filename;
};

int main() {
    std::shared_ptr<std::ofstream> fp(new std::ofstream("tmp.txt"),
        FileDeleter("tmp.txt"));
}