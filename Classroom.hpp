#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include "Visualization.hpp"
#include "Room.hpp"
#include "Person.hpp"


class Person;

class Classroom : public Room
{
public:
    Classroom(std::string name, int capacity,Visualization * Display, int _id);
    Classroom();
    ~Classroom();

    std::thread t;

    int id;
    Visualization * v;
    int x,y;

    void drawClass();

    void virtual_function();

};