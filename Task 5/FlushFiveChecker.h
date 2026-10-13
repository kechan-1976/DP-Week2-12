#pragma once
#include "PokerHandChecker.h"

class FlushFiveChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
