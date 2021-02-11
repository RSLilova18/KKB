#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cmath>
#include <fstream>
#include "CustomDataTypes.h" 
#include "CustomOperators.h"

using namespace std;

bool checkIfStudentExist(STUDENT& student, vector<STUDENT> studentsList) {
    string role;
    role = student.role;
    for (size_t i = 0; i < studentsList.size(); i++)
    {
        if (student == studentsList[i])
        {
            student = studentsList[i];
            student.role = role;
            return true;
        }
    }
    return false;
}

bool checkIfTeamNameIsValid(string name, vector<TEAM> teams)
{
    for (size_t i = 0; i < teams.size(); i++)
    {
        if (name == teams[i].name)
        {
            return true;
        }
    }
    return false;
}

bool checkStudentsData(STUDENT data, int counterStudent = 1)
{
    return !(data.grade > 6 or data.grade < 2);
}

vector<STUDENT> enterStudents(int numberOfStudents) {
    STUDENT student;
    vector<STUDENT> students;
    for (int i = 0; i < numberOfStudents; i++)
    {
        student.enterData(i + 1);
        while (checkStudentsData(student) == false)
        {

            cout << "Invalid grade!" << endl;
            student.enterData(i + 1);
        }
        students.push_back(student);
    }
    return students;
}


vector<TEAM> enterTeams(int numberOfTeams, vector<STUDENT> students) {
    TEAM team;
    vector<TEAM> teams;
    for (int i = 0; i < numberOfTeams; i++)
    {
        team.enterTeamData(students, i + 1);
        teams.push_back(team);
    }
    return teams;
}

vector<TEACHER> enterTeachers(int numberOfTeachers, vector<TEAM> teams) {
    TEACHER teacher;
    vector<TEACHER> teachers;
    for (int i = 0; i < numberOfTeachers; i++)
    {
        teacher.enterTeacherData(teams, i + 1);
        teachers.push_back(teacher);
    }
    return teachers;
}

