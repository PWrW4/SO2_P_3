#include <string>
#include "Room.hpp"
#define CUBICLE_CNT 2
#define URINAL_CNT 4

class Person;

class Toilet : public Room
{
    public:
    bool *cubicle;
    bool *urinal;

    Toilet(std::string name, int capacity);
    Toilet();
    ~Toilet();

    void Occupy(bool *type, int index);
    void Free(bool *type, int index);
    void ServePerson(Person *person);

    void virtual_function();
};
