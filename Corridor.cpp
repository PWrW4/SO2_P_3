#include <string>
#include "Corridor.hpp"
#include <iostream>
#include "Student.hpp"

	Corridor::Corridor(std::string name, int capacity, Visualization * _v)
        : Room(name, capacity, RoomType::E_Corridor)
    {
        bMtx.lock();
        v = _v;
        CalculateTraffic();
        slowing_factor=SLOWING_FACTOR;
        bench.resize(BENCHES);
        for(int i=0;i<BENCHES;i++)
        {
            bench[i].resize(SEATS);
            for (int j = 0; j < SEATS; j++)
            {
                bench[i][j] = nullptr;
            }
        }
        bMtx.unlock();
        std::thread thr(&Corridor::drawPeople, this);
        std::swap(thr, t);
    }

    void Corridor::drawPeople(){
        std::unique_lock<std::mutex> locker_drawing(*v->disp_mutex);
        int xr = v->CorridorY + 20;
        int yr = v->CorridorX + 3;
        int a = 0;
        int b = 0;
        locker_drawing.unlock();
        int xb = xr;
        int yb = yr;
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            capMutex.lock();
            a = people.size();
            b = 0;
            capMutex.unlock();

            bMtx.lock();

            for (int i = 0; i < BENCHES; i++)
            {
                for (int j = 0; j < SEATS; j++)
                {
                    if (bench[i][j] != nullptr)
                    {
                        b++;
                    }
                }
            }

            bMtx.unlock();

            for (int i = 0; i < BENCHES; i++)
            {
                for (int j = 0; j < SEATS; j++)
                {
                    if (bench[i][j] != nullptr)
                    {
                        v->PutChar(72 + 1 + j + (7*i), 16, "s",R_COLOR); //std::to_string(bench[i][j]->id));
                    }else{
                        v->PutChar(72 + 1 + j + (7*i), 16, " ");
                    }
                }
            }     

            a-=b;

            for (size_t i = 0; i < 80; i++)
            {
                if (i < 40)
                {
                    v->PutChar(xr, yr, " ");
                    xr++;
                }
                if (i == 40)
                {
                    xr=xb;
                }
                if (i >= 40 && i <= 80)
                {
                    v->PutChar(xr, yr + 2, " ");
                    xr++;
                }
            }
            xr = xb;
            yr = yb;
            for (size_t i = 0; i < a; i++)
            {
                if (i < 40)
                {
                    v->PutChar(xr, yr, "s");
                    xr++;
                }
                if (i == 40)
                {
                    xr=xb;
                }
                if (i >= 40 && i <= 80)
                {
                    v->PutChar(xr, yr + 2, "s");
                    xr++;
                }
            }
        }
    }

    Corridor::Corridor()
    {
    }
    Corridor::~Corridor()
    {
    } 
 
    float Corridor::CalculateTraffic()
    {
        return traffic = people.size()/capacity;
    }

    bool Corridor::sitAndFix(Student * s){
        int a,b;
        bool cont = true;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        bMtx.lock();
        for (int i = 0; i < BENCHES; i++)
        {
            for (int j = 0; j < SEATS; j++)
            {
                if (bench[i][j] == nullptr && cont)
                {
                    bench[i][j] = s;
                    a = i;
                    b = j;
                    cont = false;
                    break;
                }
            }
            if (false == cont)
            {
                break;
            }
        }
        bMtx.unlock();

        if(cont)return false;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        bMtx.lock();
        bench[a][b] = nullptr;
        bMtx.unlock();
        return true;
    }

    void Corridor::virtual_function(){}