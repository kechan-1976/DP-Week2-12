#pragma once
#include "IRewardRule.h"

class ModifiedRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore) override;
};
