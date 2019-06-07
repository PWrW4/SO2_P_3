#include "Lecturer.hpp"


Lecturer::Lecturer(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition)
: Person(name,_f,status,type,actualPosition)
{
}

void Lecturer::mainLoop(){

}

void Lecturer::operator()(){}