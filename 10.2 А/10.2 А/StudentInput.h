// інтерфейс модуля для перевірки введених з клавіатури даних
#pragma once
#include <string>
#include "function.h"

using namespace std;

// кожна функція повторює запит, доки користувач не введе правильне значення
int    ReadIntInRange(const string& prompt, const int minValue, const int maxValue);
double ReadDoubleInRange(const string& prompt, const double minValue, const double maxValue);
string ReadSurname(const string& prompt);

// заповнює масив даними, введеними з клавіатури
void FillStudents(Student* students, const int count);