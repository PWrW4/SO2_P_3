#include "Cloakroom.hpp"
#include "Student.hpp"

Cloakroom::Cloakroom(std::string name, int capacity,Visualization * Display)
    : Room(name, capacity, RoomType::E_Cloakroom)
{
    v = Display;
    // drawLQueue(8);
    // drawRQueue(8);

    thread thr(&Cloakroom::drawQueue, this);
	std::swap(thr, t);
}

void Cloakroom::drawQueue(){
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        int temp = 0;
        mtx_lq.lock();
        temp = ql.size();
        mtx_lq.unlock();
        drawLQueue(temp);
        mtx_rq.lock();
        temp = qr.size();
        mtx_rq.unlock();
        drawRQueue(temp);
    }
}

void Cloakroom::drawLQueue(int a){
    std::unique_lock<std::mutex> locker_drawing(*v->disp_mutex);
    int xr = v->CloakroomY + 6;
	int yr = v->CloakroomX + 4;
    locker_drawing.unlock();
    int xb = xr;
    int yb = yr;
    for (size_t i = 0; i < 12; i++)
    {
        if (i < 6)
        {
            v->PutChar(xr, yr, " ");
            xr--;
        }
        if (i==5)
        {
            xr++;
        }        
        if(i>=6 && i<=12)
        {
            v->PutChar(xr,yr+1," ");
            xr++;  
        }
    }
    xr = xb;
    yr = yb;
    for (size_t i = 0; i < a; i++)
    {
        if (i < 6)
        {
            v->PutChar(xr, yr, "s");
            xr--;
        }
        if (i==5)
        {
            xr++;
        }        
        if(i>=6 && i<=12)
        {
            v->PutChar(xr,yr+1,"s");
            xr++;  
        }
    }
	
}

void Cloakroom::drawRQueue(int a){
    std::unique_lock<std::mutex> locker_drawing(*v->disp_mutex);
    int xr = v->CloakroomY + 10;
	int yr = v->CloakroomX + 4;
    locker_drawing.unlock();
    int xb = xr;
    int yb = yr;
    for (size_t i = 0; i < 12; i++)
    {
        if (i < 6)
        {
            v->PutChar(xr, yr, " ");
            xr++;
        }
        if (i==5)
        {
            xr--;
        }        
        if(i>=6 && i<=12)
        {
            v->PutChar(xr,yr+1," ");
            xr--;  
        }
    } 
    xr = xb;
    yr = yb;
    for (size_t i = 0; i < a; i++)
    {
        if (i < 6)
        {
            v->PutChar(xr, yr, "s");
            xr++;
        }
        if (i==5)
        {
            xr--;
        }        
        if(i>=6 && i<=12)
        {
            v->PutChar(xr,yr+1,"s");
            xr--;  
        }
    } 
}

Cloakroom::Cloakroom() {}
Cloakroom::~Cloakroom() {}

void Cloakroom::enterQueue(Student *s)
{
    std::lock(mtx_lq, mtx_rq);
    std::lock_guard<std::mutex> left_lock(mtx_lq, std::adopt_lock);
    std::lock_guard<std::mutex> right_lock(mtx_rq, std::adopt_lock);

    if (ql.size() <= qr.size())
    {
        ql.push(s);
    }
    else
    {
        qr.push(s);
    }
}

void Cloakroom::virtual_function() {}