// модуль перевірки введених з клавіатури даних
#include "StudentInput.h"
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

static const string ERROR_MESSAGE = "     Помилка введення! Спробуйте ще раз.";

static bool ParseInt(const string& text, int& value)
{
    istringstream stream(text);
    stream >> value;
    if (stream.fail())
        return false;
    stream >> ws;
    return stream.eof();        // нічого зайвого після числа
}

static bool ParseDouble(string text, double& value)
{
    for (size_t i = 0; i < text.size(); i++)
        if (text[i] == ',')     // також допускати використання коми в десяткових числах
            text[i] = '.';

    istringstream stream(text);
    stream >> value;
    if (stream.fail())
        return false;
    stream >> ws;
    return stream.eof();
}

int ReadIntInRange(const string& prompt, const int minValue, const int maxValue)
{
    string line;
    int value;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))    // потік введення закрито
        {
            cin.clear();
            return minValue;
        }
        if (ParseInt(line, value) && value >= minValue && value <= maxValue)
            return value;
        cout << ERROR_MESSAGE << " (ціле число від " << minValue << " до " << maxValue << ")" << endl;
    }
}

double ReadDoubleInRange(const string& prompt, const double minValue, const double maxValue)
{
    string line;
    double value;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
        {
            cin.clear();
            return minValue;
        }
        if (ParseDouble(line, value) && value >= minValue && value <= maxValue)
            return value;
        cout << ERROR_MESSAGE << " (число від " << minValue << " до " << maxValue << ")" << endl;
    }
}

string ReadSurname(const string& prompt)
{
    string line;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
        {
            cin.clear();
            return "-";
        }

        bool isCorrect = !line.empty();
        for (size_t i = 0; i < line.size(); i++)
            if (isdigit((unsigned char)line[i]))
                isCorrect = false;

        if (isCorrect)
            return line;
        cout << ERROR_MESSAGE << " (прізвище не може бути порожнім або містити цифри)" << endl;
    }
}

void FillStudents(Student* students, const int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        students[i].surname = ReadSurname("     прізвище: ");
        students[i].course = ReadIntInRange("     курс (1-6): ", MIN_COURSE, MAX_COURSE);
        students[i].specialty = (Specialty)ReadIntInRange(
            "     спеціальність (0 - Комп'ютерні науки, 1 - Інформатика,\n"
            "                    2 - Математика та економіка, 3 - Фізика та інформатика,\n"
            "                    4 - Трудове навчання): ", 0, 4);
        students[i].physicsGrade = ReadIntInRange("     оцінка з фізики (1-5): ", MIN_GRADE, MAX_GRADE);
        students[i].mathGrade = ReadIntInRange("     оцінка з математики (1-5): ", MIN_GRADE, MAX_GRADE);

        switch (GetThirdSubject(students[i].specialty))
        {
        case PROGRAMMING:
            students[i].programmingGrade = ReadIntInRange("     оцінка з програмування (1-5): ", MIN_GRADE, MAX_GRADE);
            break;
        case NUMERICAL_METHODS:
            students[i].numericalMethodsGrade = ReadIntInRange("     оцінка з чисельних методів (1-5): ", MIN_GRADE, MAX_GRADE);
            break;
        case PEDAGOGY:
            students[i].pedagogyGrade = ReadIntInRange("     оцінка з педагогіки (1-5): ", MIN_GRADE, MAX_GRADE);
            break;
        }
        cout << endl;
    }
}