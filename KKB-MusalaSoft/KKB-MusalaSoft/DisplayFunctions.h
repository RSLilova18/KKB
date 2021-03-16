#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <time.h>
#include "CustomDataTypes.h" 
#include "CustomOperators.h"
#include "DataLayerFunctions.h" 
#include "FilterFunctions.h"
#include "FunctionsFromCustomDataTypes.h"
#include "GlobalVariables.h"

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
    for (size_t i = 0; i < school.students.size(); i++)
    {
        school.students[i].id = i + 1;
    }
    cout << endl;
    cout << "Enter the number of the teams in the school: ";
    cin >> numberOfTeams;
    school.teams = enterTeams(numberOfTeams, school.students);
    for (size_t i = 0; i < school.teams.size(); i++)
    {
        school.teams[i].id = i + 1;
    }
    cout << "Enter the number of teachers in the school: ";
    cin >> numberOfTeachers;
    school.teachers = enterTeachers(numberOfTeachers, school.teams);
    for (size_t i = 0; i < school.teachers.size(); i++)
    {
        school.teachers[i].id = i + 1;
    }
    return school;
}

void printSchoolData(SCHOOL school) {
    cout << "School city: ";
    cout << school.city << endl;
    cout << "School name: ";
    cout << school.name << endl;
    cout << "School address: ";
    cout << school.address << endl;
    cout << endl << "Students data: " << endl << endl;
    printStudentsData(school.students);
    cout << "Teams data: " << endl << endl;
    printTeamsData(school.teams);
    cout << "Teachers data: " << endl << endl;
    printTeachersData(school.teachers);
}

void showAllSchoolNames() {
    char* c1;
    string  firstCommand = "cd ../../CSVFiles && dir /B | findstr /v /i \"template\" |findstr /v /i \"BACKUP\"";
    c1 = &firstCommand[0];
    system(c1);
}

vector<TEAM> randomDistributeTeams(vector<TEAM> teamsFromFile, vector<STUDENT> studentsFromFile)
{
    int numberOfTeams;
    vector<TEAM> teams;
    TEAM team;
    vector<STUDENT> studentsFromTeams;
    studentsFromTeams = getStudentsFromTeams(teamsFromFile);
    deleteTakenStudents(studentsFromFile, studentsFromTeams);
    if (studentsFromFile.size() != 0)
    {
        cout << "How many teams do you want to enter: ";
        cin >> numberOfTeams;
        for (int i = 0; i < numberOfTeams; i++)
        {
            if (studentsFromFile.size() != 0)
            {
                cout << endl;
                cout << i + 1 << ".Enter team name: ";
                cin >> team.name;
                cout << i + 1 << ".Enter team description: ";
                cin.ignore();
                getline(cin, team.description);
                cout << i + 1 << ".Enter team creation date: ";
                cin >> team.date;
                distributeTeamMembers(team, studentsFromFile);
                cout << "Automatic dirstribution for the roles..." << endl;
                teams.push_back(team);
            }
            else {
                cout << "No more free students! You created only " << teams.size() << " teams." << endl;
                return teams;
            }
        }
    }
    else
    {
        cout << "There are no free students! No teams were created!" << endl;
        return teams;
    }
    return teams;
}

void changeTeamStatusMenu(fstream& file) {
    int id, option;
    string status;
    cout << "Enter the id of the team you want to replace: ";
    id = readInt();
    cout << "...................." << endl;
    cout << ". 1. In use        ." << endl;
    cout << ". 2. Not active    ." << endl;
    cout << "...................." << endl;
    option = readInt();
    while (!(option >= 1 && option <= 2)) {
        cout << "Not a valid option!" << endl << endl;
        cout << "...................." << endl;
        cout << ". 1. In use        ." << endl;
        cout << ". 2. Not active    ." << endl;
        cout << "...................." << endl;
        option = readInt();
    }
    if (option == 1)
    {
        status = "In use";
    }
    else {
        status = "Not active";
    }
    changeTeamStatus(file, id, status);
}


