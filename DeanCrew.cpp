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
	Put(DeanOfficeCols::idle,0,"d"+to_string(deanCrew_nr));
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
		unique_lock<std::mutex> docbuf_lck(myDeanOffice->docbuf_mutex[deanCrew_nr]); 
        	myDeanOffice->docbuf_empty[deanCrew_nr].wait(docbuf_lck);
		myDeanOffice->docbuf_mutex[deanCrew_nr].unlock();	
		getStamps();
		produce(DOC_CNT);
		freeStamps();
	}
}

void DeanCrew::getStamps()
{
	Put(DeanOfficeCols::idle,0,"  ");
	Put(DeanOfficeCols::waiting,0,"d"+to_string(deanCrew_nr));
	getStamp(first_stamp);
	Put(DeanOfficeCols::used_stamps,0,to_string(1));		
	getStamp(second_stamp);
	Put(DeanOfficeCols::used_stamps,0,to_string(2));
}
void DeanCrew::getStamp(int stamp) // actualPosition musi być DeanOffice albo zrealizowac inaczej dostęp
{
//	cout<<"PaniZDziekanatu"<<deanCrew_nr<<" czeka na pieczatke "<<stamp<<endl;			// napisz

	unique_lock<std::mutex> stamp_lck(*myDeanOffice->stamps_mutex);
  	while (!myDeanOffice->stamps[stamp]) 
		myDeanOffice->stamps_cond[stamp].wait(stamp_lck);								// Czekaj na pieczątke

	myDeanOffice->stamps[stamp] = false;												// Zajmij
//	cout<<"PaniZDziekanatu"<<deanCrew_nr<<" zajela pieczatke "<<stamp<<endl;			// napisz
	myDeanOffice->stamps_mutex->unlock();

}

void DeanCrew::freeStamps()
{
	Put(DeanOfficeCols::waiting,0,"d"+to_string(deanCrew_nr));
	freeStamp(first_stamp);
	Put(DeanOfficeCols::used_stamps,0,to_string(1));
	freeStamp(second_stamp);
	Put(DeanOfficeCols::used_stamps,0,to_string(0));
	Put(DeanOfficeCols::waiting,0,"  ");
	Put(DeanOfficeCols::idle,0,"d"+to_string(deanCrew_nr));
}

void DeanCrew::freeStamp(int stamp)
{
	myDeanOffice->stamps_mutex->lock();
	myDeanOffice->stamps[stamp] = true;												// Zwolnij pieczatke
	myDeanOffice->stamps_cond[stamp].notify_one();
	myDeanOffice->stamps_mutex->unlock();
//	cout<<"PaniZDziekanatu"<<deanCrew_nr<<" zwolnila pieczatke "<<stamp<<endl;		// napisz
}

void DeanCrew::produce(int doc_cnt) 
{
	Put(DeanOfficeCols::waiting,0,"  ");
	Put(DeanOfficeCols::working,0,"d"+to_string(deanCrew_nr));

	for(int i=0; i<doc_cnt; i++)
	{
		if(myDeanOffice->cnt[deanCrew_nr] == DOC_BUF_SIZE)
		{
			freeStamps();
			break;
		}
		else
		{
			for(int i=1;i<100;i++)
			{
				Put(DeanOfficeCols::percent,0,to_string(i));
				timer->delay(100);
			}
			Put(DeanOfficeCols::percent,0,"  ");
			makeDoc();
			Put(DeanOfficeCols::docs,0,to_string(myDeanOffice->cnt[deanCrew_nr]));
		}
	}
	Put(DeanOfficeCols::working,0,"  ");
}

void DeanCrew::makeDoc()
{
    unique_lock<std::mutex> docbuf_lck(myDeanOffice->docbuf_mutex[deanCrew_nr]);
    while(myDeanOffice->cnt[deanCrew_nr] >= DOC_BUF_SIZE) 
        myDeanOffice->docbuf_empty[deanCrew_nr].wait(docbuf_lck);
    myDeanOffice->docbuf[deanCrew_nr][myDeanOffice->head[deanCrew_nr]] = rand()%(DOC_BUF_SIZE*DOC_BUF_SIZE);      // stworzenie dokumentu i włożenie na odpowiedni stos
    myDeanOffice->head[deanCrew_nr] = (myDeanOffice->head[deanCrew_nr]+1) % DOC_BUF_SIZE; 
    myDeanOffice->cnt[deanCrew_nr]++;
//	cout<<"PaniZDziekanatu"<<deanCrew_nr<<" stworzyla dokument typu "<<deanCrew_nr<<" stos: "<<myDeanOffice->cnt[deanCrew_nr]<<endl;		// napisz
    myDeanOffice->docbuf_full[deanCrew_nr].notify_one();   
    myDeanOffice->docbuf_mutex[deanCrew_nr].unlock();
}


void DeanCrew::Put(int x, int y, string smth)
{
	int xr = Display->DeanOfficeX + x *(Display->DeanOfficeColumnsWidth+1) + Display->DeanOfficeColumnsWidth/2;
	int yr = Display->DeanOfficeY + deanCrew_nr+1;
	Display->PutChar(xr,yr,smth);
}