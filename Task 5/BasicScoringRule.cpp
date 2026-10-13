#include "BasicScoringRule.h"

int BasicScoringRule::ComputeScore(const TurnInput& input) {
    return input.value;
}
