#include "pch.h"
#include "CppUnitTest.h"
#include "../10,1 В/function.cpp"   // підключаємо реалізацію (Student.h підключиться з нього)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101
{
    // допоміжна функція: створює студента із заданими оцінками
    static Student Make(const string& prizv, Specialnist spec, int f, int m, int t)
    {
        Student s;
        s.prizv = prizv;
        s.kurs = 1;
        s.spec = spec;
        s.fizyka = f;
        s.matematyka = m;
        switch (spec)
        {
        case KN:   s.programuvannia = t;  break;
        case INF: s.chyselni_metody = t; break;
        default:          s.pedahohika = t;      break;
        }
        return s;
    }

    TEST_CLASS(UnitTest101)
    {
    public:

        TEST_METHOD(TestKilkistSerBalVyshche)
        {
            Student p[4] = {
                Make("A", KN,        5, 5, 5),   // 5,00
                Make("B", INF,      5, 4, 4),   // 4,33
                Make("C", TN, 5, 5, 4), // 4,67
                Make("D", ME,  4, 4, 4)    // 4,00
            };
            Assert::AreEqual(2, CountAverageAbove(p, 4, 4.5));
        }

        TEST_METHOD(TestSerednijBalPredmetu)
        {
            Student p[4] = {
                Make("A", KN,        5, 5, 5),
                Make("B", INF,      5, 4, 4),
                Make("C", TN, 5, 5, 4),
                Make("D", ME,  4, 4, 4)
            };
            Assert::AreEqual(4.75, SerednijBalPredmetu(p, 4, FIZYKA), 1e-9);
            Assert::AreEqual(4.0, SerednijBalPredmetu(p, 4, PEDAHOHIKA), 1e-9);
        }

        TEST_METHOD(TestNajkrashyjPredmet_Tretij)
        {
            Student p[4] = {
                Make("A", KN,        5, 5, 5),
                Make("B", INF,      5, 4, 4),
                Make("C", TN, 5, 5, 4),
                Make("D", ME,  4, 4, 4)
            };
            // програмування – лише в студента A, середній бал 5,0
            Assert::AreEqual((int)PROGR, (int)BestSubject(p, 4));
        }

        TEST_METHOD(TestNajkrashyjPredmet_Fizyka)
        {
            Student p[2] = {
                Make("A", KN, 5, 4, 3),
                Make("B", KN, 5, 4, 3)
            };
            Assert::AreEqual((int)FIZYKA, (int)BestSubject(p, 2));
        }
    };
}