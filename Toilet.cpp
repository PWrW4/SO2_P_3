#include <string>
#include "Toilet.hpp"
#include "Person.hpp"

	Toilet::Toilet(std::string name, int capacity)
        : Room(name, capacity, RoomType::E_Toilet)
    {
        cub_wait = 0;
        cubicle = new bool[CUBICLE_CNT];
        cub_mutex = new mutex;
        cub_wait_mutex = new mutex;
        cub_cond = new condition_variable;

        uri_wait = 0;
        urinal = new bool[URINAL_CNT];
        uri_mutex = new mutex;
        uri_wait_mutex = new mutex;
        uri_cond = new condition_variable;

        for(int i=0;i<CUBICLE_CNT;i++)
            cubicle[i] = false;
        for(int i=0;i<URINAL_CNT;i++)
            urinal[i] = false;            

    }

    Toilet::Toilet()
    {
        cubicle = new bool[CUBICLE_CNT];
        cub_mutex = new mutex[CUBICLE_CNT];
        cub_cond = new condition_variable;
        
        urinal = new bool[URINAL_CNT];
        uri_mutex = new mutex[URINAL_CNT];
        uri_cond = new condition_variable;
    }

    Toilet::~Toilet()
    {
        delete cubicle, cub_mutex, cub_cond;
        delete urinal, uri_mutex, uri_cond;
    } 

