#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include <string>
#include "CustomDataTypes.h" 
#include "CustomOperators.h"
#include "DataLayerFunctions.h" 
#include "DisplayFunctions.h" 
#include "FilterFunctions.h"
#include "FunctionsFromCustomDataTypes.h"

using namespace std;

string schoolDirectory;
enum STUDENT_FIELD_ORDER {
	NAME,
	SURRNAME,
	CLASS_STUDENT,
	CLASS_NAME,
	GRADE,
	MAIL
};
vector<STUDENT> getStudentsFromFile(fstream &studentsList) {
	vector<STUDENT> students;
	string line,segment;
	size_t comaIndex = 0;
	STUDENT_FIELD_ORDER order;
	size_t i = 0;
	while (getline(studentsList, line)) {
		i = 0;
		STUDENT student;
		comaIndex = line.find(',');
		segment = line.substr(0, comaIndex);
		if (segment == "0") continue;
		line = line.substr(comaIndex + 1, line.size() - comaIndex - 1);
		do {
			comaIndex = line.find(',');
			segment = line.substr(0, comaIndex);
			line = line.substr(comaIndex + 1, line.size() - comaIndex - 1);
			order = (STUDENT_FIELD_ORDER)i;
			if (order == NAME)
			{
				student.name = segment;
			}
			if (order == SURRNAME)
			{
				student.surname = segment;
			}
			if (order == MAIL)
			{
				student.mail = segment;
			}
			if (order == CLASS_NAME)
			{
				student.nameClass = segment;
			}
			if (order == CLASS_STUDENT)
			{
				student.classStudent = stringToInt(segment);
			}
			if (order == GRADE)
			{
				student.grade = stof(segment);
			}
			i++;
		} while (line.find(',') != string::npos);
		students.push_back(student);
	}
	return students;
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
    cout << ". 11. Display all students                            ." << endl;
    cout << ". 12. Display all teams                               ." << endl;
    cout << ". 13. Display all teachers                            ." << endl;
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
        setSchoolDirectory(schoolDirectory);
        closeFiles(studsFile, teachersFile, teamsFile, schoolFile);
        openFiles(studsFile, teachersFile, teamsFile, schoolFile, schoolDirectory);
        studsFile.flush();
    }
    if (option == 3)
    {
        SCHOOL school = enterSchoolData();
        schoolDirectory = school.name + " " + school.city;
        createSchoolFolder(schoolDirectory);
        setSchoolDirectory(schoolDirectory);
        closeFiles(studsFile, teachersFile, teamsFile, schoolFile);
        openFiles(studsFile, teachersFile, teamsFile, schoolFile, schoolDirectory);
        printInsertStudents(school.students, studsFile);
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
            printInsertStudents(students, studsFile);
            studsFile.flush();
        }
        else {
            cout<< "No school is selected. Select a school from the list or enter a new school!" << endl;
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
			printStudentsData(students);
			//vector<TEAM> teams = enterTeams(enterable,students);
		}
		else {
			cout << "No school is selected. Select a school from the list or enter a new school!" << endl;
		}
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

