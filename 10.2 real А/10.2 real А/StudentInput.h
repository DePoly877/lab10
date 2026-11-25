// StudentInput.h – INTERFACE of the module for validated keyboard input
#pragma once
#include <string>
#include "Student.h"

using namespace std;

// each function repeats the prompt until the user enters a correct value
int    ReadIntInRange(const string& prompt, const int minValue, const int maxValue);
double ReadDoubleInRange(const string& prompt, const double minValue, const double maxValue);
string ReadSurname(const string& prompt);

// fills the array with data entered from the keyboard
void FillStudents(Student* students, const int count);