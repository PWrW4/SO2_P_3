#pragma once
#include "Person.hpp"
#include "Room.hpp"
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "DeanOffice.hpp"
#include "Cloakroom.hpp"
#include "Corridor.hpp"
#include "Classroom.hpp"


class Student : public Person
{
    public:
        Student(int Student_nr,std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display);
        Student();
        ~Student();
        void mainLoop() override;
        void run();

        int Student_nr;
        int **request;           // tablica na tablice dokumentów danych typów - request[i][j] pole na j-ty dokument typu i
        int *doc_types_cnt;      // tablica na ilości dokumentów danych typów
        Room *nextPosition;

        std::atomic<bool> zaliczone;

        int kurtka;
        std::condition_variable studentWaitCond;
        std::mutex studentWaitMutex;
        std::atomic<bool> studentWaitBool;

        void DeanOfficeRoutine();
        void EntranceRoutine();
        void CloakroomRoutine();
        void ClassroomRoutine();
        bool generateRequest(); // false gdy student nie potrzebuje żadnego dokumentu
        void printRequest();
        void getRequest();
        void getDoc(int doc_type, int doc_slot);
        void checkStack(int doc_type);
        void randomNextPosition();

        void PutDeanOffice(int x, int y, string smth);
};