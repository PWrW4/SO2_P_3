#pragma once
#include <string>
#include <vector>
#include <thread>
#include "Visualization.hpp"
#include "Room.hpp"
#include "Person.hpp"
#include "Student.hpp"
#include "Lecturer.hpp"
#include <queue>
#include <mutex>

class Person;

class Classroom : public Room
{
public:
    Classroom(std::string name, int capacity,Visualization * Display, int _id);
    Classroom();
    ~Classroom();

    std::thread t;

    int id;
    Visualization * v;
    int x,y;


    std::mutex mtx_stanowiska;
    std::vector<Student *> stanowiska;
    std::mutex mtx_nauczyciel;
    std::vector<Lecturer *> nauczyciel;
    std::mutex mtx_q;
    std::queue <int> q;

    void studentEnter(Student * s);

    void drawClass();
    void drawStanowisko(int nr);

    void virtual_function();

};