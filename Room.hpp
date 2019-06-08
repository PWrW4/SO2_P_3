#pragma once
#include <vector>
#include <string>
#include <mutex>

#include "RoomType.cpp"

class Person;

class Room
{
public:
	std::string name;
	int capacity;
	RoomType type;
	std::mutex travelMutex;
	std::mutex typeMutex;

	std::vector<Person*> people;
	std::vector<Person*> workers;
    std::vector<Person*> students;


	Room(std::string name, int capacity, RoomType type,std::vector <Person*> people);
	Room(std::string name, int capacity, RoomType type);
	Room(int capacity, RoomType type);
    Room();
	~Room();

	int addPerson(Person * person);
	int delPerson(Person * person);
    int addWorker(Person *worker);
    int deleteWorker(Person *worker);
    int addStudent(Person *student);
    int deleteStudent(Person *student);

	void Print();
	void PrintPeople();

	virtual void virtual_function();

};