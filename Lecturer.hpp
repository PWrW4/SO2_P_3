#pragma once
#include "Person.hpp"
#include "Room.hpp"

class Lecturer : public Person
{
    public:
        Lecturer(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display);
        Lecturer();
        ~Lecturer();
        void mainLoop() override;
        void operator()();
};