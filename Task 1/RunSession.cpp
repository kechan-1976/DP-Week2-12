#include "RunSession.h"
#include <iostream>

RunSession::RunSession(std::unique_ptr<IInputGenerator> inputGen, 
                       std::unique_ptr<IScoringRule> scoreRule, 
                       std::unique_ptr<IRewardRule> rewRule)
    : inputGenerator(std::move(inputGen)), 
      scoringRule(std::move(scoreRule)), 
      rewardRule(std::move(rewRule)) {}

void RunSession::run() {
    std::cout << "=== RUN START ===\n\n";
    
    for (int round = 1; round <= 3; ++round) {
        std::cout << "Round " << round << "\n";
        
        TurnInput input = inputGenerator->generate();
        std::cout << "[PLAY] input generated: " << input.value << "\n";
        
        int baseScore = scoringRule->computeScore(input);
        std::cout << "[SCORE] base score: " << baseScore << "\n";
        
        int reward = rewardRule->computeReward(baseScore);
        money += reward;
        std::cout << "[REWARD] gain: " << reward << " | money: " << money << "\n";
        
        shop.visitShop(money);
        std::cout << "\n";
    }
    
    std::cout << "=== RUN END ===\n";
    std::cout << "Final money: " << money << "\n";
}
