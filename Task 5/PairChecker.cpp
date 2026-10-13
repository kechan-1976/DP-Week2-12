#include "PairChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 2 stands for PAIR)
static bool IsPair(const TurnInput& hand) {
    return hand.value == 2;
}

HandRank PairChecker::Check(const TurnInput& hand) {
    if (IsPair(hand)) {
        std::cout << "[CHECK] Detected PAIR\n";
        return HandRank::PAIR;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
