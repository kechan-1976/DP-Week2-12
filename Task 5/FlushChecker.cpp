#include "FlushChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 6 stands for FLUSH)
static bool IsFlush(const TurnInput& hand) {
    return hand.value == 6;
}

HandRank FlushChecker::Check(const TurnInput& hand) {
    if (IsFlush(hand)) {
        std::cout << "[CHECK] Detected FLUSH\n";
        return HandRank::FLUSH;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
