#include "Room.hpp"

using namespace std;

	Room::Room(int capacity, vector <Person>people)
    {
        this->capacity = capacity;
        this->people = people;
    }
    Room::Room() {}
	Room::~Room() {}