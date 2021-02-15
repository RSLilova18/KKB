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

bool menu(fstream& studsFile, fstream& teachersFile, fstream& teamsFile,fstream& schoolFile) {
    cout << "......................................................." << endl;
    cout << ". 1. See all schools list                             ." << endl;
    cout << ". 2. Choose a school to work with                     ." << endl;
    cout << ". 3.Enter a new school.                               ." << endl;
    cout << ". 4.Enter a new students in the list                  ." << endl;
    cout << ". 5.Enter a new teacher in the list                   ." << endl;
    cout << ". 6.Delete an already existing student from the list  ." << endl;
    cout << ". 7.Delete an already existint teacher from the list  ." << endl;
    cout << ". 8. Delete an already existing team from the list    ." << endl;
    cout << ". 9. Set a team satus                                 ." << endl;
    cout << ". 10. Display all students                            ." << endl;
    cout << ". 11. Display all teams                               ." << endl;
    cout << ". 12. Display all teachers                             ." << endl;
    cout << ". 13. Sort the students by grade                      ." << endl;
    cout << ". 14.Alphabetical distribution                        ." << endl;
    cout << ". 15.Random distribution                              ." << endl;
    cout << ". 16.Exit                                             ." << endl;
    cout << "......................................................." << endl;
    cout << endl;



    int option,numberOfStudents;
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
        cin >> schoolDirectory;
        setSchoolDirectory(schoolDirectory);
        closeFiles(studsFile, teachersFile, teamsFile, schoolFile);
        openFiles(studsFile, teachersFile, teamsFile, schoolFile, schoolDirectory);
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
    }
    if (option == 4)
    {
        do {
            cout << "How Many students do you want to enter? You can only enter positive numbers: " << endl;
            numberOfStudents = readInt();
        } while (numberOfStudents <= 0);
        if (!schoolDirectory.empty())
        {
            vector<STUDENT> students = enterStudents(numberOfStudents);
            printInsertStudents(students, studsFile);
        }
        else {
            cout<< "No school is selected. Select a school from the list or enter a new school!" << endl;
        }
    }
    if (option == 16)
    {
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

