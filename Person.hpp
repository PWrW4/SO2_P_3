#pragma once

//#include "Room.hpp"
enum Status
{
    Waiting = 0,
    Traveling = 1,
    Accessing = 2,
    Working = 3
};

class Person
{
public:
//	Room actualPosition;
    Status status;
//	Person(Room actualPosition);
    Person(Status status);
    Person();
	~Person();
};
