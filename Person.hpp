#pragma once
#include <string>

class Room;

enum Status
{
    Waiting = 0,
    Traveling = 1,
    Accessing = 2,
    Working = 3,
    Entering = 4
};

enum PersonType {
    Professor = 0,
    Student = 1,
    DziekanatCrew = 2,
    CloakroomCrew = 3
};

class Person
{
public:
    std::string name;
	Room *actualPosition;
    Status status;
    PersonType type;
    Person(std::string name, Status status, PersonType type,Room *actualPosition);
    Person(Status status, PersonType type);
    Person();
	~Person();

    virtual void operator()();   // method to override in upper classes, main thread function
    int travel(Room *destination);
    void dispose();                 // WC routine method - usable only when in Toilet
    void getTP();                   // fetching toilet paper - usable only when in Storage Room
    void Print();
};
