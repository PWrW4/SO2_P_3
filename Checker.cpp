#include "Checker.hpp"

Checker::Checker(std::string name,Floor * _f, Status status, PersonType type,Room *actualPosition,Visualization * Display, int id)
: Person(name,_f,status,type,actualPosition,Display)
{
    drawLeftSlot("ls");
    drawRightSlot("rs");
    drawLeftWieszak("lw");
    drawRightWieszak("rw");
    checkerId = id;
    c = dynamic_cast<Cloakroom *>(actualPosition);
    // thread thr(&Checker::mainLoop, this);
	// std::swap(thr, person_thread);
}

void Checker::mainLoop(){
    int sleep = 0;
    while (!this->end)
    {   
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (checkerId == 1)
        {
            std::unique_lock<std::mutex> lck(c->mtx_lq);
            if (!c->ql.empty())
            {
                Student *s = c->ql.front();
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
                        c->rightWieszak.insert(c->rightWieszak.end(),k);
                    }
                    else
                    {
                        std::unique_lock<std::mutex> wieszak(c->mtx_leftWieszak);
                        c->leftWieszak.insert(c->rightWieszak.end(),k);
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
                    }
                    if (d != -1) //pętla zaczynająca od prawego
                    {
                        c->mtx_rightWieszak.lock();
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
                        }
                        else
                        {
                            c->mtx_rightWieszak.unlock();
                            c->mtx_leftWieszak.lock();
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
                        }
                    }

                    s->kurtka = k;
                    lck_student.lock();
                    s->studentWaitBool = false;
                    lck_student.unlock();
                    s->studentWaitCond.notify_one();
                }
            }
        }
        if (checkerId==2)
        {
            /* code */
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