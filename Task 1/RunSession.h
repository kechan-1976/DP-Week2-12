#pragma once
#include <memory>
#include "IInputGenerator.h"
#include "IScoringRule.h"
#include "IRewardRule.h"
#include "ShopSystem.h"

class RunSession {
private:
    std::unique_ptr<IInputGenerator> inputGenerator;
    std::unique_ptr<IScoringRule> scoringRule;
    std::unique_ptr<IRewardRule> rewardRule;
    ShopSystem shop;
    int money = 0;

public:
    RunSession(std::unique_ptr<IInputGenerator> inputGen, 
               std::unique_ptr<IScoringRule> scoreRule, 
               std::unique_ptr<IRewardRule> rewRule);
    void run();
};
