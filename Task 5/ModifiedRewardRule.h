#pragma once
#include "IRewardRule.h"

class ModifiedRewardRule : public IRewardRule {
public:
    int ComputeReward(int baseScore, int roundNumber) override;
};
