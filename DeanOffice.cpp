#include <string>
#include "DeanOffice.hpp"

	DeanOffice::DeanOffice(std::string name, int capacity)
        : Room(name, capacity, RoomType::DeanOffice)
    {

    }

    DeanOffice::DeanOffice(){}
    DeanOffice::~DeanOffice(){}