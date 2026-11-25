// Student.h – INTERFACE of the module: data types and function declarations
#pragma once
#include <string>

using namespace std;

enum Specialty
{
    COMPUTER_SCIENCE,         // Комп'ютерні науки
    INFORMATICS,              // Інформатика
    MATH_AND_ECONOMICS,       // Математика та економіка
    PHYSICS_AND_INFORMATICS,  // Фізика та інформатика
    LABOR_TRAINING            // Трудове навчання
};

const int MIN_GRADE = 1;
const int MAX_GRADE = 5;
const int MIN_COURSE = 1;
const int MAX_COURSE = 6;

struct Student
{
    string    surname;
    int       course;
    Specialty specialty;
    int       physicsGrade;
    int       mathGrade;
    int       informaticsGrade;     // the third subject
};

// ---------- helpers ----------
string SpecialtyToString(const Specialty specialty);
double GetAverageGrade(const Student& student);

// ---------- comparison ----------
// compares two averages with accuracy 0.01 (-1, 0, 1)
int CompareAverages(const double first, const double second);
// compares by keys: average grade, informatics grade, surname (-1, 0, 1)
int CompareKeys(const double firstAverage, const int firstInformatics, const string& firstSurname,
    const double secondAverage, const int secondInformatics, const string& secondSurname,
    const bool surnameDescending);
int CompareStudents(const Student& first, const Student& second, const bool surnameDescending);

// ---------- sorting and searching ----------
// physical sorting: average (asc), informatics grade (asc), surname (desc)
void SortPhysically(Student* students, const int count);
// index sorting: average (asc), informatics grade (asc), surname (asc);
// returns a new array (the caller must delete[] it)
int* BuildSortedIndex(const Student* students, const int count);
// binary search in the physically sorted array; returns position or -1
int BinarySearch(const Student* students, const int count,
    const string& surname, const double averageGrade, const int informaticsGrade);

// ---------- output ----------
void PrintStudents(const Student* students, const int count);
void PrintStudentsByIndex(const Student* students, const int* index, const int count);