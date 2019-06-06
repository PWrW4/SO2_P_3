#pragma once
#include "Person.hpp"
#include "Room.hpp"

class Checker : public Person
{
    public:
        Checker(std::string name, Status status, PersonType type,Room *actualPosition);
        Checker();
        ~Checker();
        void mainLoop() override;
        void operator()();
};