
#include "Classroom.hpp"

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
            v->PutChar(cy+1,cx,"L");
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
            v->PutChar(cy-1,cx,"L");
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
    
}

Classroom::Classroom() {}
Classroom::~Classroom() {}

void Classroom::virtual_function() {}
