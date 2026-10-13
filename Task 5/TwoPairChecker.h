#pragma once
#include "PokerHandChecker.h"

class TwoPairChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
