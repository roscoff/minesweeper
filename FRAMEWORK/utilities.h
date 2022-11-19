#pragma once
#include <windows.h>

struct color {
	byte r, g, b, a;
    color operator*(float intensity) {
        color out{ (BYTE)(this->r * intensity), (BYTE)(this->g * intensity), (BYTE)(this->b * intensity), (BYTE)(this->a * intensity)};
        return out;
    };

    color operator+(color addcolor) {
        color out{ (BYTE)(this->r + addcolor.r), (BYTE)(this->g + addcolor.g), (BYTE)(this->b + addcolor.b), (BYTE)(this->a * +addcolor.a)};
        return out;
    }
};

struct point {
	int x, y;
};


int randBetween(int v1, int v2);

template<typename T> void swapvalue(T& v1, T& v2);

float linearInterpolation(float v1, float v2, float val);

bool isPrime(int n);

int nbDivisor(int n);

template<typename T>
inline void swapvalue(T& v1, T& v2){
    T tmp = v1;
    v1 = v2;
    v2 = tmp;
}

