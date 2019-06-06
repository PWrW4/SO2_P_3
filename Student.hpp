#pragma once
#include "Person.hpp"
#include "Room.hpp"

class Student : public Person
{
    public:
        Student(std::string name, Status status, PersonType type,Room *actualPosition);
        Student();
        ~Student();
        void mainLoop() override;
        void operator()();
};