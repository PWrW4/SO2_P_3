#pragma once
#include "Person.hpp"
#include "Room.hpp"

class Student : public Person
{
    public:
        Student(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition);
        Student();
        ~Student();
        void mainLoop() override;
        void operator()();

        int **request;           // tablica na tablice dokumentów danych typów - request[i][j] pole na j-ty dokument typu i
        int *doc_types_cnt;      // tablica na ilości dokumentów danych typów


        void DeanOfficeRoutine();
        void generateRequest();
        void printRequest();
        void getRequest();
        void getDoc(int doc_type);
        void checkStack(int doc_type);
};