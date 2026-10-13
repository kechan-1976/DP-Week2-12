#pragma once
#include "PokerHandChecker.h"

class FourOfAKindChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
