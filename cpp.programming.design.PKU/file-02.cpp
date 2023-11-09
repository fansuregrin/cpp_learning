#include <fstream>
#include <iostream>

using namespace std;

class CStudent{
    public:
        char szName[20];
        int nScore;
};

int main(){
    CStudent s;

    // open file
    ifstream inFile("students.dat", ios::in | ios::binary);
    
    // check
    if(!inFile){
        cout << "error" << endl;
        return -1;
    }

    //read info into s from file, print info
    while(inFile.read((char *)&s, sizeof(s))){
        int nReadedBytes = inFile.gcount();
        cout << s.szName << " " << s.nScore << endl;
    }

    // close file
    inFile.close();
    
    return 0;
}