#include <string>
#include <mutex>
#include <condition_variable>
#include "Room.hpp"

#define STAMPS_CNT 
#define SIZE 300        // maksymalna liczba dokumentów danego typu w buforze 
#define LSIZE 80        // Dlugosc napisu 

class DeanOffice : public Room
{
    public:
    DeanOffice(std::string name, int capacity);
    DeanOffice();
    ~DeanOffice();

    int buf[SIZE];  // Bufor na dokumenty
    int head;  // Tutaj wpisujemy do bufora nowy element 
    int tail;  // Stad pobieramy element z bufora          
    int cnt;   // Liczba elementow w buforze 
    pthread_cond_t empty;  // Tu czekamy gdy brak miejsca w buforze 
    pthread_cond_t full;   // Tu czekamy gdy brak rekordow w buforze 
    pthread_mutex_t mutex; // Wzajemne wykluczanie  
    bool *stamps;
    mutex *mutex_fork;				// mutex widelców
	condition_variable *conditions;	// tablica zmiennych warunkowych dla widelców
};