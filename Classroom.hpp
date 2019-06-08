#include <string>
#include <vector>
#include "Room.hpp"

class Person;

class Classroom : public Room
{
public:
    Classroom(std::string name, int capacity);
    Classroom();
    ~Classroom();

    void virtual_function();

};