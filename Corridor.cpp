#include <string>
#include "Corridor.hpp"

	Corridor::Corridor(std::string name, int capacity, Visualization * _v)
        : Room(name, capacity, RoomType::E_Corridor)
    {
        v = _v;
        CalculateTraffic();
        slowing_factor=SLOWING_FACTOR;
        bench.resize(BENCHES);
        for(int i=0;i<BENCHES;i++)
        {
            bench[i].resize(SEATS);
            for (int j = 0; j < SEATS; j++)
            {
                bench[i][j] = false;
            }
        }
        std::thread thr(&Corridor::drawPeople, this);
        std::swap(thr, t);
    }

    void Corridor::drawPeople(){
        std::unique_lock<std::mutex> locker_drawing(*v->disp_mutex);
        int xr = v->CorridorY + 20;
        int yr = v->CorridorX + 3;
        int a = 0;
        locker_drawing.unlock();
        int xb = xr;
        int yb = yr;
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            capMutex.lock();
            a = people.size();
            // a = 50;
            capMutex.unlock();

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

    void Corridor::Occupy(int bench_id, int seat_id)
    {
        bench[bench_id][seat_id] = true;
    }

    void Corridor::Free(int bench_id, int seat_id)
    {
        bench[bench_id][seat_id] = false;
    }

    void Corridor::virtual_function(){}