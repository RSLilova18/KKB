#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <cmath>
#include <windows.h>
#include <fstream>


using namespace std;


//Jobs hierarchy
struct STUDENT 
{
    string name, surname, role, mail, nameClass;
    int classStudent;
    float grade;

    void enterData(int counterStudent = 1) 
    {
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

    void printStudent() {
        cout << endl;
        cout << "--------------------------------------------------------------------------------";
        cout << endl;
        cout << "--" << name << " " << surname << " " << classStudent << " " << nameClass;
        cout << endl;
        cout << "--" << "Role, grade and email: " << role <<" "<< grade << " - " << mail;
        cout << endl;
        cout << "--------------------------------------------------------------------------------";
        cout << endl;
    }
};

bool operator==(const STUDENT& firstStud, const STUDENT& secondStud)
{
    return firstStud.mail == secondStud.mail;
}

bool checkIfStudentExist(STUDENT& student, vector<STUDENT> studentsList) {
    string role;
    role = student.role;
    for (size_t i = 0; i < studentsList.size();i++)
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


struct TEAM 
{
    string name, description, date, status;
    STUDENT scrumMaster;
    STUDENT backEnd;
    STUDENT frontEnd;
    STUDENT qaEngineer;

    static STUDENT enterStudentData() {
        STUDENT student;
        cout << "--Enter student mail: ";
        cin >> student.mail;
        return student;
    }

    void enterTeamData(vector<STUDENT> students, int teamNumber=1) {
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
        studentValidationPrint(backEnd,students,"OK, now enter the data for a backend: ");
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
    void studentValidationPrint(STUDENT& student, vector<STUDENT> studentsList, string msg) {
        while (!checkIfStudentExist(student, studentsList)) {
            cout << endl;
            cout << "This student does not exist! Try again!" << endl;
            cout << endl;
            cout << msg << endl;
            student = TEAM::enterStudentData();
        }
    }
    void printTeam() 
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
};

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

struct TEACHER {
    string name, surrname, mail;
    vector<string> teamNames;

    void enterTeacherData(vector<TEAM> teams, int teacherNumberCount =1) {
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

    void printTeacherData() {
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
};

struct SCHOOL {
    string name, city, address;
    vector<TEACHER> teachers;
    vector<TEAM> teams;
    vector<STUDENT> students;
};

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

//template
bool checkStudentsData(STUDENT data, int counterStudent = 1)
{
    return !(data.grade > 6 or data.grade < 2);
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



vector<TEAM> enterTeams(int numberOfTeams,vector<STUDENT> students) {
    TEAM team;
    vector<TEAM> teams;
    for (int i = 0; i < numberOfTeams; i++)
    {
        team.enterTeamData(students,i + 1);
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
    getline(cin,school.address);
    cout << "Enter the number of students in " << school.city << ": ";
    cin >> numberOfStudents;
    school.students = enterStudents(numberOfStudents);
    cout << endl;
    cout << "Enter the number of the teams in the school: ";
    cin >> numberOfTeams;
    school.teams = enterTeams(numberOfTeams,school.students);
    cout << "Enter the number of teachers in the school: ";
    cin >> numberOfTeachers;
    school.teachers = enterTeachers(numberOfTeachers, school.teams);

    return school;
}

bool menu() {
    cout << ".................................................." << endl;
    cout << "1.Enter a new school." << endl;
    cout << "2.Enter a new students in the list" << endl;
    cout << "3.Enter a new teacher in the list" << endl;
    cout << "4.Delete an already exist student from the list" << endl;
    cout << "5.Delete an already exist teacher from the list" << endl;
    cout << "6.Alphabetical distribution" << endl;
    cout << "7.Rnadom distribution" << endl;
    cout << ".................................................." << endl;
    
    cout << endl;

    int option;
    cout << "Please enter your option here -> ";
    cin >> option;


    /*while (checkStudentsData(students) == false)
    {
        enterStudentsData(students);
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
