#pragma once
#include <string>
#include <vector>
#include <thread>
#include "Room.hpp"
#include "Visualization.hpp"
#include <mutex>
#include <unistd.h>
#define SLOWING_FACTOR 1
#define BENCHES 4
#define SEATS 4

class Student;

class Corridor : public Room
{
    public:
    float traffic;
    float slowing_factor;
    std::thread t;

    std::mutex bMtx;
    std::vector<std::vector<Student *>> bench;

    Visualization * v;

    Corridor(std::string name, int capacity, Visualization * v);
    Corridor();
    ~Corridor();

    void drawPeople();

    float CalculateTraffic();

    bool sitAndFix(Student * s);

    void virtual_function();
}; 
 
