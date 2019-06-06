#pragma once
#include <vector>
#include "Room.hpp"

class Floor{
public:
    std::vector<Room*> floorRooms;

    Floor();
    ~Floor();
};