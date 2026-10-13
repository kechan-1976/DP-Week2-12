#include "FlushFiveChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 13 stands for FLUSH FIVE)
static bool IsFlushFive(const TurnInput& hand) {
    return hand.value == 13;
}

HandRank FlushFiveChecker::Check(const TurnInput& hand) {
    if (IsFlushFive(hand)) {
        std::cout << "[CHECK] Detected FLUSH FIVE\n";
        return HandRank::FLUSH_FIVE;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
