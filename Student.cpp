#include <chrono>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Student.hpp"
#include "DeanOffice.hpp"

Student::Student(int Student_nr,std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display)
: Person(name,_f,status,type,actualPosition,Display)
{
    Student_nr = Student_nr;
    thread thr(&Student::run, this);
	std::swap(thr, person_thread);
}

void Student::mainLoop(){
    int sleep = 0;
    while (!this->end)
    {
        this->actualPosition->typeMutex.lock();
        RoomType t = this->actualPosition->type;
        this->actualPosition->typeMutex.unlock();
        switch (t)
        {
        case E_Entrance:
            sleep = std::uniform_int_distribution<int>(15, 30)(rng);
            std::this_thread::sleep_for(std::chrono::milliseconds(100*sleep));
            //travel()
            break;
        case E_Corridor:
            sleep = std::uniform_int_distribution<int>(15, 30)(rng);
            std::this_thread::sleep_for(std::chrono::milliseconds(100*sleep));
            //travel()
            break;
        
        default:
            break;
        }
    }    
}

void Student::run()
{
    if(generateRequest())
 //       travel(dziekanat);
 {
    for(int i=0;i<rand()%(STAMPS_CNT+1);i++)
    {
        int docs_type = rand()%STAMPS_CNT;       
        getDoc(docs_type,rand()%STAMPS_CNT);      
//      printRequest();
//      timer->delay();
    }
 }
}

void Student::DeanOfficeRoutine()
{

}

bool Student::generateRequest()
{
    request = new int*[DOC_TYPES];            // tablica na tablice dokumentów danych typów
    doc_types_cnt = new int[DOC_TYPES];        // tablica na ilości dokumentów danych typów
    int sum = 0;
    for(int i=0;i<DOC_TYPES;i++)
    {
        doc_types_cnt[i] = rand()%3;
        sum += doc_types_cnt[i];
        //request[i]= new int[doc_types_cnt[i]];      // tablica na doc_types_cnt[i] dokumentów typu i
        request[i]= new int[DOC_TYPES];
        //for(int j=0;j<doc_types_cnt[i];j++)
        for(int j=0;j<DOC_TYPES;j++)
        {
            request[i][j]=0;                        // puste pole na j-ty dokument typu i
        }
    }
    //if(sum != 0)
        return true;
    //else
        //return false;
}

void Student::printRequest()
{
    cout<<"typ  | sloty na dokumenty\n"<<"----------------------------";
    for(int i=0;i<DOC_TYPES;i++)
    {
        cout<<endl<<i<<".   |";
        //for(int j=0;j<doc_types_cnt[i];j++)
        for(int j=0;j<DOC_TYPES;j++)
        {
            cout<<request[i][j]<<"  ";
        }
    }
    cout<<endl;
}

void Student::getRequest()
{

}

void Student::getDoc(int doc_type, int doc_slot)
{
    DeanOffice *myDeanOffice;
    if(actualPosition->type == E_DeanOffice)
        myDeanOffice = dynamic_cast<DeanOffice *>(actualPosition);

    myDeanOffice->docbuf_mutex[doc_type].lock();
    int index = myDeanOffice->ques->at(doc_type);
    PutDeanOffice(stud+index,doc_type,"s");
    myDeanOffice->ques->at(doc_type)++;
    myDeanOffice->docbuf_mutex[doc_type].unlock();

    unique_lock<std::mutex> docbuf_lck(myDeanOffice->docbuf_mutex[doc_type]);
//    cout<<"mutex lock Student\n";
    while(myDeanOffice->cnt[doc_type] <= 0)
    { 
            myDeanOffice->docbuf_empty[doc_type].notify_one(); // kolejka pusta, powiadom pania z dziekanatu 
            // cout<<"Student signaled empty\n";
        myDeanOffice->docbuf_full[doc_type].wait(docbuf_lck);
//        cout<<"Student wait for doc\n";
    }
    request[doc_type][doc_slot] = myDeanOffice->docbuf[doc_type][myDeanOffice->tail[doc_type]];      // pobranie dokumentu i włożenie na odpowiednie miejsce
    myDeanOffice->tail[doc_type] = (myDeanOffice->tail[doc_type]+1) % DOC_BUF_SIZE; 
    myDeanOffice->cnt[doc_type]--;
//	cout<<"Student"<<name<<" odebrał dokument typu "<<doc_type<<" stos: "<<myDeanOffice->cnt[doc_type]<<endl;		// napisz
    myDeanOffice->docbuf_empty[doc_type].notify_one();   
    myDeanOffice->docbuf_mutex[doc_type].unlock();

    PutDeanOffice(docs,doc_type,to_string(myDeanOffice->cnt[doc_type]));

    myDeanOffice->docbuf_mutex[doc_type].lock();
    myDeanOffice->ques->at(doc_type)--;
    index = myDeanOffice->ques->at(doc_type);
    PutDeanOffice(stud+index,doc_type," ");
    myDeanOffice->docbuf_mutex[doc_type].unlock();
}

void Student::checkStack(int doc_type)
{

}

void Student::PutDeanOffice(int x, int y, string smth)
{
	int xr = Display->DeanOfficeX + x *(Display->DeanOfficeColumnsWidth+1) + Display->DeanOfficeColumnsWidth/2;
	int yr = Display->DeanOfficeY + y+1;
	Display->PutChar(xr,yr,smth);
}