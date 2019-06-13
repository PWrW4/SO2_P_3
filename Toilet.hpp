#pragma once
#include <string>
#include "Room.hpp"
#define CUBICLE_CNT 3
#define CUBICLE_W 4
#define URINAL_CNT 6
#define TOILET_COL 21
#define TOILET_COL_W 1
#define TOILET_ROW 5
#define TOILET_ROW_W 1

class Person;

class Toilet : public Room
{
    public:
    bool *cubicle;
    bool *urinal;

    Toilet(std::string name, int capacity);
    Toilet();
    ~Toilet();

    void Occupy(bool *type, int index);
    void Free(bool *type, int index);
    void ServePerson(Person *person);
};
