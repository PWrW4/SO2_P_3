#include "Person.hpp"

using namespace std;

//	Person::Person(Room actualPosition)
 //   {
  //      this->actualPosition = actualPosition;
  //  }
  	Person::Person(Status status, PersonType type)
    {
       this->status = status;
       this->type = type;
    }
    Person::Person() {}
	Person::~Person() {}