#include <string>
#include "Room.hpp"
#include <mutex>
#include <vector>
#include <queue>

class Cloakroom : public Room
{
    public:
    Cloakroom(std::string name, int capacity);
    Cloakroom();
    ~Cloakroom();

    std::mutex mtx_leftWieszak;
    std::mutex mtx_rightWieszak;
    std::vector<int> leftWieszak;
    std::vector<int> rightWieszak;
    std::mutex mtx_lq;
    std::mutex mtx_rq;
    std::queue <int> ql;
    std::queue <int> qr;


    void virtual_function();
};