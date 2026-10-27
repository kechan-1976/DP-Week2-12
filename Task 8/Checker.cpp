#include "Checker.h"

bool Checker::isValidHand(const Hand& hand) {
    return !hand.cards.empty();
}

bool Checker::checkFlush(const Hand& hand) {
    if (!isValidHand(hand)) return false;
    
    char firstSuit = hand.cards[0].suit;
    for (const auto& card : hand.cards) {
        if (card.suit != firstSuit) {
            return false;
        }
    }
    return true;
}
