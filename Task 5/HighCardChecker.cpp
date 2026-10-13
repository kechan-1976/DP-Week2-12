#include "HighCardChecker.h"
#include <iostream>

HandRank HighCardChecker::Check(const TurnInput& hand) {
    // End of the chain: nothing stronger matched, so this is a high card.
    std::cout << "[CHECK] Detected HIGH CARD\n";
    return HandRank::HIGH_CARD;
}
