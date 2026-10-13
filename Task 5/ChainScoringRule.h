#pragma once
#include "IScoringRule.h"
#include "HighCardChecker.h"
#include "PairChecker.h"
#include "TwoPairChecker.h"
#include "ThreeOfAKindChecker.h"
#include "StraightChecker.h"
#include "FlushChecker.h"
#include "FullHouseChecker.h"
#include "FourOfAKindChecker.h"
#include "StraightFlushChecker.h"
#include "RoyalFlushChecker.h"
#include "FiveOfAKindChecker.h"
#include "FlushHouseChecker.h"
#include "FlushFiveChecker.h"

// Scoring strategy that delegates hand evaluation to the checker chain,
// then converts the resulting HandRank into a numeric score.
class ChainScoringRule : public IScoringRule {
public:
    ChainScoringRule();
    ChainScoringRule(const ChainScoringRule&) = delete;
    ChainScoringRule& operator=(const ChainScoringRule&) = delete;

    int ComputeScore(const TurnInput& input) override;

private:
    int ConvertRankToScore(HandRank rank);

    FlushFiveChecker m_flushFiveChecker;
    FlushHouseChecker m_flushHouseChecker;
    FiveOfAKindChecker m_fiveOfAKindChecker;
    RoyalFlushChecker m_royalFlushChecker;
    StraightFlushChecker m_straightFlushChecker;
    FourOfAKindChecker m_fourOfAKindChecker;
    FullHouseChecker m_fullHouseChecker;
    FlushChecker m_flushChecker;
    StraightChecker m_straightChecker;
    ThreeOfAKindChecker m_threeOfAKindChecker;
    TwoPairChecker m_twoPairChecker;
    PairChecker m_pairChecker;
    HighCardChecker m_highCardChecker;
};
