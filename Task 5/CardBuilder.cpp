#include "CardBuilder.h"
#include <algorithm>
#include <cstdlib>

namespace {

const char SUITS[4] = { 'S', 'H', 'D', 'C' };

int Rand(int n) { return std::rand() % n; }                 // 0..n-1
int RandRank()  { return 2 + Rand(13); }                    // 2..14
char RandSuit() { return SUITS[Rand(4)]; }

// n distinct suits in random order
std::vector<char> DistinctSuits(int n) {
    std::vector<char> s(SUITS, SUITS + 4);
    for (int i = 3; i > 0; --i) std::swap(s[i], s[Rand(i + 1)]);
    s.resize(n);
    return s;
}

// `count` distinct ranks, none of them in `used`
std::vector<int> DistinctRanks(int count, std::vector<int> used = {}) {
    std::vector<int> out;
    while (static_cast<int>(out.size()) < count) {
        int r = RandRank();
        if (std::find(used.begin(), used.end(), r) == used.end()) {
            out.push_back(r);
            used.push_back(r);
        }
    }
    return out;
}

bool IsStraightRanks(std::vector<int> r) {
    std::sort(r.begin(), r.end());
    if (r.back() - r.front() == 4) return true;
    return r == std::vector<int>{ 2, 3, 4, 5, 14 };          // wheel A-2-3-4-5
}

bool AllSameSuit(const std::vector<Card>& c) {
    for (const Card& x : c) if (x.suit != c[0].suit) return false;
    return true;
}

// `n` cards of one rank with distinct suits
void AddOfAKind(std::vector<Card>& hand, int rank, int n) {
    for (char s : DistinctSuits(n)) hand.push_back({ rank, s });
}

std::vector<Card> Sequence(int start, bool sameSuit) {
    std::vector<Card> hand;
    char suit = RandSuit();
    for (int i = 0; i < 5; ++i)
        hand.push_back({ start + i, sameSuit ? suit : RandSuit() });
    return hand;
}

} // namespace

std::vector<Card> BuildHandForRank(int value) {
    std::vector<Card> hand;

    switch (value) {
    case 1: { // High Card: no pair, no straight, no flush
        std::vector<int> r;
        do { r = DistinctRanks(5); } while (IsStraightRanks(r));
        do {
            hand.clear();
            for (int x : r) hand.push_back({ x, RandSuit() });
        } while (AllSameSuit(hand));
        break;
    }
    case 2: { // Pair
        std::vector<int> r = DistinctRanks(4);
        AddOfAKind(hand, r[0], 2);
        for (int i = 1; i < 4; ++i) hand.push_back({ r[i], RandSuit() });
        break;
    }
    case 3: { // Two Pair
        std::vector<int> r = DistinctRanks(3);
        AddOfAKind(hand, r[0], 2);
        AddOfAKind(hand, r[1], 2);
        hand.push_back({ r[2], RandSuit() });
        break;
    }
    case 4: { // Three of a Kind
        std::vector<int> r = DistinctRanks(3);
        AddOfAKind(hand, r[0], 3);
        hand.push_back({ r[1], RandSuit() });
        hand.push_back({ r[2], RandSuit() });
        break;
    }
    case 5: { // Straight (mixed suits), start 2..10
        do { hand = Sequence(2 + Rand(9), false); } while (AllSameSuit(hand));
        break;
    }
    case 6: { // Flush: same suit, ranks not in sequence
        std::vector<int> r;
        do { r = DistinctRanks(5); } while (IsStraightRanks(r));
        char suit = RandSuit();
        for (int x : r) hand.push_back({ x, suit });
        break;
    }
    case 7: { // Full House
        std::vector<int> r = DistinctRanks(2);
        AddOfAKind(hand, r[0], 3);
        AddOfAKind(hand, r[1], 2);
        break;
    }
    case 8: { // Four of a Kind
        std::vector<int> r = DistinctRanks(2);
        AddOfAKind(hand, r[0], 4);
        hand.push_back({ r[1], RandSuit() });
        break;
    }
    case 9:   // Straight Flush, start 2..9 (10 would be a royal flush)
        hand = Sequence(2 + Rand(8), true);
        break;
    case 10:  // Royal Flush: 10 J Q K A, same suit
        hand = Sequence(10, true);
        break;
    case 11: { // Five of a Kind: duplicates allowed, suits not all equal
        int rank = RandRank();
        do {
            hand.clear();
            for (int i = 0; i < 5; ++i) hand.push_back({ rank, RandSuit() });
        } while (AllSameSuit(hand));
        break;
    }
    case 12: { // Flush House: full house with every card the same suit
        std::vector<int> r = DistinctRanks(2);
        char suit = RandSuit();
        for (int i = 0; i < 3; ++i) hand.push_back({ r[0], suit });
        for (int i = 0; i < 2; ++i) hand.push_back({ r[1], suit });
        break;
    }
    case 13: { // Flush Five: five identical cards
        int rank = RandRank();
        char suit = RandSuit();
        for (int i = 0; i < 5; ++i) hand.push_back({ rank, suit });
        break;
    }
    default:
        return BuildHandForRank(1);
    }

    for (int i = static_cast<int>(hand.size()) - 1; i > 0; --i)
        std::swap(hand[i], hand[Rand(i + 1)]);               // shuffle for display
    return hand;
}
