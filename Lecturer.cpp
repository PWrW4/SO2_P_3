#include "Lecturer.hpp"


Lecturer::Lecturer(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display)
: Person(name,_f,status,type,actualPosition,Display)
{
    end=false;
    klasa = dynamic_cast<Classroom *>(actualPosition);
    id = klasa->id;

    currentPos = 0;
    klasa->mtx_nauczyciel.lock();
    klasa->nauczyciel[currentPos] = this;
    klasa->mtx_nauczyciel.unlock();

    thread thr(&Lecturer::mainLoop, this);
	std::swap(thr, person_thread);
}

void Lecturer::mainLoop(){
    while (!end)
    {
        std::unique_lock<std::mutex> q_lck(klasa->mtx_q);
        if (!klasa->q.empty())
        {
            int dest = klasa->q.front();
            q_lck.unlock();
            std::unique_lock<std::mutex> n_lck(klasa->mtx_nauczyciel);
            klasa->nauczyciel[currentPos] = nullptr;
            klasa->nauczyciel[dest] = this;
            currentPos = dest;
            n_lck.unlock();
            timer->delay(1000,2000);
            std::unique_lock<std::mutex> s_lck(klasa->mtx_stanowiska);
            Student * s = klasa->stanowiska[dest];
            s_lck.unlock();
            s->studentWaitMutex.lock();
            s->zaliczone = true;
            s->studentWaitBool = false;
            s->studentWaitCond.notify_one();
            s->studentWaitMutex.unlock();
            s_lck.lock();
            klasa->stanowiska[currentPos] = nullptr;
            s_lck.unlock();
            q_lck.lock();
            klasa->q.pop();
            q_lck.unlock();
        }      

        timer->delay(1000,2000);        
    }    
}

void Lecturer::operator()(){}