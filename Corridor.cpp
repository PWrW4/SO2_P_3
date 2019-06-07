#include <string>
#include "Corridor.hpp"

	Corridor::Corridor(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_Corridor)
    {
        CalculateTraffic();
        slowing_factor=SLOWING_FACTOR;
        bench = new bool[BENCHES];
        for(int i=0;i<BENCHES;i++)
            bench[i] = new bool[SEATS];
    }

    Corridor::Corridor()
    {
        CalculateTraffic();
        slowing_factor=SLOWING_FACTOR;
        bench = new bool[BENCHES];
        for(int i=0;i<BENCHES;i++)
            bench[i] = new bool[SEATS];
    }
    Corridor::~Corridor()
    {
        for(int i=0;i<BENCHES;i++)
            delete bench[i];
        delete bench;
    } 
 
    float Corridor::CalculateTraffic()
    {
        return traffic = people.size()/capacity;
    }

    void Occupy(bool **bench, int bench, int seat)
    {
        bench[bench][seat] = true;
    }

    void Free(bool **bench, int bench, int seat)
    {
        bench[bench][seat] = false;
    }