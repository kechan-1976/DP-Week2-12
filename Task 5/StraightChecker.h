#pragma once
#include "PokerHandChecker.h"

class StraightChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
