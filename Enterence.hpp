#pragma once
#include "Room.hpp"
#include <thread>
#include <chrono>

using namespace std;

class Enterence : Room
{
private:
    void mainLoop();
public:
    std::mutex enteranceMutex;
    std::vector<Person*> enterancePeople;
    Enterence();
    ~Enterence();
};

Enterence::Enterence()
{
}

Enterence::~Enterence()
{
}
