#pragma once
#include <vector>

#include "Person.hpp"

enum RoomType {
    Corridor = 0,
    Classroom = 1,
    Toilet = 2,
    Cloakroom = 3,
	Deansoffice = 4,
	Storage = 5
};

class Room
{
public:
	int capacity;
	RoomType type;
	std::vector <Person> people;

	Room(int capacity, RoomType type, std::vector <Person>people);
    Room();
	~Room();
};