#pragma once
#include <vector>
#include "Card.h"

// Per-round input. `value` is the dummy hand type (1-13) that the checkers
// read; `cards` is the 5-card hand built to match it, used for display.
struct TurnInput {
    int value;
    std::vector<Card> cards;
};
