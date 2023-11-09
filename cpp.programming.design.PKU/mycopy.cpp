#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){
    if(argc != 3){
        cout << "File name mising!" << endl;
        return -1;
    }

    // open source file, used to read
    ifstream srcFile(argv[1], ios::in | ios::binary);
    if(!srcFile){
        cout << "Source File open error!" << endl;
        return -1;
    }

    // open destination file, used to write
    ofstream dstFile(argv[2], ios::out | ios::binary);
    if(!dstFile){
        cout << "Destination File open error!" << endl;
        srcFile.close();
        return -2;
    }

    char temp;
    while(srcFile.get(temp)){
        dstFile.put(temp);
    }

    srcFile.close();
    dstFile.close();

    return 0;
}