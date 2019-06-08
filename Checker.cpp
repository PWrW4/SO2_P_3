#include "Checker.hpp"


Checker::Checker(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display)
: Person(name,_f,status,type,actualPosition,Display)
{
}

void Checker::mainLoop(){

}

void Checker::operator()(){}