#include "RoyalFlushChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 10 stands for ROYAL FLUSH)
static bool IsRoyalFlush(const TurnInput& hand) {
    return hand.value == 10;
}

HandRank RoyalFlushChecker::Check(const TurnInput& hand) {
    if (IsRoyalFlush(hand)) {
        std::cout << "[CHECK] Detected ROYAL FLUSH\n";
        return HandRank::ROYAL_FLUSH;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
