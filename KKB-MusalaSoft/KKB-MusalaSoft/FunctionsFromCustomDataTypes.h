#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cmath>
#include <fstream>
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
    cout << "--" << "Role, grade and email: " << role << " " << grade << " - " << mail;
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

void TEACHER::enterTeacherData(vector<TEAM> teams, int teacherNumberCount =1) {
    int teamsMentoredCount;
    string nameTeamTemp;
    cout << teacherNumberCount << ".Enter teacher name: ";
    cin >> name;
    cout << teacherNumberCount << ".Enter teacher surname: ";
    cin >> surrname;
    cout << teacherNumberCount << ".Enter teacher mail: ";
    cin >> mail;

    cout << "How many teams does the teacher mentors: ";
    cin >> teamsMentoredCount;
    for (int i = 0; i < teamsMentoredCount; i++)
    {
        cout << "Enter the team name that the teacher mentors: ";
        cin >> nameTeamTemp;
        while (!checkIfTeamNameIsValid(nameTeamTemp, teams)) {
            cout << "That team doesn't exist in the school! Try again!" << endl;
            cin >> nameTeamTemp;
        }
        teamNames.push_back(nameTeamTemp);
    }
}

void TEACHER::printTeacherData() {
    cout << "--------------------------------------------------------------------------------";
    cout << endl;
    cout << name << " " << surrname;
    cout << endl;
    cout << "Email: " << mail;
    cout << endl;
    for (size_t j = 0; j < teamNames.size(); j++)
    {
        cout << j + 1 << ". Team name : " << teamNames[j] << endl;
    }
    cout << "--------------------------------------------------------------------------------";
    cout << endl;
}
