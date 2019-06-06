#include <string>
#include "Room.hpp"

class Toilet : public Room
{
    public:
    Toilet(std::string name, int capacity);
    Toilet();
    ~Toilet();
}; 
