#include <string>
#include "DeanOffice.hpp"

	DeanOffice::DeanOffice(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_DeanOffice)
    {

    }

    DeanOffice::DeanOffice(){}
    DeanOffice::~DeanOffice(){}