#pragma once
#include <vector>
#include "Room.hpp"
#include <mutex>

class Floor{
public:
    std::vector<Room*> floorRooms;
    std::mutex mtx;
    Floor();
    ~Floor();
};