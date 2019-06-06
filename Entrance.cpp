#include <string>
#include "Entrance.hpp"

	Entrance::Entrance(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_Entrance)
    {

    }

    Entrance::Entrance(){}
    Entrance::~Entrance(){} 
