#pragma once
#include <memory>
#include "IInputGenerator.h"
#include "IScoringRule.h"
#include "IRewardRule.h"
#include "ShopSystem.h"


class RunSession {
public:
    RunSession(std::unique_ptr<IInputGenerator> inputGen,
               std::unique_ptr<IScoringRule> scoringRule,
               std::unique_ptr<IRewardRule> rewardRule,
               std::unique_ptr<ShopSystem> shop);

    void StartRun(int totalRounds = 3);

private:
    std::unique_ptr<IInputGenerator> m_inputGen;
    std::unique_ptr<IScoringRule>    m_scoringRule;
    std::unique_ptr<IRewardRule>     m_rewardRule;
    std::unique_ptr<ShopSystem>      m_shop;
    int m_money = 0;
};
