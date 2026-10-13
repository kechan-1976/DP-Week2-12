#pragma once
#include "IRewardRule.h"

class BasicRewardRule : public IRewardRule {
public:
    int ComputeReward(int baseScore, int roundNumber) override;
};
