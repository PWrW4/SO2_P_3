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