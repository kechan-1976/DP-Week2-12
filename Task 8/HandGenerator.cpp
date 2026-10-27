#include <iostream>
#include <random>
#include "HandGenerator.h"

Hand HandGenerator::generateHand() {
    std::cout << "Generating random hand...\n";
    Hand hand;
    
    // Inisialisasi random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Distribusi untuk Rank (2 sampai 14, di mana 11=J, 12=Q, 13=K, 14=A)
    std::uniform_int_distribution<int> rankDist(2, 14);
    
    // Distribusi untuk Suit (H = Hearts, D = Diamonds, C = Clubs, S = Spades)
    const char suits[] = {'H', 'D', 'C', 'S'};
    std::uniform_int_distribution<int> suitDist(0, 3);

    // Menghasilkan 5 kartu acak
    for (int i = 0; i < 5; ++i) {
        Card randomCard;
        randomCard.rank = rankDist(gen);
        randomCard.suit = suits[suitDist(gen)];
        hand.cards.push_back(randomCard);
    }
    
    return hand;
}
