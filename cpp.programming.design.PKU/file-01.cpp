#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

class CStudent{
    public:
        char szName[20];
        int nScore;
};

int main(){
    CStudent s;

    // open file
    ofstream outFile("students.dat", ios::out | ios::binary);
    
    // check
    if(!outFile){
        cout << "error" << endl;
        return -1;
    }

    // get info, write into file
    while(cin >> s.szName >> s.nScore){
        if(strcmp(s.szName, "exit") == 0){
            break;
        }
        outFile.write((char *)&s, sizeof(s));
        cout << s.szName << " " << s.nScore << " was writed..." << endl;
    }

    // close file
    outFile.close();
    
    return 0;
}