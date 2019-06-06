#include "Cloakroom.hpp"

	Cloakroom::Cloakroom(std::string name, int capacity)
        : Room(name, capacity, RoomType::Cloakroom)
    {

    }

    Cloakroom::Cloakroom(){}
    Cloakroom::~Cloakroom(){}