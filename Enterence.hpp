#pragma once
#include "Room.hpp"
#include <thread>
#include <chrono>


class Enterence : Room
{
private:
    void mainLoop();
public:
    Enterence();
    ~Enterence();
};

Enterence::Enterence()
{
    std::thread t(mainLoop);
}

Enterence::~Enterence()
{
}

void Enterence::mainLoop(){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
