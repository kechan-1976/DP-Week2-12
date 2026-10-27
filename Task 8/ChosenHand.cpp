#include "ChosenHand.h"

ChosenHand::ChosenHand(const Hand& selectedHand) : hand(selectedHand) {}

Hand ChosenHand::getHand() const {
    return hand;
}

void ChosenHand::displayHand() const {
    std::cout << "Kartu di Chosen Hand:\n";
    for (const auto& card : hand.cards) {
        std::cout << "Rank: " << card.rank << ", Suit: " << card.suit << "\n";
    }
}
