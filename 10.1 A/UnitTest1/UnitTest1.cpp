// UnitTest.cpp - файл unit-тестів (проєкт "Native Unit Test Project" у Visual Studio)
#include "pch.h"
#include "CppUnitTest.h"
#include "../10.1 A/header.h"
#include "../10.1 A/doing.cpp" // підключаємо реалізацію тестованих функцій

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101
{
    TEST_CLASS(UnitTest101)
    {
    public:

        // Тестові дані: 3 студенти
        //   Іваненко: 5 5 5 -> середній 5.00
        //   Петренко: 4 4 4 -> середній 4.00
        //   Сидоренко: 5 5 4 -> середній 4.67
        static void FillData(Student* s)
        {
            s[0] = { "Іваненко",  1, KN, 5, 5, 5 };
            s[1] = { "Петренко",  1, IN, 4, 4, 4 };
            s[2] = { "Сидоренко", 2, ME, 5, 5, 4 };
        }

        TEST_METHOD(TestAverageMark)
        {
            Student s = { "Тест", 1, KN, 5, 5, 4 };
            Assert::AreEqual(14.0 / 3.0, AverageMark(s), 0.0001);
        }

        TEST_METHOD(TestCountAverageAbove)
        {
            Student s[3];
            FillData(s);
            // середній бал > 4.5 у Іваненка (5.00) і Сидоренка (4.67)
            Assert::AreEqual(2, CountAverageAbove(s, 3, 4.5));
        }

        TEST_METHOD(TestCountAverageAboveNone)
        {
            Student s[1] = { { "Петренко", 1, IN, 4, 4, 4 } };
            Assert::AreEqual(0, CountAverageAbove(s, 1, 4.5));
        }

        TEST_METHOD(TestSubjectAverage)
        {
            Student s[3];
            FillData(s);
            Assert::AreEqual(14.0 / 3.0, SubjectAverage(s, 3, FIZYKA), 0.0001);
            Assert::AreEqual(14.0 / 3.0, SubjectAverage(s, 3, MATEMATYKA), 0.0001);
            Assert::AreEqual(13.0 / 3.0, SubjectAverage(s, 3, INFORMATYKA), 0.0001);
        }

        TEST_METHOD(TestBestSubject)
        {
            Student s[3];
            FillData(s);
            double maxAvg;
            Predmet best = BestSubject(s, 3, maxAvg);
            // фізика і математика мають однаковий бал - повертається перший (фізика)
            Assert::IsTrue(best == FIZYKA);
            Assert::AreEqual(14.0 / 3.0, maxAvg, 0.0001);
        }

        TEST_METHOD(TestBestSubjectInformatyka)
        {
            Student s[2] = { { "А", 1, KN, 3, 3, 5 },{ "Б", 1, KN, 4, 3, 5 } };
            double maxAvg;
            Predmet best = BestSubject(s, 2, maxAvg);
            Assert::IsTrue(best == INFORMATYKA);
            Assert::AreEqual(5.0, maxAvg, 0.0001);
        }
    };
}