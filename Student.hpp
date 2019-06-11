#pragma once
#include "Person.hpp"
#include "Room.hpp"
#include <condition_variable>
#include <mutex>


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

        int kurtka;
        std::condition_variable studentWaitCond;
        std::mutex studentWaitMutex;
        std::atomic<bool> studentWaitBool;

        void DeanOfficeRoutine();
        bool generateRequest(); // false gdy student nie potrzebuje żadnego dokumentu
        void printRequest();
        void getRequest();
        void getDoc(int doc_type, int doc_slot);
        void checkStack(int doc_type);

        void PutDeanOffice(int x, int y, string smth);
};