#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cmath>
#include <fstream>
#include "CustomDataTypes.h" 

using namespace std;

bool operator==(const STUDENT& firstStud, const STUDENT& secondStud)
{
    return firstStud.mail == secondStud.mail;
}