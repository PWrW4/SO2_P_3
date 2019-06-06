#include "Room.hpp"
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Entrance : public Room
{
private:
    
    void mainLoop();

public:
    std::mutex EntranceMutex;

    Entrance(std::string name, int capacity);
    Entrance();
    ~Entrance();
}; 
