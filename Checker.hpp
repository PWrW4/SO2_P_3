#pragma once
#include "Person.hpp"
#include "Room.hpp"
#include "Cloakroom.hpp"
#include <mutex>
#include "Student.hpp"
#include <vector>

class Checker : public Person
{
    public:
        Checker(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display, int id);
        Checker();
        ~Checker();
        void mainLoop() override;

        void drawLeftSlot(std::string s);
        void drawRightSlot(std::string s);
        void drawRightWieszak(std::string s);
        void drawLeftWieszak(std::string s);

        int checkerId=-1;

        Cloakroom *c;

        int s1X = 5;
        int s1Y = 2;
        int s2X = 9;
        int s2Y = 2;
        int lwX = 3;
        int lwY = 1;
        int rwY = 1;
        int rwX = 10;

        void operator()();
};