#pragma once
#include "Person.hpp"
#include "Room.hpp"
#include "Classroom.hpp"
#include <thread>
#include "Student.hpp"


class Lecturer : public Person
{
    public:
        Lecturer(bool *isEnd,std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display);
        Lecturer();
        ~Lecturer();

        int id;
        
        int currentPos;

        Classroom * klasa;

        void mainLoop() override;
        void operator()();
};