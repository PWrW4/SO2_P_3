#pragma once
#include <vector>
#include <string>
#include <mutex>

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
	std::mutex roomMutex;
	std::string name;
	int capacity;
	RoomType type;
	std::vector <Person*> people;

	Room(std::string name, int capacity, RoomType type,std::vector <Person*> people);
	Room(std::string name, int capacity, RoomType type);
	Room(int capacity, RoomType type);
    Room();
	~Room();

	int addPerson(Person * person);
	int delPerson(Person * person);
	void Print();
	void PrintPeople();
};