#include <string>
#include "Room.hpp"
#define SLOWING_FACTOR 1
#define BENCHES 6
#define SEATS 4

class Corridor : public Room
{
    public:
    float traffic;
    float slowing_factor;
    bool **bench;

    Corridor(std::string name, int capacity);
    Corridor();
    ~Corridor();

    float CalculateTraffic();
    void Occupy(bool **bench, int bench, int seat);
    void Free(bool **bench, int bench, int seat);

}; 
 
