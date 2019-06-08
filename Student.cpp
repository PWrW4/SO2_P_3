#include <chrono>
#include <random>
#include <cstdlib>
#include <ctime>
#include "Student.hpp"
#include "DeanOffice.hpp"

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

void Student::DeanOfficeRoutine()
{

}

void Student::generateRequest()
{
    request = new int*[DOC_TYPES];            // tablica na tablice dokumentów danych typów
    doc_types_cnt = new int[DOC_TYPES];        // tablica na ilości dokumentów danych typów
    for(int i=0;i<DOC_TYPES;i++)
    {
        doc_types_cnt[i] = rand()%3;
        request[i]= new int[doc_types_cnt[i]];      // tablica na doc_types_cnt[i] dokumentów typu i
        for(int j=0;j<doc_types_cnt[i];j++)
        {
            request[i][j]=0;                        // puste pole na j-ty dokument typu i
        }
    }
}

void Student::printRequest()
{
    cout<<"typ  | sloty na dokumenty\n"<<"----------------------------";
    for(int i=0;i<DOC_TYPES;i++)
    {
        cout<<endl<<i<<".   |";
        for(int j=0;j<doc_types_cnt[i];j++)
        {
            cout<<request[i][j]<<"  ";
        }
    }
    cout<<endl;
}

void Student::getRequest()
{

}

void Student::getDoc(int doc_type)
{

}

void Student::checkStack(int doc_type)
{

}