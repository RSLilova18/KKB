#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <cmath>
#include <windows.h>
#include <fstream>


using namespace std;

//Jobs hierarchy
struct STUDENT {
    string name, surname, role, mail, nameClass;
    int classStudent;
};

struct TEAM {
    string name, description, date, status;
    vector<STUDENT> students;
};

struct TEACHER {
    string name, surrname, mail;
    vector<TEAM> teams;
};

struct SCHOOL {
    string name, city, adress;
    vector<TEACHER> teachers;
    vector<TEAM> teams;
    vector<STUDENT> students;
};

void printStudentsData(vector <STUDENT> data, int numberOfStudents)
{
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < numberOfStudents; i++)
    {
        cout << data[i].name << " " << data[i].surname << " " << data[i].classStudent << " " << data[i].nameClass;
        cout << endl;
        cout << "Role and email: " << data[i].role << " - " << data[i].mail;
        cout << endl;
        cout << "--------------------------------------------------------------------------------";
        cout << endl;
    }
}

bool checkStudentsData(vector <STUDENT> data)
{
    return true;

}

int readInt()
{
    int a;

    //loops until the user enters an integer
    while (!(cin >> a))
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Incorrect value!" << endl;
    }

    return a;
}

void centerString(string s)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    //gets the window size and assigns it to the csbiInfo variable
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    COORD NewSBSize;
    //assigns the x size of the screen
    NewSBSize.X = csbiInfo.dwSize.X;
    int l = s.size();
    //calculates the spaces needed before the text in order to be centered
    int pos = (int)((NewSBSize.X - l) / 2);
    for (int i = 0; i < pos; i++)
        cout << " ";

    cout << s;
}

void printStrings(string rawStr)
{
    string str;
    int indexDel = 0;
    //searches for a comma in the string
    while (rawStr.find(",") != string::npos)
    {
        indexDel = rawStr.find(",");
        str = rawStr.substr(0, indexDel);
        rawStr = rawStr.substr(indexDel + 1, rawStr.size() - indexDel);
        centerString(str);
        cout << endl;
    }
}


STUDENT enterStudentsData()
{
    STUDENT student;
    cin >> student.name;
    cin >> student.surname;
    cin >> student.classStudent;
    cin >> student.nameClass;
    cin >> student.role;
    cin >> student.mail;
    return student;
}

vector<STUDENT> enterStudents(int numberOfStudents) {
    STUDENT student;
    vector<STUDENT> students;
    for (int i = 0; i < numberOfStudents; i++)
    {
        student = enterStudentsData();
        students.push_back(student);
    }
    return students;
}

bool menu() {
    cout << "Enter how many students do you want: ";
    int numberOfStudents;
    cin >> numberOfStudents;
    vector <STUDENT> students;
    students = enterStudents(numberOfStudents);
    /*while (checkStudentsData(students) == false)
    {
        //enterStudentsData(students, numberOfStudents);
    }*/
    printStudentsData(students, numberOfStudents);
    return false;

}



int main()
{
    while (menu());

}
/*bobo
dimitrov
10
v
backend
BDD
valco
petrov
10
g
front
VPP*/

