#include "Room.hpp"
#include "Person.hpp"
#include <iostream>

using namespace std;

//	Person::Person(Room actualPosition)
 //   {
  //      this->actualPosition = actualPosition;
  //  }
  	Person::Person(std::string name, Status status, PersonType type,Room *actualPosition)
    {
       this->name = name;
       this->status = status;
       this->type = type;
       this->actualPosition = actualPosition;
       actualPosition->addPerson(this);
    }
   Person::Person(Status status, PersonType type)
    {
       this->name = "person";
       this->status = status;
       this->type = type;
    }
   Person::Person() {}
	Person::~Person() {}

   void Person::operator()() {}

   int Person::travel(Room *destination)
   {
      if(actualPosition->delPerson(this) != -1)          // go to
         if(destination->addPerson(this) != -1)          // try
         {
            actualPosition = destination;                // update
            return 0;
         }
         else
         {
            actualPosition->addPerson(this);             // go back when failed
            return -1;
         }
      else
         return -1;
   }

   void Person::dispose()                 // WC routine method - usable only when in Toilet
   {
      if( this->actualPosition->type == 5)   // actual room is storage
      {

      }
   }

   void Person::getTP()                   // fetching toilet paper - usable only when in Storage Room
   {
      if( this->actualPosition->type == 2)   // actual room is WC
      {

      }
   }

   void Person::Print()
   {
      cout<<name<<", "<<type<<", "<<status<<", "<<actualPosition->name<<endl;
   }