#pragma once
#include "PokerHandChecker.h"

class ThreeOfAKindChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
