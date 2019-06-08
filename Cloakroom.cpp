#include <string>
#include "Cloakroom.hpp"

	Cloakroom::Cloakroom(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_Cloakroom)
    {

    }

    Cloakroom::Cloakroom(){}
    Cloakroom::~Cloakroom(){}

    void Cloakroom::virtual_function(){}