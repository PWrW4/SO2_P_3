#include "Application.hpp"

Application::Application(int philosophers_cnt, int philosophers_it, int time_min, int time_max)
	: philosopher_cnt(philosophers_cnt)
{
	cout << "watek macierzysty start\n" << endl;
	Display = new Visualization(philosophers_cnt ,COLUMNS, ROWS_STEP, COLUMNS_STEP);
	Display->DrawTable();
	mutex_disp = new mutex();
	mutex_fork = new mutex();
	timer = new Timer(time_min, time_max);
	Forks = new bool[philosophers_cnt];					
	exit_now = new bool;
	*exit_now = false; 
	conditions = new condition_variable[philosophers_cnt];
//	phil_tab = new Philosopher*[philosophers_cnt];
//	thread_tab = new thread*[philosophers_cnt];
	for (int i = 0; i<philosophers_cnt; i++)
	{
		Forks[i] = true;
//		phil_tab[i] = new Philosopher(i, Forks, philosophers_cnt, philosophers_it, Display, mutex_disp, mutex_fork, conditions, timer, exit_now);
//		thread_tab[i] = new thread(*phil_tab[i]);
	}
}

Application::~Application()
{
	for (int i = 0; i<philosopher_cnt; i++)
	{
//		delete phil_tab[i];
//		delete thread_tab[i];
	}
//	delete[] phil_tab;
//	delete[] thread_tab;
	delete[] conditions;
	delete[] Forks;

	delete exit_now;
	delete timer;
	delete mutex_fork;
	delete mutex_disp;
	delete Display;
	cout << "watek macierzysty koniec\n" << endl;
}

void Application::joinAll()
{
//	for (int j = 0; j<philosopher_cnt; j++)
//		thread_tab[j]->join();
}

void Application::ScanForExit()
{
	char q;
	
	while(!(*exit_now))
	{
		q=getch();
		if(q=='q')
			*exit_now=true;
		timer->delay(Display->ec_width/2);
	}
}
