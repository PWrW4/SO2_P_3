#include <string>
#include "Toilet.hpp"

	Toilet::Toilet(std::string name, int capacity)
        : Room(name, capacity, RoomType::Toilet)
    {

    }

    Toilet::Toilet(){}
    Toilet::~Toilet(){} 
