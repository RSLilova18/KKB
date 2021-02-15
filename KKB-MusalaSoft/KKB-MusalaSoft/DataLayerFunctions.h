#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <sstream>
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

void openFiles(fstream& studs, fstream& teachers,fstream& teams,fstream& school, string path) {

    
    studs.open(path+"/StudentFile.csv", ios::app);
    teachers.open(path+ "/Teachers.csv", ios::app);
    teams.open(path+"/Teams.csv", ios::app);
    school.open(path+"/School.csv", ios::app);
    if (!studs.is_open())
    {
        cout << "1 problem" << endl;
    }
    if (!teachers.is_open())
    {
        cout << "2 problem" << endl;
    }
    if (!teams.is_open())
    {
        cout << "3 problem" << endl;
    }
    if (!school.is_open())
    {
        cout << "4 problem" << endl;
    }
}

void closeFiles(fstream& studs, fstream& teachers, fstream& teams, fstream& school) {
    if (!studs.is_open())
    {
        studs.close();
    }
    if (!teachers.is_open())
    {
        teachers.close();
    }
    if (!teams.is_open())
    {
        teams.close();
    }
    if (!school.is_open())
    {
        school.close();
    }
}

void createSchoolFolder(string name) {
    char* c1;
    string  firstCommand, secondCommand;
    firstCommand = "mkdir \"" + name + "\"";
    secondCommand = "Xcopy /E \"template\" \"" + name + "\"";
    name = "cd ../../CSVFiles && " + firstCommand;
    c1 = &name[0];
    system(c1);
    name = "cd ../../CSVFiles && " + secondCommand;
    c1 = &name[0];
    system(c1);
}

void setSchoolDirectory(string& schoolNameAndTown) {
    schoolNameAndTown = "../../CSVFiles/" + schoolNameAndTown;
}

int stringToInt(string str) {
    stringstream geek(str);
    int x = 0;
    geek >> x;
    return x;
}

bool getLastId(string& id, fstream& stream) {
    string line;
    if (!stream.is_open())
    {
        cout << "Couldn't open" << endl;
        return false;
    }
    else
    {
        stream.seekg(-1, ios_base::end);                // go to one spot before the EOF

        bool keepLooping = true;
        while (keepLooping) {
            char ch;
            stream.get(ch);                            // Get current byte's data

            if ((int)stream.tellg() <= 1) {             // If the data was at or before the 0th byte
                stream.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if (ch == '\n') {                   // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            }
            else {                                  // If the data was neither a newline nor at the 0 byte
                stream.seekg(-2, ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }

        getline(stream, line);
        int lastComaId;
        lastComaId = line.find(',');
        id = line.substr(0, lastComaId);
        stream.clear();
        stream.seekg(0);
        return true;
    }
    cout << "Not found" << endl;
    return false;
}

void insertStdent(STUDENT student, fstream& file, string id) {

    string line;
    line = id + "," + student.name + "," + student.surname + "," + to_string(student.classStudent) + ",";
    line += student.nameClass + "," + to_string(student.grade) + "," + student.mail + '\n';
    file << line;
}

bool insertStudentsIntoFile(vector<STUDENT> students, fstream& file) {
    string id;
    int intId;
    if (getLastId(id, file)) {
        intId = stringToInt(id);
        intId++;
        id = to_string(intId);
        for (size_t i = 0; i < students.size(); i++)
        {
            insertStdent(students[i], file, id);
        }
        return true;
    }
    return false;
}