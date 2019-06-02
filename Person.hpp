#pragma once

class Room;

enum Status
{
    Waiting = 0,
    Traveling = 1,
    Accessing = 2,
    Working = 3
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
	Room *actualPosition;
    Status status;
    PersonType type;
    Person(Status status, PersonType type,Room *actualPosition);
    Person();
	~Person();

    virtual void operator()();   // method to override in upper classes, main thread function
    void travel(Room *source, Room *destination);
    void dispose();                 // WC routine method - usable only when in Toilet
    void getTP();                   // fetching toilet paper - usable only when in Storage Room
};
