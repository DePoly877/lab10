#include "pch.h"
#include "CppUnitTest.h"
#include "../10.2 real A/Student.cpp"   // implementation (Student.h is included from it)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102A
{
    // helper: creates a student with the given grades
    static Student MakeStudent(const string& surname, Specialty specialty,
        int physics, int math, int informatics)
    {
        Student s;
        s.surname = surname;
        s.course = 1;
        s.specialty = specialty;
        s.physicsGrade = physics;
        s.mathGrade = math;
        s.informaticsGrade = informatics;
        return s;
    }

    TEST_CLASS(UnitTest102A)
    {
    public:

        TEST_METHOD(TestCompareAverages)
        {
            Assert::AreEqual(0, CompareAverages(4.33, 13.0 / 3));
            Assert::AreEqual(-1, CompareAverages(4.0, 4.33));
            Assert::AreEqual(1, CompareAverages(5.0, 4.67));
        }

        TEST_METHOD(TestSortPhysically)
        {
            Student s[4] = {
                MakeStudent("Adams", COMPUTER_SCIENCE,   5, 5, 5),   // 5.00 / 5
                MakeStudent("Brown", INFORMATICS,        5, 4, 4),   // 4.33 / 4
                MakeStudent("Clark", LABOR_TRAINING,     4, 5, 4),   // 4.33 / 4
                MakeStudent("Davis", MATH_AND_ECONOMICS, 3, 3, 3)    // 3.00 / 3
            };
            SortPhysically(s, 4);
            // average asc, informatics grade asc, surname DESC
            Assert::AreEqual(string("Davis"), s[0].surname);
            Assert::AreEqual(string("Clark"), s[1].surname);
            Assert::AreEqual(string("Brown"), s[2].surname);
            Assert::AreEqual(string("Adams"), s[3].surname);
        }

        TEST_METHOD(TestBuildSortedIndex)
        {
            Student s[4] = {
                MakeStudent("Adams", COMPUTER_SCIENCE,   5, 5, 5),
                MakeStudent("Brown", INFORMATICS,        5, 4, 4),
                MakeStudent("Clark", LABOR_TRAINING,     4, 5, 4),
                MakeStudent("Davis", MATH_AND_ECONOMICS, 3, 3, 3)
            };
            int* index = BuildSortedIndex(s, 4);
            // surname ASC for equal average and informatics grade
            Assert::AreEqual(3, index[0]);   // Davis
            Assert::AreEqual(1, index[1]);   // Brown
            Assert::AreEqual(2, index[2]);   // Clark
            Assert::AreEqual(0, index[3]);   // Adams
            Assert::AreEqual(string("Adams"), s[0].surname);   // array itself is unchanged
            delete[] index;
        }

        TEST_METHOD(TestBinarySearchFound)
        {
            Student s[4] = {
                MakeStudent("Adams", COMPUTER_SCIENCE,   5, 5, 5),
                MakeStudent("Brown", INFORMATICS,        5, 4, 4),
                MakeStudent("Clark", LABOR_TRAINING,     4, 5, 4),
                MakeStudent("Davis", MATH_AND_ECONOMICS, 3, 3, 3)
            };
            SortPhysically(s, 4);
            Assert::AreEqual(2, BinarySearch(s, 4, "Brown", 4.33, 4));
            Assert::AreEqual(1, BinarySearch(s, 4, "Clark", 4.33, 4));
            Assert::AreEqual(3, BinarySearch(s, 4, "Adams", 5.0, 5));
        }

        TEST_METHOD(TestBinarySearchNotFound)
        {
            Student s[4] = {
                MakeStudent("Adams", COMPUTER_SCIENCE,   5, 5, 5),
                MakeStudent("Brown", INFORMATICS,        5, 4, 4),
                MakeStudent("Clark", LABOR_TRAINING,     4, 5, 4),
                MakeStudent("Davis", MATH_AND_ECONOMICS, 3, 3, 3)
            };
            SortPhysically(s, 4);
            Assert::AreEqual(-1, BinarySearch(s, 4, "Brown", 4.33, 5));   // wrong informatics grade
            Assert::AreEqual(-1, BinarySearch(s, 4, "Smith", 5.0, 5));    // no such surname
            Assert::AreEqual(-1, BinarySearch(s, 0, "Brown", 4.33, 4));   // empty array
        }
    };
}