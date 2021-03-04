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
#include "DisplayFunctions.h"

using namespace std;

void STUDENT::enterData(int counterStudent=1) {
    cout << endl;
    cout << counterStudent << ".Enter student name: ";
    cin >> name;
    cout << counterStudent << ".Enter student surname: ";
    cin >> surname;
    cout << counterStudent << ".Enter student class: ";
    cin >> classStudent;
    cout << counterStudent << ".Enter student class name: ";
    cin >> nameClass;
    cout << counterStudent << ".Enter student grade: ";
    cin >> grade;
    cout << counterStudent << ".Enter student mail: ";
    cin >> mail;
}

void STUDENT::printStudent() {
    cout << endl;
    cout << "--------------------------------------------------------------------------------";
    cout << endl;
    cout << "--" << name << " " << surname << " " << classStudent << " " << nameClass;
    cout << endl;
    cout << "--" << "Grade and email: " << " " << grade << " - " << mail;
    cout << endl;
    cout << "--------------------------------------------------------------------------------";
    cout << endl;
}

STUDENT TEAM::enterStudentData() {
    STUDENT student;
    cout << "--Enter student mail: ";
    cin >> student.mail;
    return student;
}

void TEAM::enterTeamData(vector<STUDENT> students, int teamNumber=1) {
    cout << endl;
    cout << teamNumber << ".Enter team name: ";
    cin >> name;
    cout << teamNumber << ".Enter team description: ";
    cin.ignore();
    getline(cin, description);
    cout << teamNumber << ".Enter team creation date: ";
    cin >> date;

    cout << endl;
    cout << "OK, now enter the data for a backend: " << endl;
    backEnd = enterStudentData();
    studentValidationPrint(backEnd, students, "OK, now enter the data for a backend: ");
    cout << "OK, now enter the data for a frontend: " << endl;
    frontEnd = enterStudentData();
    studentValidationPrint(frontEnd, students, "OK, now enter the data for a frontend: ");
    cout << "OK, now enter the data for a scrum master: " << endl;
    scrumMaster = enterStudentData();
    studentValidationPrint(scrumMaster, students, "OK, now enter the data for a scrum master: ");
    cout << "OK, now enter the data for a quality engineer: " << endl;
    qaEngineer = enterStudentData();
    studentValidationPrint(qaEngineer, students, "OK, now enter the data for a quality engineer: ");
    scrumMaster.role = "scrum Master";
    frontEnd.role = "Front End";
    backEnd.role = "Back End";
    qaEngineer.role = "Quality engineer";
}

void TEAM::studentValidationPrint(STUDENT& student, vector<STUDENT> studentsList, string msg) {
    while (!checkIfStudentExist(student, studentsList)) {
        cout << endl;
        cout << "This student does not exist! Try again!" << endl;
        cout << endl;
        cout << msg << endl;
        student = TEAM::enterStudentData();
    }
}


void TEAM::printTeam()
{
    cout << "--------------------------------------------------------------------------------";
    cout << endl;
    cout << name;
    cout << endl;
    cout << description;
    cout << endl;
    cout << date;
    cout << endl << endl;
    cout << "The students of the team: " << endl;
    backEnd.printStudent();
    frontEnd.printStudent();
    scrumMaster.printStudent();
    qaEngineer.printStudent();
    cout << "--------------------------------------------------------------------------------";
    cout << endl;
}

TEAM TEACHER::enterTeamData() {
    TEAM team;
    cin >> team.name;
    return team;
}

void TEACHER::teamValidationPrint(TEAM& team, vector<TEAM> teams) {
    while (!checkIfTeamExist(team, teams))
    {
        cout << endl;
        cout << "This team does not exist! Try again!" << endl;
        cout << endl;
        team = TEACHER::enterTeamData();
    }
}
void TEACHER::enterTeacherData(vector<TEAM> teams, int teacherNumberCount =1) {
    int teamsMentoredCount;
    string nameTeamTemp;
    TEAM team;
    cout << teacherNumberCount << ".Enter teacher name: ";
    cin >> name;
    cout << teacherNumberCount << ".Enter teacher surname: ";
    cin >> surrname;
    cout << teacherNumberCount << ".Enter teacher mail: ";
    cin >> mail;

    cout << "How many teams does the teacher mentors: ";
    cin >> teamsMentoredCount;
    cout << "Enter the team names that the teacher mentors: ";
    for (int i = 0; i < teamsMentoredCount; i++)
    {
        team = enterTeamData();
        teamValidationPrint(team,teams);
        teamsMentored.push_back(team);
    }
}

void TEACHER::printTeacherData() {
    cout << "--------------------------------------------------------------------------------";
    cout << endl;
    cout << name << " " << surrname;
    cout << endl;
    cout << "Email: " << mail;
    cout << endl;
    for (size_t j = 0; j < teamsMentored.size(); j++)
    {
        cout << j + 1 << ". Team name : " << teamsMentored[j].name << endl;
    }
    cout << "--------------------------------------------------------------------------------";
    cout << endl;
}
