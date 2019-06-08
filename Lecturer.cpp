#include "Lecturer.hpp"


Lecturer::Lecturer(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display)
: Person(name,_f,status,type,actualPosition,Display)
{
}

void Lecturer::mainLoop(){

}

void Lecturer::operator()(){}