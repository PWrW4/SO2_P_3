#include "Student.hpp"
#include <chrono>
#include <random>

Student::Student(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition)
: Person(name,_f,status,type,actualPosition)
{
}

void Student::mainLoop(){
    int sleep = 0;
    while (!this->end)
    {
        this->actualPosition->typeMutex.lock();
        RoomType t = this->actualPosition->type;
        this->actualPosition->typeMutex.unlock();
        switch (t)
        {
        case E_Entrance:
            sleep = std::uniform_int_distribution<int>(15, 30)(rng);
            std::this_thread::sleep_for(std::chrono::milliseconds(100*sleep));
            //travel()
            break;
        case E_Corridor:
            sleep = std::uniform_int_distribution<int>(15, 30)(rng);
            std::this_thread::sleep_for(std::chrono::milliseconds(100*sleep));
            //travel()
            break;
        
        default:
            break;
        }
    }    
}

void Student::operator()(){}