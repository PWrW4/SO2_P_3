#include "UniversityWorker.hpp"


UniversityWorker::UniversityWorker(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition)
: Person(name,_f,status,type,actualPosition)
{
}

void UniversityWorker::mainLoop(){

}

void UniversityWorker::operator()(){}