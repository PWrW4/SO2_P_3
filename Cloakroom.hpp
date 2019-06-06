#include <string>
#include "Room.hpp"

class Cloakroom : public Room
{
    public:
    Cloakroom(std::string name, int capacity);
    Cloakroom();
    ~Cloakroom();
};