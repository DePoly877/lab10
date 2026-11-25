// типи даних і прототипи функцій
#pragma once
#include <string>
#include <cstddef>

enum Specialnist { KN, IN, ME, FI, TN };
// KN - Комп'ютерні науки, IN - Інформатика, ME - Математика та економіка,
// FI - Фізика та інформатика, TN - Трудове навчання

struct Student
{
    std::string prizv;     // прізвище
    int kurs;              // курс (1..6)
    Specialnist spec;      // спеціальність

    union
    {
        struct
        {
            int fizyka;       // оцінка з фізики (1..5)
            int matematyka;   // оцінка з математики (1..5)
            int informatyka;  // оцінка з інформатики (1..5)
        };
        int marks[3];         // ті самі три оцінки у вигляді масиву
    };
};

// Введення даних з клавіатури з контролем помилок
void Create(Student* s, const int N);

// Вивід масиву у вигляді таблиці
void Print(const Student* s, const int N);

// Назва спеціальності у вигляді рядка
std::string SpecialnistStr(const Specialnist spec);

// Середній бал одного студента
double AverageMark(const Student& s);

// Предмети (для порівняння середніх балів)
enum Predmet { FIZYKA, MATEMATYKA, INFORMATYKA };

// Назва предмету у вигляді рядка
std::string PredmetStr(const Predmet p);

// Середній бал з одного предмету по всіх студентах
double SubjectAverage(const Student* s, const int N, const Predmet p);

// Завдання 1: повертає кількість студентів, середній бал яких вищий за threshold
int CountAverageAbove(const Student* s, const int N, const double threshold);

// Завдання 2: повертає предмет з найбільшим середнім балом;
// сам середній бал повертає через параметр-посилання maxAverage
Predmet BestSubject(const Student* s, const int N, double& maxAverage);

std::string PadRight(const std::string& str, size_t width);