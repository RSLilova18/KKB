#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include "CustomDataTypes.h" 
#include "CustomOperators.h"
#include "DataLayerFunctions.h" 
#include "DisplayFunctions.h" 
#include "FilterFunctions.h"
#include "FunctionsFromCustomDataTypes.h"

using namespace std;

string schoolDirectory;

void insertTeacher(TEACHER teacher, fstream& file, string id)
{

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
		if (verifySelectedSchool(schoolDirectory))
		{
			setSchoolDirectory(schoolDirectory);
            closeFiles(studsFile, teachersFile, teamsFile, schoolFile);
            openFiles(studsFile, teachersFile, teamsFile, schoolFile, schoolDirectory);
			studsFile.flush();
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
        setSchoolDirectory(schoolDirectory);
        closeFiles(studsFile, teachersFile, teamsFile, schoolFile);
        openFiles(studsFile, teachersFile, teamsFile, schoolFile, schoolDirectory);
        insertStudentsIntoFile(school.students, studsFile);
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
    if (option == 17)
    {
        closeFiles(studsFile, teachersFile, teamsFile, schoolFile);
        return false;
    }
    
    return true;
}
//dir /B | findstr /v /i "template" |findstr /v /i "BACKUP"

int main()
{
    fstream studs, teachers, teams, school;
    while (menu(studs, teachers, teams, school));
 
}

