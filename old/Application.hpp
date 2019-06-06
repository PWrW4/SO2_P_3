#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Visualization.hpp"
#include "Timer.hpp"
//#include "Philosopher.hpp"

using namespace std;

class Application
{
public:
	Visualization *Display;			// klasa obsługująca ncurses
	Timer *timer;					// obsługa uśpień
	mutex *mutex_disp;				// mutex wyświetlacza
	mutex *mutex_fork;				// mutex widelców
	condition_variable *conditions;	// tablica zmiennych warunkowych dla widelców
//	Philosopher **phil_tab;			// tablica wskaźników na filozofów
//	thread **thread_tab;			// -||- na wątki
	bool *Forks;					// tablica widelców : true-dostępny, false-w użyciu
	bool *exit_now;					// flaga zakończenia programu
	int philosopher_cnt;			// liczba filozofów

	Application(int philosophers_cnt, int philosophers_it, int time_min, int time_max);
	~Application();

	void joinAll();
	void ScanForExit();
};
