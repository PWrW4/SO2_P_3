#include <string>
#include "Corridor.hpp"

	Corridor::Corridor(std::string name, int capacity)
        : Room(name, capacity, RoomType::Corridor)
    {

    }

    Corridor::Corridor(){}
    Corridor::~Corridor(){} 
 
