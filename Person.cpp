#include "Room.hpp"
#include "Person.hpp"

using namespace std;

//	Person::Person(Room actualPosition)
 //   {
  //      this->actualPosition = actualPosition;
  //  }
  	Person::Person(Status status, PersonType type,Room *actualPosition)
    {
       this->status = status;
       this->type = type;
       this->actualPosition = actualPosition;
    }
   Person::Person() {}
	Person::~Person() {}

   void Person::operator()() {}

   void Person::travel(Room *source, Room *destination)
   {

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