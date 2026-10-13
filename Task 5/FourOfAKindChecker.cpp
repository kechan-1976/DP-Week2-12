#include "FourOfAKindChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 8 stands for FOUR OF A KIND)
static bool IsFourOfAKind(const TurnInput& hand) {
    return hand.value == 8;
}

HandRank FourOfAKindChecker::Check(const TurnInput& hand) {
    if (IsFourOfAKind(hand)) {
        std::cout << "[CHECK] Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
