#pragma once
#include "Room.hpp"
#include <string>
#include <thread>
#include "Visualization.hpp"
#include <chrono>
#include <mutex>

using namespace std;

class Entrance : public Room
{
private:
    
    void mainLoop();

public:
    Visualization * v;
    std::mutex EntranceMutex;
    std::vector<Person*> enterancePeople;
    Entrance(std::string name, int capacity, Visualization * _v);
    Entrance();
    ~Entrance();

    void drawPeople();
    std::thread t;


    void virtual_function();
}; 
