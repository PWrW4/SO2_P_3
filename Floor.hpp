#pragma once
#include <vector>
#include "Room.hpp"

class Floor{
public:
    Floor * up;
    Floor * down;
    std::vector<Room*> floorRooms;

    Floor();
    ~Floor();
};