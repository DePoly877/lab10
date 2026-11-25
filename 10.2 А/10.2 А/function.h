// модуль: типи даних та оголошення функцій
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

// третій предмет залежить від спеціальності
enum ThirdSubject
{
    PROGRAMMING,        // for COMPUTER_SCIENCE
    NUMERICAL_METHODS,  // for INFORMATICS
    PEDAGOGY            // for all other specialties
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
    union                       //третя оцінка залежить від спеціальності
    {
        int programmingGrade;       // COMPUTER_SCIENCE
        int numericalMethodsGrade;  // INFORMATICS
        int pedagogyGrade;          // всі решта
    };
};

// ---------- допоміжні ----------
string       SpecialtyToString(const Specialty specialty);
ThirdSubject GetThirdSubject(const Specialty specialty);
int          GetThirdGrade(const Student& student);
double       GetAverageGrade(const Student& student);

// ---------- порівняння ----------
// порівнює два середні значення з точністю 0.01 (-1, 0, 1)
int CompareAverages(const double first, const double second);
// порівнює за ключами: середній бал, третій клас, прізвище (-1, 0, 1)
int CompareKeys(const double firstAverage, const int firstThirdGrade, const string& firstSurname,
    const double secondAverage, const int secondThirdGrade, const string& secondSurname,
    const bool surnameDescending);
int CompareStudents(const Student& first, const Student& second, const bool surnameDescending);

// ---------- сортування та пошук ----------
// фізичне сортування: за середнім значенням (за зростанням), за третім класом (за зростанням), за прізвищем (за спаданням)
void SortPhysically(Student* students, const int count);
// сортування індексу: за середнім значенням (за зростанням), за третім класом (за зростанням), за прізвищем (за зростанням);
// повертає новий масив (викликаюча сторона повинна виконати delete[] для нього)
int* BuildSortedIndex(const Student* students, const int count);
// бінарний пошук у фізично відсортованому масиві; повертає позицію або -1
int BinarySearch(const Student* students, const int count,
    const string& surname, const double averageGrade, const int thirdGrade);

// ---------- вивід ----------
void PrintStudents(const Student* students, const int count);
void PrintStudentsByIndex(const Student* students, const int* index, const int count);