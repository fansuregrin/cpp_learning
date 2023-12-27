// topic: random accesss to a stream

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

int main() {
    // open for input and output and preposition file pointers to end-of-file
    std::fstream inOut("copyOut", std::fstream::ate | std::fstream::in | std::fstream::out);
    if (!inOut) {
        std::cerr << "Unable to open file!" << std::endl;
        return EXIT_FAILURE;
    }

    // inOut is opened in ate mode, so it starts out positioned at the end
    auto end_mark = inOut.tellg();  // remember original end-of-file position
    std::string line;  // hold each line of input
    size_t cnt = 0;  // accumulator for the byte count
    inOut.seekg(0, std::fstream::beg);  // reposition to the start of the file

    // while we haven't hit an error and are still reading the original data 
    // and can get another line of input
    while (inOut && inOut.tellg() != end_mark && getline(inOut, line)) {
        cnt += line.size() + 1;  // add 1 to account for the newline
        auto mark = inOut.tellg();  // remember the read position
        inOut.seekp(0, std::fstream::end);  // set the write marker to the end
        inOut << cnt;  // write the accumulated length
        if (mark != end_mark) inOut << ' ';  // print a separator if this is not the last line
        inOut.seekg(mark);  // restore the read position
    }
    inOut.seekp(0, std::fstream::end);  // seek to the end
    inOut << '\n';  // write a newline at end-of-file

    return 0;
}