
#include "Classroom.hpp"

Classroom::Classroom(std::string name, int capacity, Visualization *Display, int _id)
    : Room(name, capacity, RoomType::E_Classroom)
{
    v = Display;
    id = _id;
    v->disp_mutex->lock();
    x = v->ClassRoomX;
    y = v->ClassRoomY;
    v->disp_mutex->unlock();

    thread thr(&Classroom::drawClass, this);
	std::swap(thr, t);
}

void Classroom::drawClass(){

}

Classroom::Classroom() {}
Classroom::~Classroom() {}

void Classroom::virtual_function() {}
