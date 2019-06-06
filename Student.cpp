#include "Student.hpp"


Student::Student(std::string name, Status status, PersonType type,Room *actualPosition)
: Person(name,status,type,actualPosition)
{
}

void Student::mainLoop(){

}

void Student::operator()(){}