#include <string>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "Room.hpp"

#define STAMPS_CNT 3        // liczba pieczątek, niech będzie równa liczbie pracowników dziekanatu
#define DOC_TYPES 3         // liczba typów dokumentów
#define DOC_BUF_SIZE 5      // maksymalna liczba dokumentów danego typu w buforze

using namespace std;

class DeanOffice : public Room
{
    public:
    DeanOffice(string name, int capacity);
    DeanOffice();
    ~DeanOffice();

    int *docbuf;                     // Bufor na dokumenty
    int *head;                       // Tutaj wpisujemy do bufora nowy element 
    int *tail;                       // Stad pobieramy element z bufora          
    int *cnt;                        // Liczba elementow w buforze 
    condition_variable *docbuf_empty;// Tu czekamy gdy brak miejsca w buforze 
    condition_variable *docbuf_full; // Tu czekamy gdy brak rekordow w buforze 
    mutex *docbuf_mutex;             // Wzajemne wykluczanie dostępu do stosów dokumentów

    bool *stamps;                    // Pieczątki
    condition_variable *stamps_cond; // Oczekiwanie na pieczątki
    mutex *stamps_mutex;             // Wzajemne wykluczanie dostępu do pieczątek

};