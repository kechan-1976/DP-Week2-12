#pragma once
#include "IScoringRule.h"

class BasicScoringRule : public IScoringRule {
public:
    int ComputeScore(const TurnInput& input) override;
};
