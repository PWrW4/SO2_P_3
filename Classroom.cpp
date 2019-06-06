#include "Classroom.hpp"

	Classroom::Classroom(std::string name, int capacity)
        : Room(name, capacity, RoomType::Classroom)
    {

    }

    Classroom::Classroom(){}
    Classroom::~Classroom(){}