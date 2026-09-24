#pragma once

class IRewardRule {
public:
    virtual int computeReward(int baseScore) = 0;
    virtual ~IRewardRule() = default;
};
