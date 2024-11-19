#include <iostream>
using namespace std;

int i = 5;          //i is a global variable
int j = 7;          //j is also a global variable

int main()
{
    int i = 50;     //i is a local variable
    cout << "i is " << i << endl;
    cout << "::i is " << ::i << endl;
    cout << "j is " << j << endl;
    cout << "::j is " << ::j << endl;

    //start a new scope
    {
        int i = 500;
        cout << "in first scope" << endl;
        cout << "i is " << i << endl << "::i is " << ::i << endl;
        cout << "j is " << j << endl << "::j is " << ::j << endl; 

        //start another scope
        {
            int i = 5000;
            int j = 7000;
            cout << "in another scope" << endl;
            cout << "i is " << i << ", ::i is " << ::i << endl;
            cout << "j is " << j << ", ::j is " << ::j << endl;
        }

        cout << "after innermost scope" << endl;
        cout << "i is " << i << ", ::i is " << ::i << endl;
        cout << "j is " << j << ", ::J is " << ::j << endl;
    }

    cout << "after first scope" << endl;
    cout << "i is " << i << ", ::i is " << ::i << endl;
    cout << "j is " << j << ", ::J is " << ::j << endl;

    return 0;
}