#include <ctime>
#include <cstdlib>
#include "DeanCrew.hpp"

using namespace std;

DeanCrew::DeanCrew(int deanCrew_nr, int deanCrew_cnt, int doc_type, std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition, Room *myDeanOffice)
    : Person(name,_f,status,type,actualPosition),
    deanCrew_nr(deanCrew_nr),
    deanCrew_cnt(deanCrew_cnt),
    doc_type(doc_type)
{
	srand(time(NULL));
	progress_bar="";
	this->myDeanOffice = dynamic_cast<DeanOffice *>(myDeanOffice);

	first_stamp = deanCrew_nr;
	if (deanCrew_nr == 0)
		second_stamp = deanCrew_cnt - 1;
	else
		second_stamp = deanCrew_nr - 1;
	if(first_stamp<second_stamp)				// Ustal kolejnosc pieczątek
		left_first = true;
	else
	{
		left_first = false;
		swap(first_stamp,second_stamp);		    // zamień jeśli trzeba
	}
}

void DeanCrew::mainLoop(){}

void DeanCrew::operator()(){}

void DeanCrew::getStamp(int stamp) // actualPosition musi być DeanOffice albo zrealizowac inaczej dostęp
{
	unique_lock<std::mutex> stamp_lck(myDeanOffice->stamps_mutex[deanCrew_nr]);
  	while (!myDeanOffice->stamps[stamp]) 
		myDeanOffice->stamps_cond[stamp].wait(stamp_lck);								                    // Czekaj na pieczątke

	myDeanOffice->stamps[stamp] = false;												// Zajmij
	myDeanOffice->stamps_mutex[deanCrew_nr].unlock();
}

void DeanCrew::produce() // actualPosition musi być DeanOffice albo zrealizowac inaczej dostęp
{
    unique_lock<std::mutex> docbuf_lck(myDeanOffice->docbuf_mutex[deanCrew_nr]);
    while(myDeanOffice->cnt[deanCrew_nr] >= DOC_BUF_SIZE) 
        myDeanOffice->docbuf_empty[deanCrew_nr].wait(docbuf_lck);
    myDeanOffice->docbuf[deanCrew_nr][myDeanOffice->head] = rand();      // stworzenie dokumentu i włożenie na odpowiedni stos
    myDeanOffice->head[deanCrew_nr] = (myDeanOffice->head[deanCrew_nr]+1) % DOC_BUF_SIZE; 
    myDeanOffice->cnt[deanCrew_nr]++;
    myDeanOffice->docbuf_full[deanCrew_nr].notify_one();   
    myDeanOffice->docbuf_mutex[deanCrew_nr].unlock();
}