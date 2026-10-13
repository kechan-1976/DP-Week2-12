#pragma once
#include "PokerHandChecker.h"

class PairChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
