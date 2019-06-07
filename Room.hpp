#pragma once
#include <vector>
#include <string>
#include <mutex>

#include "RoomType.cpp"

class Person;

class Room
{
public:
	std::mutex travelMutex;
	std::string name;
	int capacity;
	std::mutex typeMutex;
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