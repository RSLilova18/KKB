#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include "CustomDataTypes.h" 
#include "CustomOperators.h"
#include "DataLayerFunctions.h" 
#include "DisplayFunctions.h" 
#include "FilterFunctions.h"
#include "FunctionsFromCustomDataTypes.h"

using namespace std;

bool menu() {
    cout << ".................................................." << endl;
    cout << "1.Enter a new school." << endl;
    cout << "2.Enter a new students in the list" << endl;
    cout << "3.Enter a new teacher in the list" << endl;
    cout << "4.Delete an already exist student from the list" << endl;
    cout << "5.Delete an already exist teacher from the list" << endl;
    cout << "6.Display a school data" << endl;
    cout << "7.Go to reports menu" << endl; 
    cout << "8.Alphabetical distribution" << endl;
    cout << "9.Random distribution" << endl;
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
