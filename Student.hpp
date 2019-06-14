#pragma once
#include "Person.hpp"
#include "Room.hpp"
#include "Toilet.hpp"
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <atomic>
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
        Student(bool *end,int Student_nr,std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display);
        Student();
        ~Student();
        void mainLoop() override;
        void run();

        int Student_nr;
        int **request;           // tablica na tablice dokumentów danych typów - request[i][j] pole na j-ty dokument typu i
        int *doc_types_cnt;      // tablica na ilości dokumentów danych typów
        Room *nextPosition;

        std::atomic<bool> zaliczone;
        std::atomic<bool> fixing;

        int kurtka;
        std::condition_variable studentWaitCond;
        std::mutex studentWaitMutex;
        std::atomic<bool> studentWaitBool;

        void DeanOfficeRoutine();
        void EntranceRoutine();
        void CloakroomRoutine();
        void ClassroomRoutine();
        void ToiletRoutine();
        bool generateRequest(); // false gdy student nie potrzebuje żadnego dokumentu
        void printRequest();
        void getRequest();
        void getDoc(int doc_type, int doc_slot);
        int ToiletDecide();
        void OccupyUri(Toilet *t);
        void OccupyCubi(Toilet *t);
        void randomNextPosition();

        void PutDeanOffice(int x, int y, string smth);
        void PutToilet(int x, int y, string smth, int color);
        void PutToilet(int x, int y, string smth);
};