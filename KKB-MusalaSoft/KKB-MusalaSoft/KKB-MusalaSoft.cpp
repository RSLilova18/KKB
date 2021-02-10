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
    float grade;
};

struct TEAM {
    string name, description, date, status;
    vector<STUDENT> students;
};

struct TEACHER {
    string name, surrname, mail;
    vector<string> teamNames;
};

struct SCHOOL {
    string name, city, address;
    vector<TEACHER> teachers;
    vector<TEAM> teams;
    vector<STUDENT> students;
};

void printStudentsData(vector <STUDENT> data)
{
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    for (size_t i = 0; i < data.size(); i++)
    {
        cout << data[i].name << " " << data[i].surname << " " << data[i].classStudent << " " << data[i].nameClass;
        cout << endl;
        cout << "Role, grade and email: " << data[i].role << data[i].grade << " - " << data[i].mail;
        cout << endl;
        cout << "--------------------------------------------------------------------------------";
        cout << endl;
    }
}

void printTeamsData(vector<TEAM> data)
{
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    for (size_t i = 0; i < data.size(); i++)
    {
        cout << data[i].name;
        cout << endl;
        cout << data[i].description;
        cout << endl;
        cout << data[i].date;
        cout << endl << endl;
        cout << "The students of the team: " << endl;
        printStudentsData(data[i].students);
    }
    cout << "--------------------------------------------------------------------------------" << endl;
}

void printTeachersData(vector<TEACHER> data)
{
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    for (size_t i = 0; i < data.size(); i++)
    {
        cout << data[i].name << " " << data[i].surrname;
        cout << endl;
        cout << "Email: " << data[i].mail;
        cout << endl;
        for (size_t j = 0; j < data[i].teamNames.size(); j++)
        {
            cout << j + 1 << ". Team name : " << data[i].teamNames[j] << endl;
        }
        cout << "--------------------------------------------------------------------------------";
        cout << endl;
    }
}

//template
bool checkStudentsData(STUDENT data, int counterStudent = 1)
{

    if (data.grade > 6 or data.grade < 2)
    {
        return false;
    }
    else
    {
        return true;
    }


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
STUDENT enterStudentData(int counterStudent = 1)
{
    STUDENT student;


    cout << endl;
    cout << counterStudent << ".Enter student name: ";
    cin >> student.name;
    cout << counterStudent << ".Enter student surname: ";
    cin >> student.surname;
    cout << counterStudent << ".Enter student class: ";
    cin >> student.classStudent;
    cout << counterStudent << ".Enter student class name: ";
    cin >> student.nameClass;
    cout << counterStudent << ".Enter student grade: ";
    cin >> student.grade;
    cout << counterStudent << ".Enter student role: ";
    cin >> student.role;
    cout << counterStudent << ".Enter student mail: ";
    cin >> student.mail;


    return student;
}

vector<STUDENT> enterStudents(int numberOfStudents) {
    STUDENT student;
    vector<STUDENT> students;
    for (int i = 0; i < numberOfStudents; i++)
    {
        student = enterStudentData(i + 1);
        while (checkStudentsData(student) == false)
        {
            cout << "Invalid grade!" << endl;
            student = enterStudentData(i + 1);

        }
        students.push_back(student);
    }
    return students;
}

TEAM enterTeam(int teamNumber = 1) {
    TEAM team;
    int MembersCount;
    cout << teamNumber << ".Enter team name: ";
    cin >> team.name;
    cout << teamNumber << ".Enter team description: ";
    cin.ignore();
    getline(cin, team.description);
    cout << teamNumber << ".Enter team creation date: ";
    cin >> team.date;
    cout << teamNumber << ".Enter the number of team members: ";
    cin >> MembersCount;

    cout << "Now Enter your students for the team: " << endl << endl;
    team.students = enterStudents(MembersCount);
    return team;
}

vector<TEAM> enterTeams(int numberOfTeams) {
    TEAM team;
    vector<TEAM> teams;
    for (int i = 0; i < numberOfTeams; i++)
    {
        team = enterTeam(i + 1);
        teams.push_back(team);
    }
    return teams;
}

bool checkIfTeamNameIsValid(string name, vector<TEAM> teams)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (name == teams[i].name)
        {
            return true;
        }
    }
    return false;
}

TEACHER enterTeacher(vector<TEAM> teams, int teacherNumberCount = 1) {
    TEACHER teacher;
    int teamsMentoredCount;
    string nameTeamTemp;
    cout << teacherNumberCount << ".Enter teacher name: ";
    cin >> teacher.name;
    cout << teacherNumberCount << ".Enter teacher surname: ";
    cin >> teacher.surrname;
    cout << teacherNumberCount << ".Enter teacher mail: ";
    cin >> teacher.mail;

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
        teacher.teamNames.push_back(nameTeamTemp);
    }
    return teacher;
}

vector<TEACHER> enterTeachers(int numberOfTeachers, vector<TEAM> teams) {
    TEACHER teacher;
    vector<TEACHER> teachers;
    for (int i = 0; i < numberOfTeachers; i++)
    {
        teacher = enterTeacher(teams, i + 1);
        teachers.push_back(teacher);
    }
    return teachers;
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
    cin >> school.address;
    cout << "Enter the number of students in " << school.city << ": ";
    cin >> numberOfStudents;
    school.students = enterStudents(numberOfStudents);
    cout << "Enter the number of the teams in the school: ";
    cin >> numberOfTeams;
    school.teams = enterTeams(numberOfTeams);
    cout << "Enter the number of teachers in the school: ";
    cin >> numberOfTeachers;
    school.teachers = enterTeachers(numberOfTeachers, school.teams);

    return school;
}

bool menu() {

    /*while (checkStudentsData(students) == false)
    {
        //enterStudentsData(students, numberOfStudents);
    }*/
    return false;

}


int main()
{
    //while (menu());
     
    SCHOOL sch = enterSchoolData();
    cout << "School city: ";
    cout << sch.city << endl;
    cout << "School name: ";
    cout << sch.name << endl;
    cout << "School address: ";
    cout << sch.address << endl;

    cout << endl << "Students data: " << endl << endl;
    printStudentsData(sch.students);
    cout << "Teams data: " << endl << endl;
    printTeamsData(sch.teams);
    cout << "Teachers data: " << endl << endl;
    printTeachersData(sch.teachers);




    /*fstream studs, teachers, teams, schools;
    string a, b;
    studs.open("students.csv", ios::app);
    teachers.open("teachers.csv", ios::app);
    teams.open("teams.csv", ios::app);
    schools.open("schools.csv", ios::app);


    studs.close();
    teachers.close();
    teams.close();
    schools.close();*/

}



/*bobo
dimitrov
10
v
backend
BDD
valco
petrov
10
g
front
VPP*/


/*Burgas
Chintulov
Izgrev
3
Valentin
Petrov
10
G
5.20
frontend
VPP
Raq
Lilova
10
B
4.5
codebreaker
RSL
Bojidar
Dimitrov
10
V
5.9
backend
BDD
2
Strong
We are the strongest
10.02.2021
Valentin
Petrov
10
G
5.20
frontend
VPP
Raq
Lilova
10
B
4.5
codebreaker
RSL
Strong2
We are the strongest
10.02.2021
1
Bojidar
Dimitrov
10
V
5.9
backend
BDD
2
Goshko
Petrov
GPP
1
Strong
Goshko1
Petrov1
GPP1
1
Strong2*/