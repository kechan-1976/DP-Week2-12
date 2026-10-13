#pragma once
#include "TurnInput.h"

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int ComputeScore(const TurnInput& input) = 0;
};
