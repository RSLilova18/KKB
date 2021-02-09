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
    string name, city, address;
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

//template
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

SCHOOL enterSchoolData()
{
    SCHOOL school;

    cout << endl;
    cout << "Enter city: ";
    cin >> school.city;
    cout << "Enter name: ";
    cout << school.name;
    cout << "Enter address: ";
    cout << school.address;


    return school;
}

STUDENT enterStudentsData(int counterStudent = 1)
{
    STUDENT student;


    cout << endl;
    cout << counterStudent << ".Enter student name: ";
    cin >> student.name;
    cout << counterStudent << ".Enter student surname: ";
    cin >> student.surname;
    cout << counterStudent << ".Enter student class: ";
    cin >> student.classStudent;
    cout << counterStudent << ".Enter student class name: ";
    cin >> student.nameClass;
    cout << counterStudent << ".Enter student role: ";
    cin >> student.role;
    cout << counterStudent << ".Enter student mail: ";
    cin >> student.mail;


    return student;
}

vector<STUDENT> enterStudents(int numberOfStudents) {
    STUDENT student;
    vector<STUDENT> students;
    for (int i = 0; i < numberOfStudents; i++)
    {
        student = enterStudentsData(i + 1);
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



    /*fstream studs, teachers, teams, schools;
    string a, b;
    studs.open("students.csv", ios::app);
    teachers.open("teachers.csv", ios::app);
    teams.open("teams.csv", ios::app);
    schools.open("schools.csv", ios::app);


    studs.close();
    teachers.close();
    teams.close();
    schools.close();*/

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

