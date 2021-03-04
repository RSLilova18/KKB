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
#include<sstream>
#include "CustomDataTypes.h" 
#include "CustomOperators.h"

using namespace std;

int randomInt(int minimum, int maximum)
{
    return rand() % (maximum - minimum + 1) + minimum;
}

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

bool checkIfTeamExist(TEAM& team, vector<TEAM> teams)
{
    for (size_t i = 0; i < teams.size(); i++)
    {
        if (team == teams[i])
        {
            team = teams[i];
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

STUDENT getIDfromStudentFile(int intToken, vector<STUDENT> students)
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (intToken == students[i].id)
        {
            return students[i];
            break;
        }
    }
}

TEAM getIdfromTeacherFile(int intToken, vector<TEAM> teams) {
    for (size_t i = 0; i < teams.size(); i++)
    {
        if (intToken == teams[i].id)
        {
            return teams[i];
            break;
        }
    }
}

vector<STUDENT> getStudentsFromFile(fstream& studentsList) {
    studentsList.clear();
    studentsList.seekg(ios_base::beg);
    studentsList.seekp(ios_base::beg);
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
            if (order == STUDENT_FIELD_ORDER::NAME)
            {
                student.name = token;
            }
            if (order == STUDENT_FIELD_ORDER::SURNAME)
            {
                student.surname = token;
            }
            if (order == STUDENT_FIELD_ORDER::MAIL)
            {
                student.mail = token;
            }
            if (order == STUDENT_FIELD_ORDER::CLASS_NAME)
            {
                student.nameClass = token;
            }
            if (order == STUDENT_FIELD_ORDER::CLASS_STUDENT)
            {
                student.classStudent = stringToInt(token);
            }
            if (order == STUDENT_FIELD_ORDER::GRADE)
            {
                student.grade = stof(token);
            }
            i++;
        } while (line.find(',') != string::npos);
        students.push_back(student);
    }
    studentsList.clear();
    studentsList.seekg(ios_base::beg);
    studentsList.seekp(ios_base::beg);
    return students;
}

vector<TEAM> getTeamsFromFile(fstream& teamsList, vector<STUDENT> students)
{
    teamsList.clear();
    teamsList.seekp(ios_base::beg);
    teamsList.seekg(ios_base::beg);
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
            if (order == TEAM_FIELD_ORDER::TEAMNAME)
            {
                team.name = token;
            }
            if (order == TEAM_FIELD_ORDER::DESCRIPTION)
            {
                team.description = token;
            }
            if (order == TEAM_FIELD_ORDER::TEAMDATE)
            {
                team.date = token;
            }
            if (order == TEAM_FIELD_ORDER::STATUS)
            {
                team.status = token;
            }
            if (order == TEAM_FIELD_ORDER::BACKEND)
            {
                intToken = stringToInt(token);
                team.backEnd = getIDfromStudentFile(intToken, students);
            }
            if (order == TEAM_FIELD_ORDER::FRONTEND)
            {
                 intToken = stringToInt(token);  
                 team.frontEnd=getIDfromStudentFile(intToken,students);
            }
            if (order == TEAM_FIELD_ORDER::SCRUM)
            {
                 intToken = stringToInt(token);
                 team.scrumMaster = getIDfromStudentFile(intToken, students);
            }
            if (order == TEAM_FIELD_ORDER::QA)
            {
                intToken = stringToInt(token);
                team.qaEngineer = getIDfromStudentFile(intToken, students);
            }
            i++;
        } while (line.find(',') != string::npos);
        teams.push_back(team);
    }
    teamsList.clear();
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
void insertTeamsIntoFile(vector<TEAM> teams, fstream& file) {
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


bool cmpStudentsByGrades(STUDENT first, STUDENT second)
{
    return first.grade < second.grade;
}

void insertTeacher(TEACHER teacher, fstream& file, string id)
{
    string line;
    line += '\n' +id+","+ teacher.name + "," + teacher.surrname + "," + teacher.mail + ",";
    for (size_t i = 0; i < teacher.teamsMentored.size(); i++)
    {
        line += to_string(teacher.teamsMentored[i].id) + ";";
    }
    line += ",";
    file.seekp(-1, ios_base::end);
    file << ",";
    file << line;
    file.seekp(ios_base::beg);
}
void insertTeachersIntoFile(vector<TEACHER> teachers, fstream& file)
{
    string id;
    int intId;
    for (size_t i = 0; i < teachers.size(); i++)
    {
        getLastId(id, file);
        intId = stringToInt(id);
        intId++;
        id = to_string(intId);
        insertTeacher(teachers[i], file, id);
    }
}

vector<TEACHER> getTeachersFromFile(fstream& file, vector<TEAM> teams) {
    file.clear();
    file.seekp(ios_base::beg);
    file.seekg(ios_base::beg);
    vector<TEACHER> teachers;
    string line, token, tokenId;
    size_t comaIndex = 0;
    TEACHER_FIELD_ORDER order;
    int intToken;
    size_t i = 0;
    while (getline(file, line)) {
        i = 0;
        TEACHER teacher;
        comaIndex = line.find(',');
        token = line.substr(0, comaIndex);
        if (token == "0") continue;
        teacher.id = stringToInt(token);
        line = line.substr(comaIndex + 1, line.size() - comaIndex - 1);
        do {
            comaIndex = line.find(',');
            token = line.substr(0, comaIndex);
            line = line.substr(comaIndex + 1, line.size() - comaIndex - 1);
            order = (TEACHER_FIELD_ORDER)i;
            if (order == TEACHER_FIELD_ORDER::TEACHERNAME) {
                teacher.name = token;
            }
            if (order == TEACHER_FIELD_ORDER::TEACHERSURNAME) {
                teacher.surrname = token;
            }
            if (order == TEACHER_FIELD_ORDER::TEACHERMAIL) {
                teacher.mail = token;
            }
            if (order == TEACHER_FIELD_ORDER::MENTORED_TEAMS_IDS) {
                do {
                    comaIndex = token.find(';');
                    tokenId = token.substr(0, comaIndex);
                    token = token.substr(comaIndex + 1, token.size() - comaIndex - 1);
                    intToken = stringToInt(tokenId);
                    teacher.teamsMentored.push_back(getIdfromTeacherFile(intToken, teams));
                } while (token.find(';') != string::npos);
            }
            i++;
        } while (line.find(',') != string::npos);
        teachers.push_back(teacher);
    }
    file.clear();
    file.seekp(ios_base::beg);
    file.seekg(ios_base::beg);
    return teachers;
}

vector<STUDENT> getStudentsFromTeams(vector<TEAM> teams)
{
    vector<STUDENT> students;
    for (size_t i = 0; i < teams.size(); i++)
    {
        students.push_back(teams[i].backEnd);
        students.push_back(teams[i].qaEngineer);
        students.push_back(teams[i].scrumMaster);
        students.push_back(teams[i].frontEnd);
    }
    sort(students.begin(), students.end(), cmpStudentsAlphabetically);
    students.erase(unique(students.begin(), students.end()), students.end());
    return students;
}
void deleteTakenStudents(vector<STUDENT>& studentsFromFile, vector<STUDENT>& studentsFromTeams) {
    vector<STUDENT>::iterator it;
    for (size_t i = 0; i < studentsFromFile.size(); i++) {
        for (size_t j = 0; j < studentsFromTeams.size(); j++)
        {
            if (studentsFromFile[i] == studentsFromTeams[j])
            {
                it = studentsFromFile.begin();
                advance(it, i);
                i--;
                studentsFromFile.erase(it);
                break;
            }
        }
    }
}
void distributeTeamMembers(TEAM& team, vector<STUDENT>& students) {
    vector<STUDENT>::iterator it;
    if (students.size() == 1)
    {
        team.backEnd = students[0];
        team.frontEnd = students[0];
        team.scrumMaster = students[0];
        team.qaEngineer = students[0];
        it = students.begin();
        students.erase(it);
        return;
    }
    it = students.begin();
    advance(it, randomInt(0, students.size()));
    team.backEnd = *it;
    students.erase(it);
    if (students.size() == 1)
    {
        team.frontEnd = students[0];
        team.scrumMaster = students[0];
        team.qaEngineer = students[0];
        it = students.begin();
        students.erase(it);
        return;
    }
    it = students.begin();
    advance(it, randomInt(0, students.size()));
    team.frontEnd = *it;
    students.erase(it);
    if (students.size() == 1)
    {
        team.scrumMaster = students[0];
        team.qaEngineer = students[0];
        it = students.begin();
        students.erase(it);
        return;
    }
    it = students.begin();
    advance(it, randomInt(0, students.size()));
    team.scrumMaster = *it;
    students.erase(it);
    it = students.begin();
    advance(it, randomInt(0, students.size()));
    team.qaEngineer = *it;
    students.erase(it);

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