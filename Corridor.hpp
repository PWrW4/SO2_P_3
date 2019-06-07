#include <string>
#include <vector>
#include "Room.hpp"
#define SLOWING_FACTOR 1
#define BENCHES 6
#define SEATS 4

class Corridor : public Room
{
    public:
    float traffic;
    float slowing_factor;
    std::vector<std::vector<bool>> bench;

    Corridor(std::string name, int capacity);
    Corridor();
    ~Corridor();

    float CalculateTraffic();
    void Occupy(int bench_id, int seat_id);
    void Free(int bench_id, int seat_id);

}; 
 
