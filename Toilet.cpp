#include <string>
#include "Toilet.hpp"
#include "Person.hpp"

	Toilet::Toilet(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_Toilet)
    {
        cubicle = new bool[CUBICLE_CNT];
        urinal = new bool[URINAL_CNT];
    }

    Toilet::Toilet()
    {
        cubicle = new bool[CUBICLE_CNT];
        urinal = new bool[URINAL_CNT];
    }

    Toilet::~Toilet()
    {
        delete cubicle, urinal;
    } 

    void Toilet::Occupy(bool *type, int index)
    {
        type[index] = true;
    }

    void Toilet::Free(bool *type, int index)
    {
        type[index] = false;
    }

    void Toilet::ServePerson(Person *person)
    {
    
    }

    void Toilet::virtual_function(){}