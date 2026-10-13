#include "FullHouseChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 7 stands for FULL HOUSE)
static bool IsFullHouse(const TurnInput& hand) {
    return hand.value == 7;
}

HandRank FullHouseChecker::Check(const TurnInput& hand) {
    if (IsFullHouse(hand)) {
        std::cout << "[CHECK] Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
