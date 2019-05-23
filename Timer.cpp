#include "Timer.hpp"

using namespace std;

Timer::Timer(int time_min, int time_max)
	: miliseconds(0)
{
	this->time_min = time_min;
	this->time_max = time_max;
	srand(time(NULL));
}

Timer::~Timer()
{
	miliseconds = 0;
}
void Timer::newTime(int min, int max)
{
	miliseconds = rand() % (max - min) + min;
	miliseconds *= 1000;

}

void Timer::printTime()
{
	cout << "newTime is: " << miliseconds / 1000 << " seconds\n";
}

void Timer::delay(int min, int max)
{
	newTime(min, max);
#if DEBUG
	printTime();
#endif
	usleep(miliseconds);
}
 
void Timer::delay()
{
	newTime(time_min, time_max);
#if DEBUG
	printTime();
#endif
	usleep(miliseconds);
}

void Timer::delay(int divider)
{
	newTime(time_min/divider, time_max/divider);
#if DEBUG
	printTime();
#endif
	usleep(miliseconds);
}
