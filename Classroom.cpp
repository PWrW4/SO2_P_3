#include <string>
#include <iostream>
#include "Classroom.hpp"
#include "Person.hpp"

using namespace std;

	Classroom::Classroom(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_Classroom)
    {

    }

    Classroom::Classroom(){}
    Classroom::~Classroom(){}

    void Classroom::virtual_function(){}

