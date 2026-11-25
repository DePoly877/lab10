// Lab_10_1.cpp
// <прізвище, ім'я>
// Лабораторна робота № 10.1
// Послідовний пошук в масиві структур
// Варіант 16
#include <iostream>
#define NOMINMAX
#include <Windows.h>        // забезпечення відображення кирилиці
#include "function.h"

using namespace std;

int main()
{
    SetConsoleCP(65001);         // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(65001);   // встановлення сторінки win-cp1251 в потік виводу

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

    Student* p = new Student[N];

    Create(p, N);
    Print(p, N);

    cout << "Кількість студентів із середнім балом > 4,5: "
        << CountAverageAbove(p, N, 4.5) << endl;

    cout << "Предмет з найбільшим середнім балом: "
        << PredmetStr(BestSubject(p, N)) << endl;

    delete[] p;
    return 0;
}