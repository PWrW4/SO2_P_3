#include "DeanCrew.hpp"
#include "DeanOffice.hpp"

using namespace std;

DeanCrew::DeanCrew(int deanCrew_nr, int deanCrew_cnt, int doc_type, std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition)
    : Person(name,_f,status,type,actualPosition),
    deanCrew_nr(deanCrew_nr),
    deanCrew_cnt(deanCrew_cnt),
    doc_type(doc_type)
{
	progress_bar="";

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
	unique_lock<std::mutex> stamp_lck(actualPosition->stamps_mutex[deanCrew_nr]);
  	while (!actualPosition->stamps[stamp]) 
		actualPosition->stamps_cond[stamp].wait(stamp_lck);								                    // Czekaj na pieczątke

	actualPosition->stamps[stamp] = false;												// Zajmij
	actualPosition->stamps_mutex[deanCrew_nr]->unlock();
}

void DeanCrew::produce() // actualPosition musi być DeanOffice albo zrealizowac inaczej dostęp
{
    unique_lock<std::mutex> docbuf_lck(actualPosition->docbuf_mutex[deanCrew_nr]);
    while(actualPosition->cnt >= DOC_BUF_SIZE) 
        actualPosition->docbuf_empty[deanCrew_nr].wait(docbuf_lck);
    //actualPosition->docbuf[actualPosition->head] = jakaś_liczba;      // stworzenie dokumentu i włożenie na odpowiedni stos
    actualPosition->head = (actualPosition->head+1) % DOC_BUF_SIZE; 
    actualPosition->cnt++;
    actualPosition->docbuf_full[deanCrew_nr].notify_one();   
    actualPosition->docbuf_mutex[deanCrew_nr]->unlock();
}