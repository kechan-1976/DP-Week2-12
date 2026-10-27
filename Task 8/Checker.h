#pragma once
#include "Hand.h"

class Checker {
public:
    // Mengecek apakah seluruh kartu dalam hand memiliki suit yang sama (Flush)
    bool checkFlush(const Hand& hand);
    // Mengecek apakah ada kartu di dalam hand
    bool isValidHand(const Hand& hand);
};
