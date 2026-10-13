#include "ModifiedRewardRule.h"

int ModifiedRewardRule::ComputeReward(int baseScore, int roundNumber) {

    if (roundNumber % 2 == 0) {
        return baseScore * 2;
    }
    return baseScore + 2;
}
