#pragma once
#include "Person.hpp"
#include "Room.hpp"
#include "DeanOffice.hpp"

class DeanCrew : public Person
{
    public:
        DeanCrew(int deanCrew_nr, int deanCrew_cnt, int doc_type, std::string name,Floor * _f, Status status,Room *actualPosition, Room *myDeanOffice);
        DeanCrew();
        ~DeanCrew();

        DeanOffice *myDeanOffice;

        int deanCrew_nr;
	    int deanCrew_cnt;
        int doc_type;                   // id typu produkowanych dokumentów (stosu dokumentów): od 0 do (DOC_TYPES-1)
        int first_stamp, second_stamp;  // id przysługujących pracownikowi pieczątek, współdzielone
        bool left_first;                // która pieczątka pierwsza do zabrania -> rozwiązanie deadlock
        
        void run();
        void mainLoop() override;

        void getStamps();
        void getStamp(int stamp);       // pobierz pieczątkę first_stamp lub second_stamp
        void freeStamps();
        void freeStamp(int stamp);      // zwolnij pieczątkę first_stamp lub second_stamp
        void produce(int doc_cnt);      // wyprodukuj doc_cnt dokumentów
        void makeDoc();                 // wyprodukuj jeden dokument


};