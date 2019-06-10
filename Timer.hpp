#pragma once
#include <iostream>
#include <ctime>
#include <unistd.h>

#define DEBUG 0
#define TIME_MIN 5000
#define TIME_MAX 10000

class Timer
{
public:
	double miliseconds;
	int time_min;
	int time_max;

	Timer(int time_min, int time_max);
	~Timer();

	void newTime(int min, int max);
	void printTime();
	void delay(int min, int max);
	void delay();
	void delay(int divider);
};
