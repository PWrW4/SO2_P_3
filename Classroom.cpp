
#include "Classroom.hpp"
#include "Student.hpp"
#include "Lecturer.hpp"

Classroom::Classroom(std::string name, int capacity, Visualization *Display, int _id)
    : Room(name, capacity, RoomType::E_Classroom)
{
    v = Display;
    id = _id;
    v->disp_mutex->lock();
    x = v->ClassRoomX;
    y = v->ClassRoomY;
    y=id*9;
    v->disp_mutex->unlock();

    mtx_nauczyciel.lock();
    mtx_stanowiska.lock();
    nauczyciel.resize(8);
    stanowiska.resize(8);
    for (int i = 0; i < 8; i++)
    {
        nauczyciel[i] == nullptr;
        stanowiska[i] == nullptr;
    }
    mtx_nauczyciel.unlock();
    mtx_stanowiska.unlock();    

    thread thr(&Classroom::drawClass, this);
	std::swap(thr, t);
}

void Classroom::drawClass(){

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        for (int i = 0; i < 8; i++)
        {
            drawStanowisko(i);               
        }
    }
}

void Classroom::drawStanowisko(int nr){
    int cx=0;
    int cy=0;

    if (nr == 0)
    {
        cx = x + 1;
        cy = y + 1;
    }
    if (nr == 1)
    {
        cx = x + 1;
        cy = y + 8;
    }
    if (nr == 2)
    {
        cx = x + 4;
        cy = y + 1;
    }
    if (nr == 3)
    {
        cx = x + 4;
        cy = y + 8;
    }
    if (nr == 4)
    {
        cx = x + 7;
        cy = y + 1;
    }
    if (nr == 5)
    {
        cx = x + 7;
        cy = y + 8;
    }
    if (nr == 6)
    {
        cx = x + 10;
        cy = y + 1;
    }
    if (nr == 7)
    {
        cx = x + 10;
        cy = y + 8;
    }

    if (nr % 2 == 0)
    {
        mtx_nauczyciel.lock();
        if (nauczyciel[nr] == nullptr)
        {
            v->PutChar(cy+1,cx," ");
        }
        else
        {
            nauczyciel[nr]->statMtx.lock();
            Status status = nauczyciel[nr]->status;
            nauczyciel[nr]->statMtx.unlock();
            if (status == E_Working)
            {
                v->PutChar(cy+1, cx, "L", WAITING_COLOR);
            }
            if (status == E_Accessing)
            {
                v->PutChar(cy+1, cx, "L", WORKING_COLOR);
            }
            if (status == E_Waiting)
            {
                v->PutChar(cy+1, cx, "L", IDLE_COLOR);
            }
        }
        mtx_nauczyciel.unlock();
    }
    else
    {
        mtx_nauczyciel.lock();
        if (nauczyciel[nr] == nullptr)
        {
            v->PutChar(cy-1,cx," ");
        }
        else
        {
            nauczyciel[nr]->statMtx.lock();
            Status status = nauczyciel[nr]->status;
            nauczyciel[nr]->statMtx.unlock();
            if (status == E_Working)
            {
                v->PutChar(cy - 1, cx, "L", WAITING_COLOR);
            }
            if (status == E_Accessing)
            {
                v->PutChar(cy - 1, cx, "L", WORKING_COLOR);
            }
            if (status == E_Waiting)
            {
                v->PutChar(cy - 1, cx, "L", IDLE_COLOR);
            }
        }
        mtx_nauczyciel.unlock();
    }



    if (nr % 2 == 0)
    {
        mtx_stanowiska.lock();
        if (stanowiska[nr] == nullptr)
        {
            v->PutChar(cy,cx+1," ");
        }
        else
        {
            v->PutChar(cy,cx+1,"S");
        }
        mtx_stanowiska.unlock();
    }
    else
    {
        mtx_stanowiska.lock();
        if (stanowiska[nr] == nullptr)
        {
            v->PutChar(cy,cx+1," ");
        }
        else
        {
            v->PutChar(cy,cx+1,"S");
        }
        mtx_stanowiska.unlock();
    }
}

void Classroom::studentEnter(Student * s){
    std::lock(mtx_stanowiska,mtx_q);
    std::lock_guard<std::mutex> lstan(mtx_stanowiska, std::adopt_lock);
    std::lock_guard<std::mutex> lque(mtx_q, std::adopt_lock);
    for (int i = 0; i < 8; i++)
    {
        if(stanowiska[i]==nullptr){
            stanowiska[i] = s;
            q.push(i);
            break;
        }
    }
}

Classroom::Classroom() {}
Classroom::~Classroom() {}

void Classroom::virtual_function() {}
