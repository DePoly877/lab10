#pragma once
#include <string>
#include <cstddef>
using namespace std;

// спеціальності
enum Specialnist
{
    KN,          // Комп'ютерні науки
    INF,        // Інформатика
    ME,    // Математика та економіка
    FI,    // Фізика та інформатика
    TN  // Трудове навчання
};

// предмети (перші два є в усіх студентів, третій – залежить від спеціальності)
enum Predmet
{
    FIZYKA,
    MATEM,
    PROGR,
    CH_METOD,
    PEDAHOHIKA
};

const int n_subject = 5;

struct Student
{
    string      prizv;
    int         kurs;
    Specialnist spec;
    int         fizyka;
    int         matematyka;
    union               // третя оцінка – залежно від спеціальності
    {
        int programuvannia;     // KOMPNAUKY
        int chyselni_metody;    // INFORMATYKA
        int pedahohika;         // всі інші спеціальності
    };
};

// ---- допоміжні функції ----
string SpecialnistStr(const Specialnist spec);
string PredmetStr(const Predmet predmet);
bool   MaiePredmet(const Student& s, const Predmet predmet);   // чи вивчає студент предмет
int    Otsinka(const Student& s, const Predmet predmet);       // оцінка з предмету (якщо MaiePredmet)

// ---- введення / виведення ----
void Create(Student* p, const int N);
void Print(const Student* p, const int N);

// ---- опрацювання ----
double SerednijBal(const Student& s);                                       // середній бал студента
int    CountAverageAbove(const Student* p, const int N, const double mezha); // К-сть студентів із сер. балом > mezha
double SerednijBalPredmetu(const Student* p, const int N, const Predmet predmet); // сер. бал предмету (-1, якщо його ніхто не вивчає)
Predmet BestSubject(const Student* p, const int N);                   // предмет з найбільшим сер. балом

std::string PadRight(const std::string& str, int width); 