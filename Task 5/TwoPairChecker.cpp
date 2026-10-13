#include "TwoPairChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 3 stands for TWO PAIR)
static bool IsTwoPair(const TurnInput& hand) {
    return hand.value == 3;
}

HandRank TwoPairChecker::Check(const TurnInput& hand) {
    if (IsTwoPair(hand)) {
        std::cout << "[CHECK] Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
