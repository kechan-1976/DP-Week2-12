#pragma once
#include <string>

// A playing card. rank: 2-10, 11 = J, 12 = Q, 13 = K, 14 = A.
// suit: 'S' (spades), 'H' (hearts), 'D' (diamonds), 'C' (clubs).
struct Card {
    int  rank;
    char suit;

    std::string ToString() const {
        std::string r;
        switch (rank) {
        case 11: r = "J"; break;
        case 12: r = "Q"; break;
        case 13: r = "K"; break;
        case 14: r = "A"; break;
        default: r = std::to_string(rank); break;
        }
        return r + suit;
    }
};
