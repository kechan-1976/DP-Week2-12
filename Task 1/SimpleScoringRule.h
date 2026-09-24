#pragma once
#include "IScoringRule.h"

class SimpleScoringRule : public IScoringRule {
public:
    int computeScore(const TurnInput& input) override;
};
