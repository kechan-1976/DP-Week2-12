#pragma once
#include "PokerHandChecker.h"

class StraightFlushChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
