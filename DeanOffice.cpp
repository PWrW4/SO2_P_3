#include <string>
#include "DeanOffice.hpp"

	DeanOffice::DeanOffice(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_DeanOffice)
    {
        stamps = new bool[STAMPS_CNT]
    }

    DeanOffice::DeanOffice(){}
    DeanOffice::~DeanOffice(){}