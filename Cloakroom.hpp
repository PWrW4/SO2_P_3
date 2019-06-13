#pragma once
#include <string>
#include "Room.hpp"
#include <mutex>
#include <vector>
#include <queue>
#include <thread>
#include "Visualization.hpp"

class Student;

class Cloakroom : public Room
{
    public:
    Cloakroom(std::string name, int capacity,Visualization * Display);
    Cloakroom();
    ~Cloakroom();

    std::thread t;

    Visualization * v;

    void enterQueue(Student* s);

    void drawQueue();

    void drawLQueue(int a);
    void drawRQueue(int a);

    std::mutex mtx_leftWieszak;
    std::mutex mtx_rightWieszak;
    std::vector<int> leftWieszak;
    std::vector<int> rightWieszak;
    std::mutex mtx_lq;
    std::mutex mtx_rq;
    std::queue <Student*> ql;
    std::queue <Student*> qr;


    void virtual_function();
};