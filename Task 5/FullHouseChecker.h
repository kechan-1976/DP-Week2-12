#pragma once
#include "PokerHandChecker.h"

class FullHouseChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
