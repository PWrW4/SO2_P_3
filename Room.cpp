#include <vector>
#include "Room.hpp"

using namespace std;

	Room::Room(int capacity, RoomType type, vector <Person>people)
    {
        this->capacity = capacity;
        this->type = type;
        this->people = people;
    }
    Room::Room() {}
	Room::~Room() {}