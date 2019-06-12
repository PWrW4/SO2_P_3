#pragma once
#include <string>
#include <vector>
#include <thread>
#include "Room.hpp"
#include "Visualization.hpp"
#define SLOWING_FACTOR 1
#define BENCHES 6
#define SEATS 4

class Corridor : public Room
{
    public:
    float traffic;
    float slowing_factor;
    std::thread t;
    std::vector<std::vector<bool>> bench;

    Visualization * v;

    Corridor(std::string name, int capacity, Visualization * v);
    Corridor();
    ~Corridor();

    void drawPeople();

    float CalculateTraffic();
    void Occupy(int bench_id, int seat_id);
    void Free(int bench_id, int seat_id);

    void virtual_function();
}; 
 
