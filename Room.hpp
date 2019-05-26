#pragma once
#include <vector>

#include "Person.hpp"

class Room
{
public:
	int capacity;
	std::vector <Person> people;

	Room(int capacity, std::vector <Person>people);
    Room();
	~Room();
};