#pragma once
#include <vector>
#include "Card.h"

// Builds a random 5-card hand that matches the dummy hand type
// (1 = High Card ... 13 = Flush Five), so the shown cards agree with
// what the checker chain reports.
std::vector<Card> BuildHandForRank(int value);
