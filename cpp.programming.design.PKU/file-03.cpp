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
    fstream ioFile("students.dat", ios::binary | ios::in | ios::out);
    
    // check file
    if(!ioFile){
        cout << "error" << endl;
        return -1;
    }
    
    // modify info of the third student
    ioFile.seekp(2*sizeof(s), ios::beg);
    cout << "name:";
    cin >> s.szName;
    cout << "score:";
    cin >> s.nScore;
    ioFile.write((char *)&s, sizeof(s));
    
    // show info of all students
    ioFile.seekg(0, ios::beg);
    while(ioFile.read((char *)&s, sizeof(s))){
        cout << s.szName << " " << s.nScore << endl;
    }

    // close file
    ioFile.close();

    return 0;
}