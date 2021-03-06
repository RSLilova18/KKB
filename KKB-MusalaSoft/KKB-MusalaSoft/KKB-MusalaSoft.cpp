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
#include "DisplayFunctions.h" 
#include "FilterFunctions.h"
#include "FunctionsFromCustomDataTypes.h"
#include "GlobalVariables.h"

using namespace std;


bool menu(fstream& studsFile, fstream& teachersFile, fstream& teamsFile,fstream& schoolFile) {
    cout << "......................................................." << endl;
    cout << ". 1. See all schools list                             ." << endl;
    cout << ". 2. Choose a school to work with                     ." << endl;
    cout << ". 3.Enter a new school.                               ." << endl;
    cout << ". 4.Enter a new students in the list                  ." << endl;
    cout << ". 5.Enter a new teacher in the list                   ." << endl;
	cout << ". 6.Enter a new team in the list                      ." << endl;
    cout << ". 7.Delete an already existing student from the list  ." << endl;
    cout << ". 8.Delete an already existint teacher from the list  ." << endl;
    cout << ". 9. Delete an already existing team from the list    ." << endl;
    cout << ". 10. Set a team satus                                ." << endl;
    cout << ". 11. Display all students in the current school      ." << endl;
    cout << ". 12. Display all teams in the current school         ." << endl;
    cout << ". 13. Display all teachers in the current school      ." << endl;
    cout << ". 14. Sort the students by grade                      ." << endl;
    cout << ". 15.Alphabetical distribution                        ." << endl;
    cout << ". 16.Random distribution                              ." << endl;
    cout << ". 17.Exit                                             ." << endl;
    cout << "......................................................." << endl;
    cout << endl;



    int option, enterable;
    cout << "Please enter your option here -> ";
    //Enters the option we want to work with
    option = readInt();
    cout << endl;
    
    if (option == 1)
    {
        showAllSchoolNames();
    }
    if (option == 2)
    {
        showAllSchoolNames();
        cout << endl;
        cout << "Enter the school you want to work with: ";
        cin.ignore();
        getline(cin, schoolDirectory);
		if (verifySelectedSchool(schoolDirectory))//checks if we have entered a valid school
		{
            //sets the working path
			setSchoolDirectory(schoolDirectory);
            //changes the streams
            closeFiles(studsFile, teachersFile, teamsFile, schoolFile);
            openFiles(studsFile, teachersFile, teamsFile, schoolFile, schoolDirectory);
			return true;
		}
		cout << endl;
		cout << "This school doesn't exist!" << endl;
		cout << "NO SCHOOL IS SELECTED!" << endl;

    }
    if (option == 3)
    {
        SCHOOL school = enterSchoolData();
        schoolDirectory = school.name + " " + school.city;

        createSchoolFolder(schoolDirectory);
        setSchoolDirectory(schoolDirectory);//sets the working path
        //changes the streams
        closeFiles(studsFile, teachersFile, teamsFile, schoolFile);
        openFiles(studsFile, teachersFile, teamsFile, schoolFile, schoolDirectory);
        insertStudentsIntoFile(school.students, studsFile);
        insertTeamsIntoFile(school.teams, teamsFile);
        insertTeachersIntoFile(school.teachers, teachersFile);
        studsFile.flush();
    }
    if (option == 4)
    {
        if (!schoolDirectory.empty())
        {
			do {
				cout << "How Many students do you want to enter? You can only enter positive numbers: " << endl;
				enterable = readInt();
			} while (enterable <= 0);
            vector<STUDENT> students = enterStudents(enterable);
            insertStudentsIntoFile(students, studsFile);
            studsFile.flush();
        }
        else {
            cout<< "No school is selected. Select a school from the list or enter a new school!" << endl;
        }
    }
    if (option == 5)
    {   
        if (!schoolDirectory.empty())
        {
            do{
                cout << "How many teachers do you want to enter?"<<endl;
                enterable = readInt();
            } while (enterable <= 0);
            
            vector<STUDENT> students=getStudentsFromFile(studsFile);
            vector<TEAM> teams = getTeamsFromFile(teamsFile,students);
            vector<TEACHER> teachers = enterTeachers(enterable,teams);
            printTeachersData(teachers);
            insertTeachersIntoFile(teachers, teachersFile);
        }
    }
	if (option == 6) 
	{
		if (!schoolDirectory.empty())
		{
			do {
				cout << "How many teams do you want to enter: ";
				enterable = readInt();
			} while (enterable <= 0);
			vector<STUDENT> students = getStudentsFromFile(studsFile);
			vector<TEAM> teams = enterTeams(enterable,students);       
            insertTeamsIntoFile(teams, teamsFile);
            teamsFile.flush();
		}
		else {
			cout << "No school is selected. Select a school from the list or enter a new school!" << endl;
		}
	}
    if (option == 7)
    {
        if (!schoolDirectory.empty())
        {
            deleteFromFile(studsFile, "/StudentFile.csv");
            return true;
        }
        cout << endl;
        cout << "No school is selected!" << endl;
        cout << endl;
    }
    if (option == 8)
    {
        if (!schoolDirectory.empty())
        {
            deleteFromFile(teachersFile, "/Teachers.csv");
        }
        cout << endl;
        cout << "No school is selected!" << endl;
        cout << endl;
    }
    if (option == 9)
    {
        if (!schoolDirectory.empty())
        {
            deleteFromFile(teamsFile, "/Teams.csv");
        }
        cout << endl;
        cout << "No school is selected!" << endl;
        cout << endl;
    }
    if (option == 10)
    {
        if (!schoolDirectory.empty())
        {
            changeTeamStatusMenu(teamsFile);
            return true;
        }
        cout << endl;
        cout << "No school is selected!" << endl;
        cout << endl;
    }
    if (option == 11)
    {
        if (!schoolDirectory.empty()) {
            cout << "Full list of students: ";
            vector<STUDENT> students = getStudentsFromFile(studsFile);
            printStudentsData(students);
            return true;
        }
        cout << endl;
        cout << "No school is selected!" << endl;
        cout << endl;
    }
    if (option == 12)
    {
        if (!schoolDirectory.empty()) {
            cout << "Full list of the teams: " << endl;
            vector<STUDENT> students = getStudentsFromFile(studsFile);
            vector<TEAM> teams = getTeamsFromFile(teamsFile,students);
            printTeamsData(teams);
            return true;
        }
        cout << endl;
        cout << "No school is selected!" << endl;
        cout << endl;
    }
    if (option == 13)
    {
        if (!schoolDirectory.empty()) {
            cout << "Full list of teachers: " << endl;
            vector<STUDENT> students = getStudentsFromFile(studsFile);
            vector<TEAM> teams = getTeamsFromFile(teamsFile,students);
            vector<TEACHER> teachers = getTeachersFromFile(teachersFile,teams);
            printTeachersData(teachers);
            return true;
        }
        cout << endl;
        cout << "No school is selected!" << endl;
        cout << endl;
    }
    if (option == 14)
    {
        if (!schoolDirectory.empty())
        {
            cout << "Full list of students which are sorted by their grades: " << endl;
            vector<STUDENT> students = getStudentsFromFile(studsFile);
            sort(students.begin(), students.end(), cmpStudentsByGrades);
            printStudentsData(students);
            return true;
        }
        cout << endl;
        cout << "No school is selected!" << endl;
        cout << endl;
    }
    if (option == 15)
    {
        if (!schoolDirectory.empty())
        {
            cout << "Full list of alphabetically sorted students: " << endl;
            vector<STUDENT> students = getStudentsFromFile(studsFile);
            sort(students.begin(), students.end(), cmpStudentsAlphabetically);
            printStudentsData(students);
            return true;
        }
        cout << endl;
        cout << "No school is selected!" << endl;
        cout << endl;
    }
    if (option == 16) {
        vector<STUDENT> students = getStudentsFromFile(studsFile);
        vector<TEAM> teams = getTeamsFromFile(teamsFile,students);
        vector<TEAM> randomTeams = randomDistributeTeams(teams,students);
        if (randomTeams.size() != 0)
        {
            insertTeamsIntoFile(randomTeams,teamsFile);
        }
    }
    if (option == 17)
    {
        closeFiles(studsFile, teachersFile, teamsFile, schoolFile);
        return false;
    }
    
    return true;
}

int main()
{
    blankStudent.mail = "emptyStudent-`*_";
    blankTeam.name = "emptyTeam-`*_";
    srand(time(NULL));
    fstream studs, teachers, teams, school;
    while (menu(studs, teachers, teams, school));
   
}

