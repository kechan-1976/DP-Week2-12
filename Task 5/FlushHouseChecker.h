#pragma once
#include "PokerHandChecker.h"

class FlushHouseChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
