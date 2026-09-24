#pragma once
#include "TurnInput.h"

class IScoringRule {
public:
    virtual int computeScore(const TurnInput& input) = 0;
    virtual ~IScoringRule() = default;
};
