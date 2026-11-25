
#include <iostream>
#include <string>
#ifdef _WIN32
#include <Windows.h>        // Підтримка кирилиці в консолі
#endif
#include "function.h"
#include "StudentInput.h"

using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleCP(65001);         // win-cp65001 для введення data;
    SetConsoleOutputCP(65001);   // win-cр65001 для виведення data;
#endif

    int count = ReadIntInRange("Введіть кількість студентів N: ", 1, 1000);
    Student* students = new Student[count]();

    bool isDataEntered = false;         // дані введені
    bool isPhysicallySorted = false;    // масив фізично відсортований (необхідно для бінарного пошуку)

    int menuItem;
    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента за прізвищем, середнім балом" << endl;
        cout << "       та оцінкою з третього предмету" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        menuItem = ReadIntInRange("Введіть значення: ", 0, 5);
        cout << endl;

        if (menuItem >= 2 && menuItem <= 5 && !isDataEntered)
        {
            cout << "Спочатку введіть дані (пункт 1)!" << endl;
            continue;
        }

        switch (menuItem)
        {
        case 1:
            FillStudents(students, count);
            isDataEntered = true;
            isPhysicallySorted = false;
            break;
        case 2:
            PrintStudents(students, count);
            break;
        case 3:
            SortPhysically(students, count);
            isPhysicallySorted = true;
            cout << "Масив фізично впорядковано." << endl;
            break;
        case 4:
        {
            int* index = BuildSortedIndex(students, count);
            PrintStudentsByIndex(students, index, count);
            delete[] index;
            break;
        }
        case 5:
        {
            if (!isPhysicallySorted)
            {
                cout << "Бінарний пошук потребує впорядкованого масиву – "
                    "спочатку виконайте пункт 3!" << endl;
                break;
            }
            cout << "Введіть ключі пошуку:" << endl;
            string surname = ReadSurname("     прізвище: ");
            double averageGrade = ReadDoubleInRange("     середній бал (1-5): ", MIN_GRADE, MAX_GRADE);
            int thirdGrade = ReadIntInRange("     оцінка з третього предмету (1-5): ", MIN_GRADE, MAX_GRADE);
            cout << endl;

            int found = BinarySearch(students, count, surname, averageGrade, thirdGrade);
            if (found != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        }
        case 0:
            break;
        }
    } while (menuItem != 0);

    delete[] students;
    return 0;
}