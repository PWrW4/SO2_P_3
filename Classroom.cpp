#include <string>
#include <iostream>
#include "Classroom.hpp"
#include "Person.hpp"

using namespace std;

	Classroom::Classroom(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_Classroom)
    {

    }

    Classroom::Classroom(){}
    Classroom::~Classroom(){}

    int Classroom::setProfessor(Person *professor)
    {
        if(this->professor != nullptr)
        {
            this->professor = professor;
            return 0;
        }
        else
        {
            cout<<"na zajeciach jest juz prowadzacy!\n";
            return -1;
        }   
    }

    int Classroom::freeProfessor()
    {
        this->professor = nullptr;
        return 0;
    }

    int Classroom::addStudent(Person *student)
    {
        if(students.size()==capacity-1)
        {
            cout<<"brak miejsc dla studentow w"<<name<<"!\n";
            return -1;
        }
        students.push_back(student);
        return 0;
    }

    int Classroom::deleteStudent(Person *student)
    {
        if(students.size()==0)
        {
            cout<<"nie ma studentow w sali "<<name<<"!\n";
            return -1;
        }
        vector<Person*>::iterator it = find(students.begin(), students.end(), student);
        if(it == students.end() && students.back() != student)
        {
            cout<<"student nieobecny w "<<name<<"!\n";
            return -1;
        }
        students.erase(it);
        return 0;
    }