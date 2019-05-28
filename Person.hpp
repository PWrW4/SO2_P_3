#pragma once

//#include "Room.hpp"
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
    DziekanatCrew = 2
};

class Person
{
public:
//	Room actualPosition;
    Status status;
    PersonType type;
//	Person(Room actualPosition);
    Person(Status status, PersonType type);
    Person();
	~Person();
};
