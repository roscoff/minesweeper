#include "timer.h"

timer::timer(){
	QueryPerformanceFrequency((LARGE_INTEGER*)&mCountsPerSec);
	QueryPerformanceCounter((LARGE_INTEGER*)&Start);
}

void timer::start(){
	QueryPerformanceCounter((LARGE_INTEGER*)&Start);
}

float timer::getTime(){
	__int64 Now;
	QueryPerformanceCounter((LARGE_INTEGER*)&Now);
	return (Now - Start)/ mCountsPerSec;
}
