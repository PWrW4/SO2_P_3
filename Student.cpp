#include "Student.hpp"
#include <chrono>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "DeanOffice.hpp"
#include "Cloakroom.hpp"
#include "Classroom.hpp"



Student::Student(int Student_nr,std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display)
: Person(name,_f,status,type,actualPosition,Display)
{
    this->Student_nr = Student_nr;
    kurtka = this->Student_nr;
    thread thr(&Student::run, this);
    // thread thr(&Student::mainLoop, this);
	std::swap(thr, person_thread);
}

void Student::mainLoop()
{
    int room_type=0;
    while (!this->end)
    {
        this->actualPosition->typeMutex.lock();
        RoomType t = this->actualPosition->type;
        this->actualPosition->typeMutex.unlock();
        switch (t)
        {
        case E_Entrance:
        {
            EntranceRoutine();
            break;
        }
        case E_Corridor:
        {
            RoomType rtype;

            timer->delay(2500,3500); // wait for random time between 2,5s and 3,5s

            switch(room_type%4)
            {
                case 0:
                    rtype =  E_Entrance;
                    break;
                case 1:
                    rtype =  E_Cloakroom;
                    break;
                case 2:
                    rtype =  E_DeanOffice;
                    break;
                case 3:
                    rtype = E_Classroom;
                    break;
                default:
                    break;
            }
            Room *cRoom = nullptr;
            int cId = 0;
            if (rtype==E_Classroom)
            {
                cId = rand() % 5;
            }
            
            for (Room * r : f.floorRooms)
            {
                if (rtype == E_Classroom)
                {
                    if (r->type == rtype)
                    {
                        if (dynamic_cast<Classroom *>(r)->id == cId)
                        {
                            travel(r);
                        }
                    }
                }
                else
                {
                    if (r->type == rtype)
                        travel(r);
                }
            }
            break;
        }
        case E_DeanOffice:
        {
            DeanOfficeRoutine();
            break;
        }
        case E_Cloakroom:
        {
            CloakroomRoutine();
            break;
        }
        case E_Classroom:
            ClassroomRoutine();
            break;
        default:
            break;
        }
        room_type++;
    }    
}

// void Student::run()
// {
//     if(generateRequest())
//  //       travel(dziekanat);
//  {
//     for(int i=0;i<rand()%(STAMPS_CNT+1);i++)
//     {
//         int docs_type = rand()%STAMPS_CNT;       
//         getDoc(docs_type,rand()%STAMPS_CNT);      
// //      printRequest();
// //      timer->delay();
//     }
//  }
// }
//
// void Student::run()
// {
//     int sleep = 0;
//     sleep = std::uniform_int_distribution<int>(15, 30)(rng);
//     std::this_thread::sleep_for(std::chrono::milliseconds(100 * sleep));
//     for (auto &r : f.floorRooms)
//     {
//         if (r->type == E_Corridor)
//         {
//             travel(r);
//         }
//     }
//     sleep = std::uniform_int_distribution<int>(15, 30)(rng);
//     std::this_thread::sleep_for(std::chrono::milliseconds(100 * sleep));
//     Room *cRoom = nullptr;
//     for (Room * r : f.floorRooms)
//     {
//         if (r->type == E_Cloakroom)
//         {
//             travel(r);
//             cRoom = r;
//         }
//     }

//     Cloakroom *c = dynamic_cast<Cloakroom *>(cRoom);
//     c->enterQueue(this);
//     studentWaitBool = true;
//     unique_lock<std::mutex> queue_lck(studentWaitMutex);
//     while (studentWaitBool)
//         studentWaitCond.wait(queue_lck);

//     //ten sleap nie potrzebny
//     // sleep = std::uniform_int_distribution<int>(15, 30)(rng);
//     // std::this_thread::sleep_for(std::chrono::milliseconds(100 * sleep));
//     for (auto &r : f.floorRooms)
//     {
//         if (r->type == E_Corridor)
//         {
//             travel(r);
//         }
//     }
// }

void Student::run()
{
    mainLoop();
}

void Student::DeanOfficeRoutine()
{
    generateRequest();
    for(int i=0;i<rand()%(STAMPS_CNT+1);i++)
    {
        int docs_type = rand()%STAMPS_CNT;       
        getDoc(docs_type,rand()%STAMPS_CNT);      
//      printRequest();
//      timer->delay();
    }
    for (auto &r : f.floorRooms)
    {
        if (r->type == E_Corridor)
        {
            while(travel(r)==-1);
        }
    }
}

void Student::EntranceRoutine()
{
    timer->delay(3000,5000);

    for (auto &r : f.floorRooms)
    {
        if (r->type == E_Corridor)
        {
            while(travel(r)==-1);
        }
    }
}

void Student::CloakroomRoutine()
{   
    Room *cRoom;
    cRoom = this->actualPosition;
    Cloakroom *c = dynamic_cast<Cloakroom *>(cRoom);
    c->enterQueue(this);
    studentWaitBool = true;
    unique_lock<std::mutex> queue_lck(studentWaitMutex);
    while(studentWaitBool) 
        studentWaitCond.wait(queue_lck);

    timer->delay(15,30);
    
    for (auto &r : f.floorRooms)
    {
        if (r->type == E_Corridor)
        {
            while(travel(r)==-1);
        }
    }
}

void Student::ClassroomRoutine(){
    Room *cRoom;
    cRoom = this->actualPosition;
    Classroom *c = dynamic_cast<Classroom *>(cRoom);
    c->studentEnter(this);
    zaliczone = false;
    studentWaitBool = true;
    unique_lock<std::mutex> class_lck(studentWaitMutex);
    
    while (!zaliczone)
    {
        while(studentWaitBool) 
            studentWaitCond.wait(class_lck);
    }      

    timer->delay(15,30);
    
    for (auto &r : f.floorRooms)
    {
        if (r->type == E_Corridor)
        {
            travel(r);
        }
    }
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

    unique_lock<std::mutex> queue_lck(myDeanOffice->queue_mutex[doc_type]); // blokada kolejki
    //myDeanOffice->queue_mutex[doc_type].lock();
    while(myDeanOffice->que->at(doc_type).size()>=STAMPS_CNT)                    // sprawdź czy jest miejsce
        myDeanOffice->queue_changed[doc_type].wait(queue_lck);      // czekaj na wolne miejsce w kolejce

    myDeanOffice->que->at(doc_type).push(Student_nr);               // Student ustawia się w kolejce
    int index = myDeanOffice->ques->at(doc_type);
    PutDeanOffice(stud+index,doc_type,"s");                         // wizualizuj ustawienie się w kolejce na odpowiednim miejscu
    myDeanOffice->ques->at(doc_type)++;                             // indeks kolejnego miejsca w kolejce

//Display->PutChar(50,50+doc_type,to_string(myDeanOffice->ques->at(doc_type)));

    while(myDeanOffice->que->at(doc_type).front() != Student_nr)    // Student sprawdza czy jego kolej
        myDeanOffice->queue_changed[doc_type].wait(queue_lck);      // czekaj na swoją kolej
    myDeanOffice->queue_mutex[doc_type].unlock();                   // zwolnij kolejke


    unique_lock<std::mutex> docbuf_lck(myDeanOffice->docbuf_mutex[doc_type]);   // blokada stosu
//    cout<<"mutex lock Student\n";
    while(myDeanOffice->cnt[doc_type] <= 0)
    { 
        if(!myDeanOffice->isWorking[doc_type])
        {
            myDeanOffice->isWorking[doc_type] = true;
            myDeanOffice->docbuf_empty[doc_type].notify_one();      // kolejka pusta, powiadom pania z dziekanatu 
        }
            // cout<<"Student signaled empty doc stack\n";
        myDeanOffice->docbuf_full[doc_type].wait(docbuf_lck);       // czekaj na pojawienie się dokumentów - odblokuj dostęp do stosu
//        cout<<"Student wait for doc\n";
    }                                                               // blokada stosu
    request[doc_type][doc_slot] = myDeanOffice->docbuf[doc_type][myDeanOffice->tail[doc_type]];      // pobranie dokumentu i włożenie na odpowiednie miejsce
    myDeanOffice->tail[doc_type] = (myDeanOffice->tail[doc_type]+1) % DOC_BUF_SIZE; 
    myDeanOffice->cnt[doc_type]--;
    PutDeanOffice(docs,doc_type,to_string(myDeanOffice->cnt[doc_type]));    // aktualizacja stanu stosu
    myDeanOffice->docbuf_empty[doc_type].notify_one();              // powiadom pania z dziekanatu o zwolnionym miejscu na stosie w razie jakby czekała
    myDeanOffice->docbuf_mutex[doc_type].unlock();                  // odblokuj dostęp do stosu



    myDeanOffice->queue_mutex[doc_type].lock();                     // blokada kolejki
    myDeanOffice->que->at(doc_type).pop();                          // student był pierwszy, pobrał dokument, wychodzi z kolejki
    myDeanOffice->ques->at(doc_type)--;                             // indeks zwolnionego miejsca w kolejce ( na końcu )
    
//Display->PutChar(50,50+doc_type,to_string(myDeanOffice->ques->at(doc_type)));

    index = myDeanOffice->ques->at(doc_type);
    PutDeanOffice(stud+index,doc_type," ");                         // wizualizacja zwolnionego miejsca i przesunięcia kolejki
    myDeanOffice->queue_changed[doc_type].notify_all();             // powiadom studentów o zmianie kolejki - niech sprawdzą czy ich kolej
    myDeanOffice->queue_mutex[doc_type].unlock();                   // zwolnij kolejkę
}

void Student::checkStack(int doc_type)
{

}

void Student::randomNextPosition()
{
    int max_index = f.floorRooms.size();
    int rand_index = 0;
    Room *r = actualPosition;            // metoda powinna być wywoływana tylko w korytarzu
    while(r->type == E_Corridor)         // zatem pętla się wykona minimum raz
    {
        rand_index = rand() % max_index;
        r = f.floorRooms[rand_index];
    }
}
void Student::PutDeanOffice(int x, int y, string smth)
{
	int xr = Display->DeanOfficeX + x *(Display->DeanOfficeColumnsWidth+1) + Display->DeanOfficeColumnsWidth/2;
	int yr = Display->DeanOfficeY + y+1;
	Display->PutChar(xr,yr,smth);
}

// void Student::run()
// {
//     Room *cRoom = nullptr;
//     int sleep = 0;

//     sleep = std::uniform_int_distribution<int>(15, 30)(rng);
//     std::this_thread::sleep_for(std::chrono::milliseconds(100 * sleep));
//     for (auto &r : f.floorRooms)
//     {
//         if (r->type == E_Corridor)
//         {
//             while (travel(r) == -1)
//                 ;
//         }
//     }
//     sleep = std::uniform_int_distribution<int>(15, 30)(rng);
//     std::this_thread::sleep_for(std::chrono::milliseconds(100 * sleep));

//     for (Room *r : f.floorRooms)
//     {
//         if (r->type == E_Cloakroom)
//         {
//             while (travel(r) == -1)
//                 ;
//             cRoom = r;
//         }
//     }

//     Cloakroom *c = dynamic_cast<Cloakroom *>(cRoom);
//     c->enterQueue(this);
//     studentWaitBool = true;
//     unique_lock<std::mutex> queue_lck(studentWaitMutex);
//     while (studentWaitBool)
//         studentWaitCond.wait(queue_lck);

//     //ten sleap nie potrzebny
//     // sleep = std::uniform_int_distribution<int>(15, 30)(rng);
//     // std::this_thread::sleep_for(std::chrono::milliseconds(100 * sleep));
//     for (auto &r : f.floorRooms)
//     {
//         if (r->type == E_Corridor)
//         {
//             while (travel(r) == -1)
//                 ;
//         }
//     }

//     sleep = std::uniform_int_distribution<int>(15, 30)(rng);
//     std::this_thread::sleep_for(std::chrono::milliseconds(100 * sleep));
//     for (Room *r : f.floorRooms)
//     {
//         if (r->type == E_Entrance)
//         {
//             while (travel(r) == -1)
//                 ;
//         }
//     }
// }
