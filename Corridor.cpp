#include <string>
#include "Corridor.hpp"

	Corridor::Corridor(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_Corridor)
    {

    }

    Corridor::Corridor(){}
    Corridor::~Corridor(){} 
 
