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

void Checker::mainLoop(){
    
    while (!this->end)
    {   
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        if (checkerId == 1)
        {
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
                    int rnd = rand() % 2;
                    if (rnd == 0)
                    {
                        std::unique_lock<std::mutex> wieszak(c->mtx_rightWieszak);
                        drawLeftSlot("  ");
                        drawRightWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        c->rightWieszak.insert(c->rightWieszak.end(),k);
                        drawLeftSlot(chName);
                        drawRightWieszak("  ");
                    }
                    else
                    {
                        drawLeftSlot("  ");
                        drawLeftWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        std::unique_lock<std::mutex> wieszak(c->mtx_leftWieszak);
                        c->leftWieszak.insert(c->rightWieszak.end(),k);
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
                            c->leftWieszak.erase(c->leftWieszak.begin() + d);
                        }
                        c->mtx_leftWieszak.unlock();
                        drawLeftSlot(chName);
                        drawLeftWieszak("  ");
                    }
                    if (d != -1) //pętla zaczynająca od prawego
                    {
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
                            c->rightWieszak.erase(c->leftWieszak.begin() + d);
                            c->mtx_rightWieszak.unlock();
                            drawLeftSlot(chName);
                            drawRightWieszak("  ");
                        }
                        else
                        {
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
                                c->leftWieszak.erase(c->leftWieszak.begin() + d);
                            }
                            c->mtx_leftWieszak.unlock();
                            drawLeftSlot(chName);
                            drawLeftWieszak("  ");
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
                    int rnd = rand() % 2;
                    if (rnd == 0)
                    {
                        std::unique_lock<std::mutex> wieszak(c->mtx_rightWieszak);
                        drawRightSlot("  ");
                        drawRightWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        c->rightWieszak.insert(c->rightWieszak.end(),k);
                        drawRightSlot(chName);
                        drawRightWieszak("  ");
                    }
                    else
                    {
                        drawRightSlot("  ");
                        drawLeftWieszak(chName);
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        std::unique_lock<std::mutex> wieszak(c->mtx_leftWieszak);
                        c->leftWieszak.insert(c->rightWieszak.end(),k);
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
                            c->leftWieszak.erase(c->leftWieszak.begin() + d);
                        }
                        c->mtx_leftWieszak.unlock();
                        drawRightSlot(chName);
                        drawLeftWieszak("  ");
                    }
                    if (d != -1) //pętla zaczynająca od prawego
                    {
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
                            c->rightWieszak.erase(c->leftWieszak.begin() + d);
                            c->mtx_rightWieszak.unlock();
                            drawRightSlot(chName);
                            drawRightWieszak("  ");
                        }
                        else
                        {
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
                                c->leftWieszak.erase(c->leftWieszak.begin() + d);
                            }
                            c->mtx_leftWieszak.unlock();
                            drawRightSlot(chName);
                            drawLeftWieszak("  ");
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
	Display->PutChar(xr,yr,s);
}
void Checker::drawRightSlot(std::string s){
    std::unique_lock<std::mutex> locker_drawing(*Display->disp_mutex);
    int xr = Display->CloakroomY + s2X;
	int yr = Display->CloakroomX + s2Y;
    locker_drawing.unlock();
	Display->PutChar(xr,yr,s);
}
void Checker::drawLeftWieszak(std::string s){
    std::unique_lock<std::mutex> locker_drawing(*Display->disp_mutex);
    int xr = Display->CloakroomY + lwX;
	int yr = Display->CloakroomX + lwY;
    locker_drawing.unlock();
	Display->PutChar(xr,yr,s);
}
void Checker::drawRightWieszak(std::string s){
    std::unique_lock<std::mutex> locker_drawing(*Display->disp_mutex);
    int xr = Display->CloakroomY + rwX;
	int yr = Display->CloakroomX + rwY;
    locker_drawing.unlock();
	Display->PutChar(xr,yr,s);
}

void Checker::operator()(){}