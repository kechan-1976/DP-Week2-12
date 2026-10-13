#include "ThreeOfAKindChecker.h"
#include <iostream>

// dummy helper: only the hand type is printed, no real card logic yet
// (TurnInput.value 4 stands for THREE OF A KIND)
static bool IsThreeOfAKind(const TurnInput& hand) {
    return hand.value == 4;
}

HandRank ThreeOfAKindChecker::Check(const TurnInput& hand) {
    if (IsThreeOfAKind(hand)) {
        std::cout << "[CHECK] Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }

    if (m_nextChecker)
        return m_nextChecker->Check(hand);

    return HandRank::HIGH_CARD;
}
