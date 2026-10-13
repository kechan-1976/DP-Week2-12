#include "RunSession.h"
#include <iostream>

RunSession::RunSession(std::unique_ptr<IInputGenerator> inputGen,
                        std::unique_ptr<IScoringRule> scoringRule,
                        std::unique_ptr<IRewardRule> rewardRule,
                        std::unique_ptr<ShopSystem> shop)
    : m_inputGen(std::move(inputGen)),
      m_scoringRule(std::move(scoringRule)),
      m_rewardRule(std::move(rewardRule)),
      m_shop(std::move(shop)) {}

void RunSession::StartRun(int totalRounds) {
    std::cout << "=== RUN START ===\n";

    for (int round = 1; round <= totalRounds; ++round) {
        std::cout << "\nRound " << round << "\n";

        TurnInput input = m_inputGen->Generate();
        std::cout << "[PLAY] input generated: " << input.value << "\n";

        std::cout << "[PLAY] cards:";
        for (const Card& c : input.cards)
            std::cout << " " << c.ToString();
        std::cout << "\n";

        int baseScore = m_scoringRule->ComputeScore(input);
        std::cout << "[SCORE] base score: " << baseScore << "\n";

        int reward = m_rewardRule->ComputeReward(baseScore, round);

        m_money += reward;
        std::cout << "[REWARD] gain: " << reward << " | money: " << m_money << "\n";

        m_shop->OfferItem(round);

    }

    std::cout << "\n=== RUN END ===\n";
    std::cout << "Final money: " << m_money << "\n";
}
