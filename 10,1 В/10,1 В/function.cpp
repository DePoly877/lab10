// Student.cpp – РЕАЛІЗАЦІЯ модуля
#include "function.h"
#include <iostream>
#include <iomanip>

using namespace std;

string SpecialnistStr(const Specialnist spec)
{
    switch (spec)
    {
    case KN:          return "Комп'ютерні науки";
    case INF:        return "Інформатика";
    case ME:    return "Математика та економіка";
    case FI:    return "Фізика та інформатика";
    case TN: return "Трудове навчання";
    }
    return "";
}

string PredmetStr(const Predmet predmet)
{
    switch (predmet)
    {
    case FIZYKA:          return "Фізика";
    case MATEM:      return "Математика";
    case PROGR:  return "Програмування";
    case CH_METOD: return "Чисельні методи";
    case PEDAHOHIKA:      return "Педагогіка";
    }
    return "";
}

bool MaiePredmet(const Student& s, const Predmet predmet)
{
    switch (predmet)
    {
    case FIZYKA:
    case MATEM:
        return true;
    case PROGR:
        return s.spec == KN;
    case CH_METOD:
        return s.spec == INF;
    case PEDAHOHIKA:
        return s.spec != KN && s.spec != INF;
    }
    return false;
}

int Otsinka(const Student& s, const Predmet predmet)
{
    switch (predmet)
    {
    case FIZYKA:          return s.fizyka;
    case MATEM:      return s.matematyka;
    case PROGR:  return s.programuvannia;
    case CH_METOD: return s.chyselni_metody;
    case PEDAHOHIKA:      return s.pedahohika;
    }
    return 0;
}

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

void Create(Student* p, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "     прізвище: ";   getline(cin, p[i].prizv);
        p[i].kurs = ReadInt("  курс (1-6): ", 1, 6);
        p[i].spec = (Specialnist)ReadInt(
            "  спеціальність (0 - КН, 1 - Інформатика, 2 - Мат.та екон.,\n"
            "                 3 - Фіз.та інф., 4 - Труд.навч.): ", 0, 4);

        p[i].fizyka = ReadInt("  оцінка з фізики (1-5): ", 1, 5);
        p[i].matematyka = ReadInt("  оцінка з математики (1-5): ", 1, 5);
        switch (p[i].spec)
        {
        case KN:
            p[i].programuvannia = ReadInt("  оцінка з програмування: (1-5): ", 1, 5);
            break;
        case INF:
            p[i].chyselni_metody = ReadInt("  оцінка з чисельних методів: (1-5): ", 1, 5);
            break;
        default:
            p[i].pedahohika = ReadInt("  оцінка з педагогіки: (1-5): ", 1, 5);
            break;
        }
        cout << endl;
    }
}

void Print(const Student* p, const int N)
{
    cout << "====================================================================================================================" << endl;
    cout << "| №  | Прізвище        | Курс | Спеціальність           | Фізика | Математика | Програм. | Чис.методи | Педагогіка |" << endl;
    cout << "====================================================================================================================" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << left << i + 1
            << "| " << PadRight(p[i].prizv, 16)
            << "| " << setw(5) << right << p[i].kurs
            << "| " << PadRight(SpecialnistStr(p[i].spec), 24)
            << "| " << setw(7) << right << p[i].fizyka
            << "| " << setw(11) << right << p[i].matematyka << "|";

        // у рядку заповнена лише одна з трьох клітинок
        const Predmet tretij[] = { PROGR, CH_METOD, PEDAHOHIKA };
        const int     width[] = { 9, 11, 11 };
        for (int k = 0; k < 3; k++)
        {
            if (MaiePredmet(p[i], tretij[k]))
                cout << setw(width[k]) << right << Otsinka(p[i], tretij[k]);
            else
                cout << setw(width[k]) << " ";
            cout << " |";
        }
        cout << endl;
    }
    cout << "====================================================================================================================" << endl << endl;
}

double SerednijBal(const Student& s)
{
    // третя оцінка є в кожного студента (залежить лише від спеціальності)
    int tretia = (s.spec == KN) ? s.programuvannia
        : (s.spec == INF) ? s.chyselni_metody
        : s.pedahohika;
    return (s.fizyka + s.matematyka + tretia) / 3.0;
}

int CountAverageAbove(const Student* p, const int N, const double mezha)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (SerednijBal(p[i]) > mezha)
            k++;
    return k;
}

double SerednijBalPredmetu(const Student* p, const int N, const Predmet predmet)
{
    int suma = 0, k = 0;
    for (int i = 0; i < N; i++)
        if (MaiePredmet(p[i], predmet))
        {
            suma += Otsinka(p[i], predmet);
            k++;
        }
    if (k == 0)
        return -1;
    return (double)suma / k;
}

Predmet BestSubject(const Student* p, const int N)
{
    Predmet best = FIZYKA;
    double  maxBal = SerednijBalPredmetu(p, N, FIZYKA);
    for (int i = MATEM; i < n_subject; i++)
    {
        double bal = SerednijBalPredmetu(p, N, (Predmet)i);
        if (bal > maxBal)
        {
            maxBal = bal;
            best = (Predmet)i;
        }
    }
    return best;
}

std::string PadRight(const std::string& str, int width)
{
    int visualLength = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        unsigned char c = static_cast<unsigned char>(str[i]);
        if ((c == 0xD0 || c == 0xD1) && i + 1 < str.length())
        {
            visualLength++;
            i++; // пропускаємо другий байт UTF-8
        }
        else
        {
            visualLength++;
        }
    }
    if (visualLength >= width)
        return str;
    return str + std::string(width - visualLength, ' ');
}