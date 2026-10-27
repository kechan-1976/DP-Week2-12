#pragma once
#include <iostream>
#include "HandGenerator.h"
#include "Hand.h"

struct HandPlayer { 
    void playHand(Hand h) { std::cout << "Memainkan kartu...\n"; } 
};
struct ScoringRule { 
    int scoreHand(Hand h) { return 100; } 
};
struct BlindRule { 
    bool checkBlind(int score) { return score > 50; } 
};
struct RewardRule { 
    int earnMoney(bool win, int score) { return win ? score * 2 : 0; } 
};

class GameManager {
private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
public:
    void runSession();
};
