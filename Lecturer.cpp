#include "Lecturer.hpp"


Lecturer::Lecturer(std::string name, Status status, PersonType type,Room *actualPosition)
: Person(name,status,type,actualPosition)
{
}

void Lecturer::mainLoop(){

}

void Lecturer::operator()(){}