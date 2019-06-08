#pragma once
#include "Person.hpp"
#include "Room.hpp"

class Checker : public Person
{
    public:
        Checker(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display);
        Checker();
        ~Checker();
        void mainLoop() override;
        void operator()();
};