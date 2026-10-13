#pragma once
#include "PokerHandChecker.h"

class RoyalFlushChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
