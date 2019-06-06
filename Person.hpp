#pragma once
#include <string>
#include <thread>
#include <atomic>
#include "Status.cpp"
#include "PersonType.cpp"

class Room;

class Person
{
public:
    std::thread t;
    std::string name;
	Room *actualPosition;
    Status status;
    PersonType type;
    std::atomic<bool> end;
    Person(std::string name, Status status, PersonType type, Room *actualPosition);
    Person();
	~Person();

    virtual void operator()();      // method to override in upper classes, main thread function
    virtual void mainLoop();
    int travel(Room *destination);
    void dispose();                 // WC routine method - usable only when in Toilet
    void getTP();                   // fetching toilet paper - usable only when in Storage Room
    void Print();
};
