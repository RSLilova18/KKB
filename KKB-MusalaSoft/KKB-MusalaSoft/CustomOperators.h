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
#include "CustomDataTypes.h" 

using namespace std;

bool operator==(const STUDENT& firstStud, const STUDENT& secondStud)
{
    return firstStud.mail == secondStud.mail;
}

bool operator==(const TEAM& firstTeam, const TEAM& secondTeam)
{
    return firstTeam.name == secondTeam.name;
}