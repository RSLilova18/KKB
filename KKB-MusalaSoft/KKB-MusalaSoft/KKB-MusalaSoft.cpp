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
    string name, surrname, role, mail, nameClass;
    int classStudent;
};

struct TEAM {
    string name, description, date, status;
    vector<STUDENT> students;
};

struct TEACHER {
    string name, surrname, mail;
    vector<TEAM> teams;
};

struct SCHOOL {
    string name, city, adress;
    vector<TEACHER> teachers;
    vector<TEAM> teams;
    vector<STUDENT> students;
};


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

bool menu() {
    return true;
}


int main()
{
    //while (menu());
    /*fstream file;
    string a,b;
    cin >> a >> b;
    a += ',' + b;

    file.open("example.csv", ios::app);
    file << a<<endl;
    file << "anton" << endl;
    file.close();*/

}


