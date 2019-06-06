#include "UniversityWorker.hpp"


UniversityWorker::UniversityWorker(std::string name, Status status, PersonType type,Room *actualPosition)
: Person(name,status,type,actualPosition)
{
}

void UniversityWorker::mainLoop(){

}

void UniversityWorker::operator()(){}