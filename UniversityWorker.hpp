#pragma once
#include "Person.hpp"
#include "Room.hpp"

class UniversityWorker : public Person
{
    public:
        UniversityWorker(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition);
        UniversityWorker();
        ~UniversityWorker();
        void mainLoop() override;
        void operator()();
};