#include "Room.hpp"

class Classroom : public Room
{
    public:
    Classroom(std::string name, int capacity);
    Classroom();
    ~Classroom();
}