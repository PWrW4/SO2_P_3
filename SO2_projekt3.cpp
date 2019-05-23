//============================================================================
// Name        : SO2_projekt2.cpp
// Author      : Paweł Czarnecki
// Description : Systemy Operacyjne 2 - Projekt 2
//============================================================================
#include <cstdlib>


#include "Application.hpp"


using namespace std;


int main(int argc, char *argv[])// liczba filozofów, liczba powtórzeń sekwencji jedzenie-filozofowanie, minimalny czas, maksymalny czas [ms]
{
	int Philosophers_cnt = 5,
		Philosopher_it = 5,
		Time_min = 2500,
		Time_max = 3500;

	if(argc>1)
	{
		if(atoi(argv[1])>2)
			Philosophers_cnt = atoi(argv[1]);
		if(argc>2)
		{
			if(atoi(argv[2])>=0)
				Philosopher_it = atoi(argv[2]);
			if(argc>3)
			{
				if(atoi(argv[3])>0)
					Time_min = atoi(argv[3]);
				if(argc>4)
				{
					if(argv[4]>0)
						Time_max = atoi(argv[4]);
					if(atoi(argv[4])<Time_min)
						swap(Time_max,Time_min);
				}
			}
		}
	}

	cout<<Philosophers_cnt<<endl
		<<Philosopher_it<<endl
		<<Time_min<<endl
		<<Time_max<<endl;

	Application *app = new Application(Philosophers_cnt, Philosopher_it, Time_min,Time_max);
	
	app->ScanForExit();

	app->joinAll();
	delete app;
	return 0;
}
