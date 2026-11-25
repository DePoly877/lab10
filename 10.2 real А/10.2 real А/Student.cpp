// Student.cpp – IMPLEMENTATION of the module
#include "Student.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ================= helpers =================

string SpecialtyToString(const Specialty specialty)
{
    switch (specialty)
    {
    case COMPUTER_SCIENCE:        return "Комп'ютерні науки";
    case INFORMATICS:             return "Інформатика";
    case MATH_AND_ECONOMICS:      return "Математика та економіка";
    case PHYSICS_AND_INFORMATICS: return "Фізика та інформатика";
    case LABOR_TRAINING:          return "Трудове навчання";
    }
    return "";
}

double GetAverageGrade(const Student& student)
{
    return (student.physicsGrade + student.mathGrade + student.informaticsGrade) / 3.0;
}

// ================= comparison =================

int CompareAverages(const double first, const double second)
{
    const double EPSILON = 0.005;   // averages are compared with accuracy 0.01
    if (fabs(first - second) < EPSILON)
        return 0;
    return first < second ? -1 : 1;
}

int CompareKeys(const double firstAverage, const int firstInformatics, const string& firstSurname,
    const double secondAverage, const int secondInformatics, const string& secondSurname,
    const bool surnameDescending)
{
    int result = CompareAverages(firstAverage, secondAverage);
    if (result != 0)
        return result;

    if (firstInformatics != secondInformatics)
        return firstInformatics < secondInformatics ? -1 : 1;

    int surnameResult = firstSurname.compare(secondSurname);
    if (surnameResult < 0) surnameResult = -1;
    else if (surnameResult > 0) surnameResult = 1;

    return surnameDescending ? -surnameResult : surnameResult;
}

int CompareStudents(const Student& first, const Student& second, const bool surnameDescending)
{
    return CompareKeys(GetAverageGrade(first), first.informaticsGrade, first.surname,
        GetAverageGrade(second), second.informaticsGrade, second.surname,
        surnameDescending);
}

// ================= sorting and searching =================

void SortPhysically(Student* students, const int count)
{
    Student temp;
    for (int pass = 0; pass < count - 1; pass++)            // bubble sort
        for (int i = 0; i < count - pass - 1; i++)
            if (CompareStudents(students[i], students[i + 1], true) > 0)
            {
                temp = students[i];
                students[i] = students[i + 1];
                students[i + 1] = temp;
            }
}

int* BuildSortedIndex(const Student* students, const int count)
{
    int* index = new int[count];
    for (int i = 0; i < count; i++)
        index[i] = i;

    int temp;
    for (int pass = 0; pass < count - 1; pass++)
        for (int i = 0; i < count - pass - 1; i++)
            if (CompareStudents(students[index[i]], students[index[i + 1]], false) > 0)
            {
                temp = index[i];
                index[i] = index[i + 1];
                index[i + 1] = temp;
            }
    return index;
}

int BinarySearch(const Student* students, const int count,
    const string& surname, const double averageGrade, const int informaticsGrade)
{
    int left = 0, right = count - 1;
    while (left <= right)
    {
        int middle = left + (right - left) / 2;
        int result = CompareKeys(GetAverageGrade(students[middle]), students[middle].informaticsGrade,
            students[middle].surname,
            averageGrade, informaticsGrade, surname,
            true);     // the array is sorted with surnames in descending order
        if (result == 0)
            return middle;
        if (result < 0)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return -1;
}

// ================= output =================

// =============== output ===============

static string PadRight(const string& str, int width)
{
    int visualLength = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        unsigned char c = static_cast<unsigned char>(str[i]);
        if ((c == 0xD0 || c == 0xD1) && i + 1 < str.length())
        {
            visualLength++;
            i++;
        }
        else
        {
            visualLength++;
        }
    }
    if (visualLength >= width)
        return str;
    return str + string(width - visualLength, ' ');
}

static const char* TABLE_LINE =
"=================================================================================================";

static void PrintTableHeader()
{
    cout << "                                        Список студентів" << endl;
    cout << TABLE_LINE << endl;
    cout << "| №   | Прізвище        | Курс | Спеціальність           | Фізика  | Математика  | Інформатика  |" << endl;
    cout << TABLE_LINE << endl;
}

static void PrintTableRow(const Student& student, const int number)
{
    cout << "| " << setw(3) << right << number << " "
        << "| " << PadRight(student.surname, 16)
        << "| " << setw(4) << right << student.course << " "
        << "| " << PadRight(SpecialtyToString(student.specialty), 24)
        << "| " << setw(7) << right << student.physicsGrade << " "
        << "| " << setw(11) << right << student.mathGrade << " "
        << "| " << setw(12) << right << student.informaticsGrade << " |" << endl;
}

void PrintStudents(const Student* students, const int count)
{
    PrintTableHeader();
    for (int i = 0; i < count; i++)
        PrintTableRow(students[i], i + 1);
    cout << "=================================================================================================" << endl << endl;
}

void PrintStudentsByIndex(const Student* students, const int* index, const int count)
{
    PrintTableHeader();
    for (int i = 0; i < count; i++)
        PrintTableRow(students[index[i]], i + 1);
    cout << "=================================================================================================" << endl << endl;
}