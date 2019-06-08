#pragma once
#include <string>
#include <thread>
#include <atomic>
#include <random>
#include <chrono>

#include "Status.cpp"
#include "PersonType.cpp"
#include "Floor.hpp"
#include "Timer.hpp"

#define TIME_MIN 2500
#define TIME_MAX 3500

class Room;

class Person
{
public:
    std::thread person_thread;
    std::string name;
    std::string progress_bar;
    Timer *timer;
	Room *actualPosition;
    Status status;
    PersonType type;
    Floor f;
    std::atomic<bool> end;
    std::mt19937 rng{std::random_device{}()};
    Person(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition);
    Person();
	~Person();

    virtual void run();      // method to override in upper classes, main thread function
    virtual void mainLoop();
    int travel(Room *destination);

    void dispose();                 // WC routine method - usable only when in Toilet
    void getTP();                   // fetching toilet paper - usable only when in Storage Room
    void Print();
};
