#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cmath>
#include <fstream>
#include "CustomDataTypes.h" 
#include "CustomOperators.h"
#include "DataLayerFunctions.h" 
#include "FilterFunctions.h"
#include "FunctionsFromCustomDataTypes.h"

using namespace std;

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

void printStudentsData(vector <STUDENT> data)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i].printStudent();
    }
}

void printTeamsData(vector<TEAM> data)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i].printTeam();
    }
}

void printTeachersData(vector<TEACHER> data)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i].printTeacherData();
    }
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
    int numberOfStudents, numberOfTeams, numberOfTeachers;
    /*cout << endl;*/
    cout << "Enter the city of the school: ";
    cin >> school.city;
    cout << "Enter the name: ";
    cin >> school.name;
    cout << "Enter the address: ";
    cin.ignore();
    getline(cin, school.address);
    cout << "Enter the number of students in " << school.city << ": ";
    cin >> numberOfStudents;
    school.students = enterStudents(numberOfStudents);
    cout << endl;
    cout << "Enter the number of the teams in the school: ";
    cin >> numberOfTeams;
    school.teams = enterTeams(numberOfTeams, school.students);
    cout << "Enter the number of teachers in the school: ";
    cin >> numberOfTeachers;
    school.teachers = enterTeachers(numberOfTeachers, school.teams);

    return school;
}