#pragma once
#include "utilities.h"

int randBetween(int v1, int v2) {
    if (v1 <= v2) {
        return (rand() % (v2+1 - v1)) + v1;
    }
    return randBetween(v2, v1);
}

float linearInterpolation(float v1, float v2, float val) {
    return (v2 - v1) * val + v1;
}

bool isPrime(int n){
    for (int d = 2 ; d < n-1; d++) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

int nbDivisor(int n){
    int out = 0;
    for (int d = 2; d < n - 1; d++) {
        if (n % d == 0) {
            out++;
        }
    }
    return out;
}
