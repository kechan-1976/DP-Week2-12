#pragma once
#include "TurnInput.h"
#include "HandRank.h"

// Abstract handler: every checker answers "does this hand match my rule?"
// and passes the hand to the next checker if it does not.
class PokerHandChecker {
public:
    virtual ~PokerHandChecker() = default;

    virtual HandRank Check(const TurnInput& hand) = 0;
    void SetNext(PokerHandChecker* next);

protected:
    PokerHandChecker* m_nextChecker = nullptr;
};
