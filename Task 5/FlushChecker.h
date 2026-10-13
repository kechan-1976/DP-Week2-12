#pragma once
#include "PokerHandChecker.h"

class FlushChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput& hand) override;
};
