// Лабораторна робота № 10.1, рівень А, варіант 16
#include <iostream>
#include <iomanip>
#include <limits>
#include "header.h"
#ifdef _WIN32
#define NOMINMAX
#include <Windows.h> // відображення кирилиці
#endif
using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    int N;
    while (true)
    {
        cout << "Введіть кількість студентів N: ";
        if (cin >> N && N > 0)
            break;
        cout << "  Помилка! Введіть додатне ціле число" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Student* s = new Student[N];
    Create(s, N);
    Print(s, N);

    // Завдання 1: кількість студентів із середнім балом > 4,5
    cout << "Кількість студентів із середнім балом > 4,5: "
        << CountAverageAbove(s, N, 4.5) << endl;

    // Завдання 2: предмет з найбільшим середнім балом
    double maxAvg;
    Predmet best = BestSubject(s, N, maxAvg);
    cout << "Предмет з найбільшим середнім балом: " << PredmetStr(best)
        << " (" << fixed << setprecision(2) << maxAvg << ")" << endl;

    delete[] s;
    return 0;
}