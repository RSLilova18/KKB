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

void print_state(const std::ios& stream) {
    std::cout << " good()=" << stream.good() << endl;
    std::cout << " eof()=" << stream.eof() << endl;
    std::cout << " fail()=" << stream.fail() << endl;
    std::cout << " bad()=" << stream.bad() << endl;
}

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

    
    studs.open(path+"/StudentFile.csv");
    teachers.open(path+ "/Teachers.csv");
    teams.open(path+"/Teams.csv");
    school.open(path+"/School.csv");
    if (!studs.is_open())
    {
        cout << "1 problem" << endl;
        print_state(studs);
    }
    if (!teachers.is_open())
    {
        cout << "2 problem" << endl;
        print_state(teachers);
    }
    if (!teams.is_open())
    {
        cout << "3 problem" << endl;
        print_state(teams);
    }
    if (!school.is_open())
    {
        cout << "4 problem" << endl;
        print_state(school);
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

bool getLastId(string& id, fstream& file) {
    string line;
    if (!file.is_open())
    {
        cout << "Couldn't open" << endl;
        return false;
    }
    else
    {
        file.clear();
        file.seekg(ios::beg);
        file.seekp(ios::beg);
        print_state(file);
        //Got to the last character before EOF
        file.seekg(-1, ios_base::end);                // go to one spot before the EOF

        bool keepLooping = true;
        while (keepLooping) {
            char ch;
            file.get(ch);                            // Get current byte's data

            if ((int)file.tellg() <= 1) {             // If the data was at or before the 0th byte
                file.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if (ch == '\n') {                   // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            }
            else {                                  // If the data was neither a newline nor at the 0 byte
                file.seekg(-2, ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }

        getline(file, line);
        int lastComaId;
        lastComaId = line.find(',');
        id = line.substr(0, lastComaId);
        file.clear();
        file.seekg(0);
        return true;
    }
    return false;
}

void insertStdent(STUDENT student, fstream& file, string id) {

    string line;
    line = '\n' + id + "," + student.name + "," + student.surname + "," + to_string(student.classStudent) + ",";
    line += student.nameClass + "," + to_string(student.grade) + "," + student.mail + ",";
    file.seekp(-1,ios_base::end);
    file << ",";
    file << line;
    file.seekp(ios_base::beg);
}

bool insertStudentsIntoFile(vector<STUDENT> students, fstream& file) {
    string id;
    int intId;
        for (size_t i = 0; i < students.size(); i++)
        {
            getLastId(id, file);
            intId = stringToInt(id);
            intId++;
            id = to_string(intId);
            insertStdent(students[i], file, id);
        }
    return true;
}

vector<STUDENT> getStudentsFromFile(fstream& studentsList) {
    vector<STUDENT> students;
    string line, token;
    size_t comaIndex = 0;
    STUDENT_FIELD_ORDER order;
    size_t i = 0;
    while (getline(studentsList, line)) {
        i = 0;
        STUDENT student;
        comaIndex = line.find(',');
        token = line.substr(0, comaIndex);
        if (token == "0") continue;
        student.id = stringToInt(token);
        line = line.substr(comaIndex + 1, line.size() - comaIndex - 1);
        do {
            comaIndex = line.find(',');
            token = line.substr(0, comaIndex);
            line = line.substr(comaIndex + 1, line.size() - comaIndex - 1);
            order = (STUDENT_FIELD_ORDER)i;
            if (order == NAME)
            {
                student.name = token;
            }
            if (order == SURNAME)
            {
                student.surname = token;
            }
            if (order == MAIL)
            {
                student.mail = token;
            }
            if (order == CLASS_NAME)
            {
                student.nameClass = token;
            }
            if (order == CLASS_STUDENT)
            {
                student.classStudent = stringToInt(token);
            }
            if (order == GRADE)
            {
                student.grade = stof(token);
            }
            i++;
        } while (line.find(',') != string::npos);
        students.push_back(student);
    }
    studentsList.seekp(ios_base::beg);
    studentsList.seekg(ios_base::beg);
    return students;
}


STUDENT getIDfromStudentFile(int intToken, vector<STUDENT> students)
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (intToken = students[i].id)
        {
            return students[i];
            break;
        }
    }
}
vector<TEAM> getTeamsFromFile(fstream& teamsList, vector<STUDENT> students)
{
    vector<TEAM> teams;
    string line, token;
    size_t comaIndex = 0;
    TEAM_FIELD_ORDER order;
    int intToken;
    size_t i = 0;
    while (getline(teamsList, line))
    {
        i = 0;
        TEAM team;
        comaIndex = line.find(',');
        token = line.substr(0, comaIndex);
        if (token == "0") continue;
        team.id = stringToInt(token);
        line = line.substr(comaIndex + 1, line.size() - comaIndex - 1);


        do {

            comaIndex = line.find(',');
            token = line.substr(0, comaIndex);
            line = line.substr(comaIndex + 1, line.size() - comaIndex - 1);
            order = (TEAM_FIELD_ORDER)i;
            if (order == TEAMNAME)
            {
                team.name = token;
            }
            if (order == DESCRIPTION)
            {
                team.description = token;
            }
            if (order == TEAMDATE)
            {
                team.date = token;
            }
            if (order == STATUS)
            {
                team.status = token;
            }
            if (order == BACKEND)
            {
               intToken = stringToInt(token);
            

                team.backEnd = getIDfromStudentFile(intToken, students);
            }
            if (order == FRONTEND)
            {
                 intToken = stringToInt(token);
           
                 team.frontEnd=getIDfromStudentFile(intToken,students);
            }
            if (order == SCRUM)
            {
                 intToken = stringToInt(token);
               

                team.scrumMaster = getIDfromStudentFile(intToken, students);
            }
            if (order == QA)
            {
                 intToken = stringToInt(token);
                
                team.qaEngineer = getIDfromStudentFile(intToken, students);
            }
            i++;
        } while (line.find(',') != string::npos);
        teams.push_back(team);
    }
    teamsList.seekp(ios_base::beg);
    teamsList.seekg(ios_base::beg);
    return teams;
}
bool verifySelectedSchool(string school) {
    fstream file;
    school = "../../CSVFiles/" + school;
    file.open(school + "/StudentFile.csv");
    return file.is_open();
}

void insertTeam(TEAM team, fstream& file, string id) {
    string line;
    line = '\n' + id + "," + team.name + "," + team.description + "," + team.date + "," + team.status + ",";
    line += to_string(team.backEnd.id) + "," + to_string(team.frontEnd.id) + "," + to_string(team.scrumMaster.id);
    line += "," + to_string(team.qaEngineer.id) + ",";
    file.seekp(-1, ios_base::end);
    file << ",";
    file << line;
    file.seekp(ios_base::beg);
}
bool insertTeamsIntoFile(vector<TEAM> teams, fstream& file) {
    string id;
    int intId;
    for (size_t i = 0; i < teams.size(); i++)
    {
        getLastId(id, file);
        intId = stringToInt(id);
        intId++;
        id = to_string(intId);
        insertTeam(teams[i], file, id);
    }
    return true;
}

void to_lower(string& str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        str[i] = tolower(str[i]);
    }
}

bool cmpStudentsAlphabetically(STUDENT first, STUDENT second)
{
    string firstName, secondName;
    firstName = first.name + first.surname;
    secondName = second.name + second.surname;
    to_lower(firstName);
    to_lower(secondName);
    for (size_t i = 0; i < min(firstName.size(), secondName.size()); i++)
    {
        if (firstName[i] == secondName[i])
        {
            continue;
        }
        return firstName[i] < secondName[i];
    }
    return firstName.size() < secondName.size();
}