#include "Entrance.hpp"

	Entrance::Entrance(std::string name, int capacity, Visualization * _v)
        : Room(name, capacity, RoomType::E_Entrance)
    {
        v = _v;
        std::thread thr(&Entrance::drawPeople, this);
        std::swap(thr, t);
    }

    void Entrance::drawPeople(){
        std::unique_lock<std::mutex> locker_drawing(*v->disp_mutex);
        int xr = v->EnteranceY + 2;
        int yr = v->EnteranceX + 2;
        int c = 0;
        locker_drawing.unlock();
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            capMutex.lock();
            c = people.size();
            capMutex.unlock();
            v->PutChar(xr, yr, "    ");
            v->PutChar(xr, yr, "Sx" + std::to_string(c));
        }
    }

    Entrance::Entrance(){}
    Entrance::~Entrance(){} 

    void Entrance::virtual_function(){}
