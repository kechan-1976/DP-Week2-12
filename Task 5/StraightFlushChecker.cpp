#include "StraightFlushChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 9 stands for STRAIGHT FLUSH)
static bool IsStraightFlush(const TurnInput& hand) {
    return hand.value == 9;
}

HandRank StraightFlushChecker::Check(const TurnInput& hand) {
    if (IsStraightFlush(hand)) {
        std::cout << "[CHECK] Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
