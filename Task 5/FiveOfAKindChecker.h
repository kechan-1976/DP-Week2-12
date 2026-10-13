#pragma once
#include "PokerHandChecker.h"

class FiveOfAKindChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
