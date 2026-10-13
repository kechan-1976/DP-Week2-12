#include "FlushHouseChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 12 stands for FLUSH HOUSE)
static bool IsFlushHouse(const TurnInput& hand) {
    return hand.value == 12;
}

HandRank FlushHouseChecker::Check(const TurnInput& hand) {
    if (IsFlushHouse(hand)) {
        std::cout << "[CHECK] Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
