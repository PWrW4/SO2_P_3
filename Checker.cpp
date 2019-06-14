#include "Checker.hpp"

Checker::Checker(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display, int id)
: Person(name,_f,status,type,actualPosition,Display)
{
    //testing
    // drawLeftSlot("ls");
    // drawRightSlot("rs");
    // drawLeftWieszak("lw");
    // drawRightWieszak("rw");
    
    chName = "s" + std::to_string(id);

    status = E_Waiting;

    checkerId = id;

    if (checkerId == 1) 
    {
        drawLeftSlot(chName);
    }else
    {
        drawRightSlot(chName);
    }
    
    this->end = false;
    c = dynamic_cast<Cloakroom *>(actualPosition);
    thread thr(&Checker::mainLoop, this);
	std::swap(thr, person_thread);
}

Checker::~Checker(){}

void Checker::mainLoop(){
    
    while (!this->end)
    {   
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (checkerId == 1)
        {
            status = E_Waiting;
            drawLeftSlot(chName);
            std::unique_lock<std::mutex> lck(c->mtx_lq);
            if (!c->ql.empty())
            {
                Student *s = c->ql.front();
                lck.unlock();
                std::unique_lock<std::mutex> lck_student(s->studentWaitMutex);
                if (s->kurtka != -1)
                {
                    int k = s->kurtka;
                    s->kurtka = -1;
                    lck_student.unlock();
                    int rnd = std::uniform_int_distribution<int>(0, 1)(rng);;
                    if (rnd == 0)
                    {
                        std::unique_lock<std::mutex> wieszak(c->mtx_rightWieszak);
                        status = E_Working;
                        drawLeftSlot(chName);
                        drawLeftSlot("  ");
                        drawRightWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        c->rightWieszak.insert(c->rightWieszak.begin(),k);
                        status = E_Waiting;
                        drawLeftSlot(chName);
                        drawRightWieszak("  ");
                    }
                    else
                    {
                        std::unique_lock<std::mutex> wieszak(c->mtx_leftWieszak);
                        status = E_Working;
                        drawLeftSlot(chName);
                        drawLeftSlot("  ");
                        drawLeftWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        c->leftWieszak.insert(c->leftWieszak.begin(),k);
                        status = E_Waiting;
                        drawLeftSlot(chName);
                        drawLeftWieszak("  ");
                    }
                    lck_student.lock();
                    s->studentWaitBool = false;
                    lck_student.unlock();
                    s->studentWaitCond.notify_one();
                }
                else
                {
                    bool czyscic = false; 
                    status = E_Accessing;
                    drawLeftSlot(chName);
                    int k = s->Student_nr;
                    int d = -1;
                    lck_student.unlock();
                    if (c->mtx_leftWieszak.try_lock())
                    {
                        drawLeftSlot("  ");
                        drawLeftWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        for (int i = 0; i < c->leftWieszak.size(); i++)
                        {
                            if (k == c->leftWieszak[i])
                            {
                                d = i;
                            }
                        }
                        if (d != -1)
                        {
                            status = E_Waiting;
                            c->leftWieszak.erase(c->leftWieszak.begin() + d);
                            drawLeftSlot(chName);
                            drawLeftWieszak("  ");
                        }
                        drawLeftWieszak("  ");
                        c->mtx_leftWieszak.unlock();
                    }
                    if (d == -1) //pętla zaczynająca od prawego
                    {
                        czyscic = true;
                        status = E_Accessing;
                        c->mtx_rightWieszak.lock();
                        drawLeftSlot("  ");
                        drawRightWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        for (int i = 0; i < c->rightWieszak.size(); i++)
                        {
                            if (k == c->rightWieszak[i])
                            {
                                d = i;
                            }
                        }
                        if (d != -1)
                        {
                            status = E_Waiting;
                            c->rightWieszak.erase(c->rightWieszak.begin() + d);
                            drawLeftSlot(chName);
                            drawRightWieszak("  ");
                            c->mtx_rightWieszak.unlock();
                        }
                        else
                        {
                            status = E_Accessing;
                            if(czyscic)drawRightWieszak("  ");     
                            c->mtx_rightWieszak.unlock();
                            c->mtx_leftWieszak.lock();                       
                            drawLeftSlot("  ");
                            drawLeftWieszak(chName);
                            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

                            for (int i = 0; i < c->leftWieszak.size(); i++)
                            {
                                if (k == c->leftWieszak[i])
                                {
                                    d = i;
                                }
                            }
                            if (d != -1)
                            {
                                status = E_Waiting;
                                c->leftWieszak.erase(c->leftWieszak.begin() + d);
                            }
                            status = E_Waiting;
                            drawLeftSlot(chName);
                            drawLeftWieszak("  ");
                            c->mtx_leftWieszak.unlock();
                        }
                    }

                    s->kurtka = k;
                    lck_student.lock();
                    s->studentWaitBool = false;
                    lck_student.unlock();
                    s->studentWaitCond.notify_one();
                }
                lck.lock();
                c->ql.pop();
                lck.unlock();
            }
        }
        if (checkerId==2)
        {
            status = E_Waiting;
            drawRightSlot(chName);
            std::unique_lock<std::mutex> lck(c->mtx_rq);
            if (!c->qr.empty())
            {
                Student *s = c->qr.front();
                lck.unlock();
                std::unique_lock<std::mutex> lck_student(s->studentWaitMutex);
                if (s->kurtka != -1)
                {
                    int k = s->kurtka;
                    s->kurtka = -1;
                    lck_student.unlock();
                    int rnd = std::uniform_int_distribution<int>(0, 1)(rng);;
                    if (rnd == 0)
                    {
                        std::unique_lock<std::mutex> wieszak(c->mtx_rightWieszak);
                        status = E_Working;
                        drawRightSlot(chName);
                        drawRightSlot("  ");
                        drawRightWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        c->rightWieszak.insert(c->rightWieszak.begin(),k);
                        status = E_Waiting;
                        drawRightSlot(chName);
                        drawRightWieszak("  ");
                    }
                    else
                    {
                        std::unique_lock<std::mutex> wieszak(c->mtx_leftWieszak);
                        status = E_Working;
                        drawRightSlot(chName);
                        drawRightSlot("  ");
                        drawLeftWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        c->leftWieszak.insert(c->leftWieszak.begin(),k);
                        status = E_Waiting;
                        drawRightSlot(chName);
                        drawLeftWieszak("  ");
                    }
                    lck_student.lock();
                    s->studentWaitBool = false;
                    lck_student.unlock();
                    s->studentWaitCond.notify_one();
                }
                else
                {
                    bool czyscic = false; 
                    status = E_Accessing;
                    drawRightSlot(chName);
                    int k = s->Student_nr;
                    int d = -1;
                    lck_student.unlock();
                    if (c->mtx_leftWieszak.try_lock())
                    {
                        drawRightSlot("  ");
                        drawLeftWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        for (int i = 0; i < c->leftWieszak.size(); i++)
                        {
                            if (k == c->leftWieszak[i])
                            {
                                d = i;
                            }
                        }
                        if (d != -1)
                        {
                            status = E_Waiting;
                            c->leftWieszak.erase(c->leftWieszak.begin() + d);
                            drawRightSlot(chName);
                            drawLeftWieszak("  ");
                        }
                        drawLeftWieszak("  ");    
                        c->mtx_leftWieszak.unlock();                    
                    }
                    if (d == -1) //pętla zaczynająca od prawego
                    {
                        czyscic = true;
                        status = E_Accessing;
                        c->mtx_rightWieszak.lock();
                        drawRightSlot("  ");
                        drawRightWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        for (int i = 0; i < c->rightWieszak.size(); i++)
                        {
                            if (k == c->rightWieszak[i])
                            {
                                d = i;
                            }
                        }
                        if (d != -1)
                        {
                            status = E_Waiting;
                            c->rightWieszak.erase(c->rightWieszak.begin() + d);
                            drawRightWieszak("  ");
                            c->mtx_rightWieszak.unlock();
                            drawRightSlot(chName);
                        }
                        else
                        {
                            status = E_Accessing;
                            if(czyscic)drawRightWieszak("  ");   
                            c->mtx_rightWieszak.unlock();
                            c->mtx_leftWieszak.lock();   
                            drawRightSlot("  ");
                            drawLeftWieszak(chName);
                            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

                            for (int i = 0; i < c->leftWieszak.size(); i++)
                            {
                                if (k == c->leftWieszak[i])
                                {
                                    d = i;
                                }
                            }
                            if (d != -1)
                            {
                                status = E_Waiting;
                                c->leftWieszak.erase(c->leftWieszak.begin() + d);
                            }
                            status = E_Waiting;
                            drawRightSlot(chName);
                            drawLeftWieszak("  ");
                            c->mtx_leftWieszak.unlock();
                        }
                    }

                    s->kurtka = k;
                    lck_student.lock();
                    s->studentWaitBool = false;
                    lck_student.unlock();
                    s->studentWaitCond.notify_one();
                }
                lck.lock();
                c->qr.pop();
                lck.unlock();
            }
        }        
    }
}

void Checker::drawLeftSlot(std::string s){
    std::unique_lock<std::mutex> locker_drawing(*Display->disp_mutex);
    int xr = Display->CloakroomY + s1X;
	int yr = Display->CloakroomX + s1Y;
    locker_drawing.unlock();
    if (status==E_Working)
    {
        Display->PutChar(xr,yr,s,WORKING_COLOR);
    }
    if (status==E_Accessing)
    {
        Display->PutChar(xr,yr,s,WAITING_COLOR);
    }
    if (status==E_Waiting)
    {
        Display->PutChar(xr,yr,s,IDLE_COLOR);
    }   
	
}

void Checker::drawRightSlot(std::string s){
    std::unique_lock<std::mutex> locker_drawing(*Display->disp_mutex);
    int xr = Display->CloakroomY + s2X;
	int yr = Display->CloakroomX + s2Y;
    locker_drawing.unlock();
	if (status==E_Working)
    {
        Display->PutChar(xr,yr,s,WORKING_COLOR);
    }
    if (status==E_Accessing)
    {
        Display->PutChar(xr,yr,s,WAITING_COLOR);
    }
    if (status==E_Waiting)
    {
        Display->PutChar(xr,yr,s,IDLE_COLOR);
    }
}
void Checker::drawLeftWieszak(std::string s){
    std::unique_lock<std::mutex> locker_drawing(*Display->disp_mutex);
    int xr = Display->CloakroomY + lwX;
	int yr = Display->CloakroomX + lwY;
    locker_drawing.unlock();
	if (status==E_Working)
    {
        Display->PutChar(xr,yr,s,WORKING_COLOR);
    }
    if (status==E_Accessing)
    {
        Display->PutChar(xr,yr,s,WAITING_COLOR);
    }
    if (status==E_Waiting)
    {
        Display->PutChar(xr,yr,s,IDLE_COLOR);
    }
}
void Checker::drawRightWieszak(std::string s){
    std::unique_lock<std::mutex> locker_drawing(*Display->disp_mutex);
    int xr = Display->CloakroomY + rwX;
	int yr = Display->CloakroomX + rwY;
    locker_drawing.unlock();
	if (status==E_Working)
    {
        Display->PutChar(xr,yr,s,WORKING_COLOR);
    }
    if (status==E_Accessing)
    {
        Display->PutChar(xr,yr,s,WAITING_COLOR);
    }
    if (status==E_Waiting)
    {
        Display->PutChar(xr,yr,s,IDLE_COLOR);
    }
}

void Checker::operator()(){}