#include "Room.hpp"
#include "Person.hpp"
#include "Visualization.hpp"
#include <iostream>

using namespace std;

   Person::Person(bool *isEnd,std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display)
   {
      this->Display = Display;
      _f->mtx.lock();
      this->f.floorRooms = _f->floorRooms;
      _f->mtx.unlock();
      this->timer = new Timer(TIME_MIN,TIME_MAX);
      this->name = name;
      this->status = status;
      this->type = type;
      this->actualPosition = actualPosition;
      this->isEnd = isEnd;
      std::lock_guard<std::mutex> lock_at_start(actualPosition->travelMutex);
      actualPosition->addPerson(this);
   }
   Person::Person() {}
   Person::~Person() 
   {
      delete timer;
      	person_thread.join();
   }

   void Person::run() {}
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

   void Person::DoProgress(Visualization *Display,int id)
   {
	for(int i=0, color=0; i<Display->ec_width ; i++)						// Postęp czynności
		{
			if(i<Display->ec_width/2)												// Wybór koloru
				color = COLOR_GREEN;
			else if(i<3*Display->ec_width/4)
				color = COLOR_YELLOW;
			else
				color = COLOR_RED;

			timer->delay(Display->ec_width);
			progress_bar+="#";
			{
				attron( COLOR_PAIR( color ) );
				Display->Print(id,3,progress_bar);
				attroff( COLOR_PAIR( color ) );
			}
		}
		progress_bar="";
   }