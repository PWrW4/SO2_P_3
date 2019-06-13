#pragma once
#include <string>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "Room.hpp"
#define CUBICLE_CNT 3
#define CUBICLE_W 4
#define URINAL_CNT 6
#define TOILET_COL 21
#define TOILET_COL_W 1
#define TOILET_ROW 5
#define TOILET_ROW_W 1


class Person;

class Toilet : public Room
{
    public:
    int cub_wait;
    bool *cubicle;
    std::mutex *cub_wait_mutex;
    std::mutex *cub_mutex;
    std::condition_variable *cub_cond;

    int uri_wait;
    bool *urinal;
    std::mutex *uri_wait_mutex;
    std::mutex *uri_mutex;
    std::condition_variable *uri_cond;

    Toilet(std::string name, int capacity);
    Toilet();
    ~Toilet();

};
