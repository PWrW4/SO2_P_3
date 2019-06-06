#include <string>
#include "Entrance.hpp"

	Entrance::Entrance(std::string name, int capacity)
        : Room(name, capacity, RoomType::Entrance)
    {

    }

    Entrance::Entrance(){}
    Entrance::~Entrance(){} 
