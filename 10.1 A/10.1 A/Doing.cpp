// Student.cpp - РЕАЛІЗАЦІЯ функцій, оголошених у Student.h
#include "header.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Читає ціле число з діапазону [min; max], поки користувач не введе коректне
static int ReadInt(const string& prompt, const int min, const int max)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x && x >= min && x <= max)
            return x;
        cout << "  Помилка! Введіть число від " << min << " до " << max << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string SpecialnistStr(const Specialnist spec)
{
    switch (spec)
    {
    case KN: return "Комп. науки";
    case IN: return "Інформатика";
    case ME: return "Мат. та екон.";
    case FI: return "Фіз. та інф.";
    case TN: return "Труд. навч.";
    }
    return "?";
}

void Create(Student* s, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  прізвище: ";
        getline(cin, s[i].prizv);
        s[i].kurs = ReadInt("  курс (1-6): ", 1, 6);
        s[i].spec = (Specialnist)ReadInt(
            "  спеціальність (0 - КН, 1 - Інформатика, 2 - Мат.та екон.,\n"
            "                 3 - Фіз.та інф., 4 - Труд.навч.): ", 0, 4);
        s[i].fizyka = ReadInt("  оцінка з фізики (1-5): ", 1, 5);
        s[i].matematyka = ReadInt("  оцінка з математики (1-5): ", 1, 5);
        s[i].informatyka = ReadInt("  оцінка з інформатики (1-5): ", 1, 5);
        cout << endl;
    }
}

void Print(const Student* s, const int N)
{
    cout << "============================================================================" << endl;
    cout << "|  №  |     Прізвище      | Курс |  Спеціальність  |  Фіз  |  Мат  |  Інф  |" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(4) << right << i + 1 << " "
            << "|   " << PadRight(s[i].prizv, 15) << " "
            << "| " << setw(4) << right << s[i].kurs << " "
            << "|   " << PadRight(SpecialnistStr(s[i].spec), 13) << " "
            << "| " << setw(5) << right << s[i].fizyka << " "
            << "| " << setw(5) << right << s[i].matematyka << " "
            << "| " << setw(5) << right << s[i].informatyka << " |" << endl;
    }
    cout << "============================================================================" << endl;
    cout << endl;
}

double AverageMark(const Student& s)
{
    int sum = 0;
    for (int j = 0; j < 3; j++)
        sum += s.marks[j];
    return sum / 3.0;
}

string PredmetStr(const Predmet p)
{
    switch (p)
    {
    case FIZYKA: return "фізика";
    case MATEMATYKA: return "математика";
    case INFORMATYKA: return "інформатика";
    }
    return "?";
}

double SubjectAverage(const Student* s, const int N, const Predmet p)
{
    if (N <= 0)
        return 0.0;
    double sum = 0;
    for (int i = 0; i < N; i++)
        switch (p)
        {
        case FIZYKA: sum += s[i].fizyka; break;
        case MATEMATYKA: sum += s[i].matematyka; break;
        case INFORMATYKA: sum += s[i].informatyka; break;
        }
    return sum / N;
}

int CountAverageAbove(const Student* s, const int N, const double threshold)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (AverageMark(s[i]) > threshold)
            k++;
    return k;
}

Predmet BestSubject(const Student* s, const int N, double& maxAverage)
{
    Predmet best = FIZYKA;
    maxAverage = SubjectAverage(s, N, FIZYKA);
    for (int p = MATEMATYKA; p <= INFORMATYKA; p++)
    {
        double avg = SubjectAverage(s, N, (Predmet)p);
        if (avg > maxAverage)
        {
            maxAverage = avg;
            best = (Predmet)p;
        }
    }
    return best;
}

// Функція повертає рядок, доповнений пробілами до потрібної візуальної ширини
string PadRight(const string& str, size_t width) {
    size_t visualLength = 0;
    for (unsigned char c : str) {
        // Рахуємо лише початкові байти символів UTF-8 (ігноруємо байти продовження 10xxxxxx)
        if ((c & 0xC0) != 0x80) {
            visualLength++;
        }
    }
    if (visualLength >= width) return str;
    return str + string(width - visualLength, ' ');
}