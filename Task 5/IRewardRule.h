#pragma once

class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int ComputeReward(int baseScore, int roundNumber) = 0;
};
