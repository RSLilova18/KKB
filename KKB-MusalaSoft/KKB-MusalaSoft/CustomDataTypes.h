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


using namespace std;

struct STUDENT
{
    int id;
    string name, surname, role, mail, nameClass;
    int classStudent;
    float grade;

    void enterData(int counterStudent);
    void printStudent();
};

struct TEAM
{
    int id;
    string name, description, date, status;
    STUDENT scrumMaster;
    STUDENT backEnd;
    STUDENT frontEnd;
    STUDENT qaEngineer;

    static STUDENT enterStudentData();
    void enterTeamData(vector<STUDENT> students, int teamNumber);
    void studentValidationPrint(STUDENT& student, vector<STUDENT> studentsList, string msg);
    void printTeam();
};

struct TEACHER {
    int id;
    string name, surrname, mail;
    vector<TEAM> teamsMentored;

    static TEAM enterTeamData();
    void teamValidationPrint(TEAM& team, vector<TEAM> teamList);
    void enterTeacherData(vector<TEAM> teams, int teacherNumberCount);
    void printTeacherData();
};

struct SCHOOL {
    string name, city, address;
    vector<TEACHER> teachers;
    vector<TEAM> teams;
    vector<STUDENT> students;  
};

enum STUDENT_FIELD_ORDER {
    NAME,
    SURNAME,
    CLASS_STUDENT,
    CLASS_NAME,
    GRADE,
    MAIL
};


enum TEAM_FIELD_ORDER
{
    TEAMNAME,
    DESCRIPTION,
    TEAMDATE,
    BACKEND,
    FRONTEND,
    SCRUM,
    QA,
    STATUS
};

enum  TEACHER_FIELD_ORDER {
    TEACHERNAME,
    TEACHERSURNAME,
    TEACHERMAIL,
    MENTORED_TEAMS_IDS
};