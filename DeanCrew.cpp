#include <ctime>
#include <thread>
#include <cstdlib>
#include "DeanCrew.hpp"

using namespace std;

DeanCrew::DeanCrew(int deanCrew_nr, int deanCrew_cnt, int doc_type, std::string name,Floor * _f, Status status, Room *actualPosition, Room *myDeanOffice,Visualization * Display)
    : Person(name,_f,status,E_DziekanatCrew,actualPosition, Display),
    deanCrew_nr(deanCrew_nr),
    deanCrew_cnt(deanCrew_cnt),
    doc_type(doc_type)
{
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
	Put(DeanOfficeCols::idle,0,"d"+to_string(deanCrew_nr),IDLE_COLOR);

	Put(DeanOfficeCols::used_stamps,0,to_string(0));
	Put(DeanOfficeCols::docs,0,to_string(this->myDeanOffice->cnt[deanCrew_nr]));
	thread thr(&DeanCrew::run, this);
	std::swap(thr, person_thread);
}

DeanCrew::~DeanCrew(){}

void DeanCrew::run()
{
	mainLoop();
}

void DeanCrew::mainLoop()
{
	//travel(myDeanOffice);
	//for(int i=0;i<4;i++)
	while(1)
	{
		//cout<<"DeanCrew"<<deanCrew_nr<<" arrival"<<endl;
		// unique_lock<std::mutex> docbuf_lck(myDeanOffice->docbuf_mutex[deanCrew_nr]);
		// cout<<"mutex lock DeanCrew"<<deanCrew_nr<<endl;
    	// while(myDeanOffice->cnt[deanCrew_nr] > 0)
    	// { 
        // 	myDeanOffice->docbuf_empty[deanCrew_nr].wait(docbuf_lck);
		// 	cout<<"DeanCrew"<<deanCrew_nr<<" wait for empty signal\n";
    	// }
		// myDeanOffice->docbuf_mutex[deanCrew_nr].unlock();
		// czekaj na powiadomienie o braku dokumentów
		// wtedy zacznij procedure produkcji
		unique_lock<std::mutex> docbuf_lck(myDeanOffice->docbuf_mutex[deanCrew_nr]);	// blokada stosu
        while(!myDeanOffice->isWorking[deanCrew_nr])
		{
			myDeanOffice->docbuf_full[deanCrew_nr].notify_all();							// wyślij powiadomienie o oczekiwaniu na prace do wykonania  
			myDeanOffice->docbuf_empty[deanCrew_nr].wait(docbuf_lck);					// czekaj na powiadomienie o pustym stosie dokumentów
		}
		myDeanOffice->docbuf_mutex[deanCrew_nr].unlock();								// odblokuj stos
		getStamps();																	// pobranie pieczątek
		produce(DOC_CNT);																// produkuj N dokumentów
		freeStamps();																	// zwolnij pieczątki
	}
}

void DeanCrew::getStamps()
{
		Put(DeanOfficeCols::idle,0,"  ");

		Put(DeanOfficeCols::waiting,0,"d"+to_string(deanCrew_nr),WAITING_COLOR);

	getStamp(first_stamp);
		Put(DeanOfficeCols::used_stamps,0,to_string(1));		
	getStamp(second_stamp);
		Put(DeanOfficeCols::used_stamps,0,to_string(2));
}
void DeanCrew::getStamp(int stamp) // actualPosition musi być DeanOffice albo zrealizowac inaczej dostęp
{
//	cout<<"PaniZDziekanatu"<<deanCrew_nr<<" czeka na pieczatke "<<stamp<<endl;			// napisz

	unique_lock<std::mutex> stamp_lck(*myDeanOffice->stamps_mutex);						// blokuj pieczatki
  	while (!myDeanOffice->stamps[stamp]) 												// czy pieczątka wolna
		myDeanOffice->stamps_cond[stamp].wait(stamp_lck);								// Czekaj na zwolnienie

	myDeanOffice->stamps[stamp] = false;												// Zajmij
	myDeanOffice->stamps_mutex->unlock();
//	cout<<"PaniZDziekanatu"<<deanCrew_nr<<" zajela pieczatke "<<stamp<<endl;			// napisz

}

void DeanCrew::freeStamps()
{
		Put(DeanOfficeCols::waiting,0,"d"+to_string(deanCrew_nr),WAITING_COLOR);
	freeStamp(first_stamp);
		Put(DeanOfficeCols::used_stamps,0,to_string(1));
	freeStamp(second_stamp);
		Put(DeanOfficeCols::used_stamps,0,to_string(0));
		Put(DeanOfficeCols::waiting,0,"  ");
		Put(DeanOfficeCols::idle,0,"d"+to_string(deanCrew_nr),IDLE_COLOR);
}

void DeanCrew::freeStamp(int stamp)
{
	myDeanOffice->stamps_mutex->lock();
	myDeanOffice->stamps[stamp] = true;												// Zwolnij pieczatke
	myDeanOffice->stamps_cond[stamp].notify_one();									// powiadom o zwolnieniu
	myDeanOffice->stamps_mutex->unlock();
//	cout<<"PaniZDziekanatu"<<deanCrew_nr<<" zwolnila pieczatke "<<stamp<<endl;		// napisz
}

void DeanCrew::produce(int doc_cnt) 
{
		Put(DeanOfficeCols::waiting,0,"  ");
		Put(DeanOfficeCols::working,0,"d"+to_string(deanCrew_nr),WORKING_COLOR);

	for(int i=0; i<doc_cnt; i++)
	{
		myDeanOffice->docbuf_mutex[deanCrew_nr].lock();								// blokuj stos 
		if(myDeanOffice->cnt[deanCrew_nr] == DOC_BUF_SIZE)							// sprawdź czy pełny
		{
			myDeanOffice->docbuf_mutex[deanCrew_nr].unlock();
			freeStamps();															// zwolnij pieczątki
			break;																	// przerwij produkcję
		}
		else
		{
			myDeanOffice->docbuf_mutex[deanCrew_nr].unlock();
			for(int i=1;i<100;i++)
			{
				Put(DeanOfficeCols::percent,0,to_string(i));						// postęp - procenty
				timer->delay(100);
			}
			Put(DeanOfficeCols::percent,0,"  ");
			makeDoc();																// twórz dokument
		}
	}
	myDeanOffice->docbuf_mutex[deanCrew_nr].lock();
		myDeanOffice->isWorking[deanCrew_nr] = false;
	myDeanOffice->docbuf_mutex[deanCrew_nr].unlock();
	Put(DeanOfficeCols::working,0,"  ");
}

void DeanCrew::makeDoc()
{
    unique_lock<std::mutex> docbuf_lck(myDeanOffice->docbuf_mutex[deanCrew_nr]);	// blokuj stos
    while(myDeanOffice->cnt[deanCrew_nr] >= DOC_BUF_SIZE) 							// sprawdź czy jest miejsce na nowy dokument
        myDeanOffice->docbuf_empty[deanCrew_nr].wait(docbuf_lck);					// czekaj na zwolnienie miejsca (wątek blokuje pieczątki!) - problem zlikwidowany
    myDeanOffice->docbuf[deanCrew_nr][myDeanOffice->head[deanCrew_nr]] = std::uniform_int_distribution<int>(0, (DOC_BUF_SIZE*DOC_BUF_SIZE)-1)(rng);    	// stworzenie dokumentu i włożenie na odpowiedni stos
    myDeanOffice->head[deanCrew_nr] = (myDeanOffice->head[deanCrew_nr]+1) % DOC_BUF_SIZE;							// bufor cykliczny - aktualizacja głowy
    myDeanOffice->cnt[deanCrew_nr]++;												// zwiększ ilość dokumentów na stosie
//	cout<<"PaniZDziekanatu"<<deanCrew_nr<<" stworzyla dokument typu "<<deanCrew_nr<<" stos: "<<myDeanOffice->cnt[deanCrew_nr]<<endl;		// napisz
    myDeanOffice->docbuf_full[deanCrew_nr].notify_all();							// powiadom o dodaniu dokumentu
	Put(DeanOfficeCols::docs,0,to_string(myDeanOffice->cnt[deanCrew_nr]));   		// wizualizacja - aktualna liczba dokumentow na stosie
    myDeanOffice->docbuf_mutex[deanCrew_nr].unlock();								// odblokuj stos
}


void DeanCrew::Put(int x, int y, string smth,int color)
{
	int xr = Display->DeanOfficeX + x *(Display->DeanOfficeColumnsWidth+1) + Display->DeanOfficeColumnsWidth/2;
	int yr = Display->DeanOfficeY + deanCrew_nr+1;
	Display->PutChar(xr,yr,smth,color);
}

void DeanCrew::Put(int x, int y, string smth)
{
	int xr = Display->DeanOfficeX + x *(Display->DeanOfficeColumnsWidth+1) + Display->DeanOfficeColumnsWidth/2;
	int yr = Display->DeanOfficeY + deanCrew_nr+1;
	Display->PutChar(xr,yr,smth);
}