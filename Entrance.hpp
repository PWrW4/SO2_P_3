#pragma once
#include "Room.hpp"
#include <thread>
#include <chrono>

using namespace std;

class Entrance : Room
{
private:
    
    void mainLoop();

public:
    std::mutex EntranceMutex;

    Entrance(std::string name, int capacity)
    Entrance();
    ~Entrance();
}; 
