#include "StraightChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 5 stands for STRAIGHT)
static bool IsStraight(const TurnInput& hand) {
    return hand.value == 5;
}

HandRank StraightChecker::Check(const TurnInput& hand) {
    if (IsStraight(hand)) {
        std::cout << "[CHECK] Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
