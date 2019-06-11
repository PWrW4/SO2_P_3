#include "Cloakroom.hpp"

Cloakroom::Cloakroom(std::string name, int capacity)
    : Room(name, capacity, RoomType::E_Cloakroom)
{
}

Cloakroom::Cloakroom() {}
Cloakroom::~Cloakroom() {}

void Cloakroom::enterQueue(Student *s)
{
    std::lock(mtx_lq, mtx_rq);
    std::unique_lock<std::mutex> left_lock(mtx_lq, std::adopt_lock);
    std::unique_lock<std::mutex> right_lock(mtx_rq, std::adopt_lock);

    if (ql.size() < qr.size())
    {
        ql.push(s);
    }
    else
    {
        qr.push(s);
    }
}

void Cloakroom::virtual_function() {}