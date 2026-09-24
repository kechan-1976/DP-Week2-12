#include "SimpleScoringRule.h"

int SimpleScoringRule::computeScore(const TurnInput& input) {
    return input.value;
}
