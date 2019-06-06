#include "Room.hpp"
#include "Person.hpp"
#include <iostream>

using namespace std;

  	Person::Person(std::string name, Status status, PersonType type,Room *actualPosition)
    {
       this->name = name;
       this->status = status;
       this->type = type;
       this->actualPosition = actualPosition;
       this->end = false;
       std::lock_guard<std::mutex> lock_at_start(actualPosition->travelMutex);
       actualPosition->addPerson(this);
    }
   Person::Person() {}
   Person::~Person() {}

   void Person::operator()() {}
   void Person::mainLoop() {}


   int Person::travel(Room *destination)
   {
      std::lock(actualPosition->travelMutex,destination->travelMutex);
      std::lock_guard<std::mutex> from_lock(actualPosition->travelMutex, std::adopt_lock);
      std::lock_guard<std::mutex> to_lock(destination->travelMutex, std::adopt_lock);
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