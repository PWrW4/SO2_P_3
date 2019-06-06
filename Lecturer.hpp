#pragma once
#include "Person.hpp"
#include "Room.hpp"

class Lecturer : public Person
{
    public:
        Lecturer(std::string name, Status status, PersonType type,Room *actualPosition);
        Lecturer();
        ~Lecturer();
        void mainLoop() override;
        void operator()();
};