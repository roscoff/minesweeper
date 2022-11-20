#pragma once
#include <Windows.h>

class timer {
public:
	timer();
	void start();
	float getTime();
private:
	__int64 Start;
	__int64 mCountsPerSec;
};