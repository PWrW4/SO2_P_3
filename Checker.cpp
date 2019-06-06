#include "Checker.hpp"


Checker::Checker(std::string name, Status status, PersonType type,Room *actualPosition)
: Person(name,status,type,actualPosition)
{
}

void Checker::mainLoop(){

}

void Checker::operator()(){}