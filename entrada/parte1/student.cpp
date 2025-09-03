#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string cui;
    string apePaterno;
    string apeMaterno;
    string nombres;

public:
    Student(string _cui, string _apePaterno, string _apeMaterno, string _nombres)
    {
        cui = _cui;
        apePaterno = _apePaterno;
        apeMaterno = _apeMaterno;
        nombres = _nombres;
    }

    void presentarse()
    {
        cout << cui << "-" << apePaterno << "/" << apeMaterno << ", " << nombres << endl;
    }
};