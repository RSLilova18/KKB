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


void enterStudentsData(vector <STUDENT> data, int numberOfStudents)
{
    cin >> numberOfStudents;
    for (int i = 0; i < numberOfStudents; i++)
    {
        cin >> data[i].name;
        cin >> data[i].surname;
        cin >> data[i].classStudent;
        cin >> data[i].nameClass;
        cin >> data[i].role;
        cin >> data[i].mail;
    }

}

void printStudentsData(vector <STUDENT> data, int numberOfStudents)
{
    cout << endl;
    cout << "--------------------------------------------------------------------------------";
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

bool menu(vector <STUDENT> data, int numberOfStudents) {

    enterStudentsData(data, numberOfStudents);
    while (checkStudentsData(data) == false)
    {
        enterStudentsData(data, numberOfStudents);

    }
    printStudentsData(data, numberOfStudents);
    return false;

}



int main()
{
    cout << "Enter how many students do you want: ";
    int numberOfStudents;
    vector <STUDENT> data;
    while (menu(data, numberOfStudents));


}


