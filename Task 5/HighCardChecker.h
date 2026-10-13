#pragma once
#include "PokerHandChecker.h"

class HighCardChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
