#include "Checker.hpp"


Checker::Checker(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition)
: Person(name,_f,status,type,actualPosition)
{
}

void Checker::mainLoop(){

}

void Checker::operator()(){}