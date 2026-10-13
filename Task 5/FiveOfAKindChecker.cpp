#include "FiveOfAKindChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 11 stands for FIVE OF A KIND)
static bool IsFiveOfAKind(const TurnInput& hand) {
    return hand.value == 11;
}

HandRank FiveOfAKindChecker::Check(const TurnInput& hand) {
    if (IsFiveOfAKind(hand)) {
        std::cout << "[CHECK] Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
