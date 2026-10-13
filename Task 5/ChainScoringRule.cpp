#include "ChainScoringRule.h"

ChainScoringRule::ChainScoringRule() {
    // Chain (strongest first): Flush Five -> Flush House -> Five of a Kind
    // -> Royal Flush -> Straight Flush -> Four of a Kind -> Full House
    // -> Flush -> Straight -> Three of a Kind -> Two Pair -> Pair -> High Card
    m_flushFiveChecker.SetNext(&m_flushHouseChecker);
    m_flushHouseChecker.SetNext(&m_fiveOfAKindChecker);
    m_fiveOfAKindChecker.SetNext(&m_royalFlushChecker);
    m_royalFlushChecker.SetNext(&m_straightFlushChecker);
    m_straightFlushChecker.SetNext(&m_fourOfAKindChecker);
    m_fourOfAKindChecker.SetNext(&m_fullHouseChecker);
    m_fullHouseChecker.SetNext(&m_flushChecker);
    m_flushChecker.SetNext(&m_straightChecker);
    m_straightChecker.SetNext(&m_threeOfAKindChecker);
    m_threeOfAKindChecker.SetNext(&m_twoPairChecker);
    m_twoPairChecker.SetNext(&m_pairChecker);
    m_pairChecker.SetNext(&m_highCardChecker);
}

int ChainScoringRule::ComputeScore(const TurnInput& input) {
    HandRank rank = m_flushFiveChecker.Check(input);
    return ConvertRankToScore(rank);
}

int ChainScoringRule::ConvertRankToScore(HandRank rank) {
    switch (rank) {
    case HandRank::FLUSH_FIVE:
        return 100;
    case HandRank::FLUSH_HOUSE:
        return 80;
    case HandRank::FIVE_OF_A_KIND:
        return 70;
    case HandRank::ROYAL_FLUSH:
        return 60;
    case HandRank::STRAIGHT_FLUSH:
        return 50;
    case HandRank::FOUR_OF_A_KIND:
        return 40;
    case HandRank::FULL_HOUSE:
        return 35;
    case HandRank::FLUSH:
        return 30;
    case HandRank::STRAIGHT:
        return 25;
    case HandRank::THREE_OF_A_KIND:
        return 20;
    case HandRank::TWO_PAIR:
        return 15;
    case HandRank::PAIR:
        return 10;
    case HandRank::HIGH_CARD:
    default:
        return 5;
    }
}
