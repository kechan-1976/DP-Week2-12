#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

//Structure Data Utama
// A playing card. rank: 2-10, 11 = J, 12 = Q, 13 = K, 14 = A.
// Kartu: 'S' (spades), 'H' (hearts), 'D' (diamonds), 'C' (clubs).
struct Card {
    int  rank;
    char suit;

    string ToString() const {
        string r;
        switch (rank) {
        case 11: r = "J"; break;
        case 12: r = "Q"; break;
        case 13: r = "K"; break;
        case 14: r = "A"; break;
        default: r = to_string(rank); break;
        }
        return r + suit;
    }
};

struct TurnInput {
    int value;
    vector<Card> cards;
};

// Ordered from weakest to strongest.
enum class HandRank {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH,
    FIVE_OF_A_KIND,
    FLUSH_HOUSE,
    FLUSH_FIVE
};

// Card builder: random 5-card hand matching the dummy hand type
namespace {

    const char SUITS[4] = { 'S', 'H', 'D', 'C' };

    int Rand(int n) { return rand() % n; }                 
    int RandRank() { return 2 + Rand(13); }                
    char RandSuit() { return SUITS[Rand(4)]; }

    // n distinct suits in random order
    vector<char> DistinctSuits(int n) {
        vector<char> s(SUITS, SUITS + 4);
        for (int i = 3; i > 0; --i) swap(s[i], s[Rand(i + 1)]);
        s.resize(n);
        return s;
    }

    // `count` distinct ranks, none of them in `used`
    vector<int> DistinctRanks(int count, vector<int> used = {}) {
        vector<int> out;
        while (static_cast<int>(out.size()) < count) {
            int r = RandRank();
            if (find(used.begin(), used.end(), r) == used.end()) {
                out.push_back(r);
                used.push_back(r);
            }
        }
        return out;
    }

    bool IsStraightRanks(vector<int> r) {
        sort(r.begin(), r.end());
        if (r.back() - r.front() == 4) return true;
        return r == vector<int>{ 2, 3, 4, 5, 14 };          
    }

    bool AllSameSuit(const vector<Card>& c) {
        for (const Card& x : c) if (x.suit != c[0].suit) return false;
        return true;
    }

    // `n` cards of one rank with distinct suits
    void AddOfAKind(vector<Card>& hand, int rank, int n) {
        for (char s : DistinctSuits(n)) hand.push_back({ rank, s });
    }

    vector<Card> Sequence(int start, bool sameSuit) {
        vector<Card> hand;
        char suit = RandSuit();
        for (int i = 0; i < 5; ++i)
            hand.push_back({ start + i, sameSuit ? suit : RandSuit() });
        return hand;
    }

} // namespace

// 1 = High Card ... 13 = Flush Five
vector<Card> BuildHandForRank(int value) {
    vector<Card> hand;

    switch (value) {
    case 1: { // High Card: no pair, no straight, no flush
        vector<int> r;
        do { r = DistinctRanks(5); } while (IsStraightRanks(r));
        do {
            hand.clear();
            for (int x : r) hand.push_back({ x, RandSuit() });
        } while (AllSameSuit(hand));
        break;
    }
    case 2: { // Pair
        vector<int> r = DistinctRanks(4);
        AddOfAKind(hand, r[0], 2);
        for (int i = 1; i < 4; ++i) hand.push_back({ r[i], RandSuit() });
        break;
    }
    case 3: { // Two Pair
        vector<int> r = DistinctRanks(3);
        AddOfAKind(hand, r[0], 2);
        AddOfAKind(hand, r[1], 2);
        hand.push_back({ r[2], RandSuit() });
        break;
    }
    case 4: { // Three of a Kind
        vector<int> r = DistinctRanks(3);
        AddOfAKind(hand, r[0], 3);
        hand.push_back({ r[1], RandSuit() });
        hand.push_back({ r[2], RandSuit() });
        break;
    }
    case 5: { // Straight (mixed suits), start 2..10
        do { hand = Sequence(2 + Rand(9), false); } while (AllSameSuit(hand));
        break;
    }
    case 6: { // Flush: same suit, ranks not in sequence
        vector<int> r;
        do { r = DistinctRanks(5); } while (IsStraightRanks(r));
        char suit = RandSuit();
        for (int x : r) hand.push_back({ x, suit });
        break;
    }
    case 7: { // Full House
        vector<int> r = DistinctRanks(2);
        AddOfAKind(hand, r[0], 3);
        AddOfAKind(hand, r[1], 2);
        break;
    }
    case 8: { // Four of a Kind
        vector<int> r = DistinctRanks(2);
        AddOfAKind(hand, r[0], 4);
        hand.push_back({ r[1], RandSuit() });
        break;
    }
    case 9:   // Straight Flush, start 2..9 (10 would be a royal flush)
        hand = Sequence(2 + Rand(8), true);
        break;
    case 10:  // Royal Flush: 10 J Q K A, same suit
        hand = Sequence(10, true);
        break;
    case 11: { // Five of a Kind: duplicates allowed, suits not all equal
        int rank = RandRank();
        do {
            hand.clear();
            for (int i = 0; i < 5; ++i) hand.push_back({ rank, RandSuit() });
        } while (AllSameSuit(hand));
        break;
    }
    case 12: { // Flush House: full house with every card the same suit
        vector<int> r = DistinctRanks(2);
        char suit = RandSuit();
        for (int i = 0; i < 3; ++i) hand.push_back({ r[0], suit });
        for (int i = 0; i < 2; ++i) hand.push_back({ r[1], suit });
        break;
    }
    case 13: { // Flush Five: five identical cards
        int rank = RandRank();
        char suit = RandSuit();
        for (int i = 0; i < 5; ++i) hand.push_back({ rank, suit });
        break;
    }
    default:
        return BuildHandForRank(1);
    }

    for (int i = static_cast<int>(hand.size()) - 1; i > 0; --i)
        swap(hand[i], hand[Rand(i + 1)]);               // shuffle for display
    return hand;
}
// Input generators

class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput Generate() = 0;
};

class ManualInputGenerator : public IInputGenerator {
public:
    TurnInput Generate() override {
        return TurnInput{ 3, BuildHandForRank(3) };
    }
};

class RandomInputGenerator : public IInputGenerator {
public:
    TurnInput Generate() override {
        int value = (rand() % 13) + 1;
        return TurnInput{ value, BuildHandForRank(value) };
    }
};

// Chain of Responsibility: poker hand checkers
class PokerHandChecker {
public:
    virtual ~PokerHandChecker() = default;

    virtual HandRank Check(const TurnInput& hand) = 0;
    void SetNext(PokerHandChecker* next) { m_nextChecker = next; }

protected:
    PokerHandChecker* m_nextChecker = nullptr;
};

class ValueChecker : public PokerHandChecker {
public:
    ValueChecker(int value, HandRank rank, const char* name)
        : m_value(value), m_rank(rank), m_name(name) {}

    HandRank Check(const TurnInput& hand) override {
        if (hand.value == m_value) {
            cout << "[CHECK] Detected " << m_name << "\n";
            return m_rank;
        }
        if (m_nextChecker)
            return m_nextChecker->Check(hand);
        return HandRank::HIGH_CARD;
    }

private:
    int m_value;
    HandRank m_rank;
    const char* m_name;
};

class PairChecker : public ValueChecker {
public:
    PairChecker() : ValueChecker(2, HandRank::PAIR, "PAIR") {}
};
class TwoPairChecker : public ValueChecker {
public:
    TwoPairChecker() : ValueChecker(3, HandRank::TWO_PAIR, "TWO PAIR") {}
};
class ThreeOfAKindChecker : public ValueChecker {
public:
    ThreeOfAKindChecker() : ValueChecker(4, HandRank::THREE_OF_A_KIND, "THREE OF A KIND") {}
};
class StraightChecker : public ValueChecker {
public:
    StraightChecker() : ValueChecker(5, HandRank::STRAIGHT, "STRAIGHT") {}
};
class FlushChecker : public ValueChecker {
public:
    FlushChecker() : ValueChecker(6, HandRank::FLUSH, "FLUSH") {}
};
class FullHouseChecker : public ValueChecker {
public:
    FullHouseChecker() : ValueChecker(7, HandRank::FULL_HOUSE, "FULL HOUSE") {}
};
class FourOfAKindChecker : public ValueChecker {
public:
    FourOfAKindChecker() : ValueChecker(8, HandRank::FOUR_OF_A_KIND, "FOUR OF A KIND") {}
};
class StraightFlushChecker : public ValueChecker {
public:
    StraightFlushChecker() : ValueChecker(9, HandRank::STRAIGHT_FLUSH, "STRAIGHT FLUSH") {}
};
class RoyalFlushChecker : public ValueChecker {
public:
    RoyalFlushChecker() : ValueChecker(10, HandRank::ROYAL_FLUSH, "ROYAL FLUSH") {}
};
class FiveOfAKindChecker : public ValueChecker {
public:
    FiveOfAKindChecker() : ValueChecker(11, HandRank::FIVE_OF_A_KIND, "FIVE OF A KIND") {}
};
class FlushHouseChecker : public ValueChecker {
public:
    FlushHouseChecker() : ValueChecker(12, HandRank::FLUSH_HOUSE, "FLUSH HOUSE") {}
};
class FlushFiveChecker : public ValueChecker {
public:
    FlushFiveChecker() : ValueChecker(13, HandRank::FLUSH_FIVE, "FLUSH FIVE") {}
};

// Default checker for the lowest hand rank (High Card)
class HighCardChecker : public PokerHandChecker {
public:
    HandRank Check(const TurnInput&) override {
        cout << "[CHECK] Detected HIGH CARD\n";
        return HandRank::HIGH_CARD;
    }
};

// Scoring rules

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int ComputeScore(const TurnInput& input) = 0;
};

class BasicScoringRule : public IScoringRule {
public:
    int ComputeScore(const TurnInput& input) override { return input.value; }
};

// Scoring strategy that delegates hand evaluation to the checker chain,
// then converts the resulting HandRank into a numeric score.
class ChainScoringRule : public IScoringRule {
public:
    ChainScoringRule() {
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
    ChainScoringRule(const ChainScoringRule&) = delete;
    ChainScoringRule& operator=(const ChainScoringRule&) = delete;

    int ComputeScore(const TurnInput& input) override {
        return ConvertRankToScore(m_flushFiveChecker.Check(input));
    }

private:
    int ConvertRankToScore(HandRank rank) {
        switch (rank) {
        case HandRank::FLUSH_FIVE:      return 100;
        case HandRank::FLUSH_HOUSE:     return 80;
        case HandRank::FIVE_OF_A_KIND:  return 70;
        case HandRank::ROYAL_FLUSH:     return 60;
        case HandRank::STRAIGHT_FLUSH:  return 50;
        case HandRank::FOUR_OF_A_KIND:  return 40;
        case HandRank::FULL_HOUSE:      return 35;
        case HandRank::FLUSH:           return 30;
        case HandRank::STRAIGHT:        return 25;
        case HandRank::THREE_OF_A_KIND: return 20;
        case HandRank::TWO_PAIR:        return 15;
        case HandRank::PAIR:            return 10;
        case HandRank::HIGH_CARD:
        default:                        return 5;
        }
    }

    FlushFiveChecker     m_flushFiveChecker;
    FlushHouseChecker    m_flushHouseChecker;
    FiveOfAKindChecker   m_fiveOfAKindChecker;
    RoyalFlushChecker    m_royalFlushChecker;
    StraightFlushChecker m_straightFlushChecker;
    FourOfAKindChecker   m_fourOfAKindChecker;
    FullHouseChecker     m_fullHouseChecker;
    FlushChecker         m_flushChecker;
    StraightChecker      m_straightChecker;
    ThreeOfAKindChecker  m_threeOfAKindChecker;
    TwoPairChecker       m_twoPairChecker;
    PairChecker          m_pairChecker;
    HighCardChecker      m_highCardChecker;
};

// ============================================================
// Reward rules
// ============================================================

class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int ComputeReward(int baseScore, int roundNumber) = 0;
};

class BasicRewardRule : public IRewardRule {
public:
    int ComputeReward(int baseScore, int /*roundNumber*/) override {
        return baseScore;
    }
};

class ModifiedRewardRule : public IRewardRule {
public:
    int ComputeReward(int baseScore, int roundNumber) override {
        if (roundNumber % 2 == 0)
            return baseScore * 2;
        return baseScore + 2;
    }
};

// ============================================================
// Command pattern: shop actions as objects
// (Invoker -> Command -> Receiver)
// ============================================================

// Command interface: uniform way to execute any behavior.
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

// Receiver: contains the actual implementation of the shop behavior.
class ShopSystem {
public:
    void ShowOffer() const {
        cout << "[SHOP] offered: Bonus(+2) cost 2\n";
    }
    void SkipOffer() const {
        cout << "[SHOP] skipped\n";
    }
};

// Concrete commands: each wraps a receiver and the behavior to run.
class OfferItemCommand : public Command {
public:
    explicit OfferItemCommand(ShopSystem* shop) : m_shop(shop) {}
    void execute() override { m_shop->ShowOffer(); }
private:
    ShopSystem* m_shop;
};

class SkipItemCommand : public Command {
public:
    explicit SkipItemCommand(ShopSystem* shop) : m_shop(shop) {}
    void execute() override { m_shop->SkipOffer(); }
private:
    ShopSystem* m_shop;
};

// Invoker: stores commands in a queue and runs them in order,
// without knowing what each command does.
class ShopInvoker {
public:
    void addCommand(unique_ptr<Command> cmd) {
        m_commands.push_back(move(cmd));
    }
    void executeAll() {
        for (auto& cmd : m_commands)
            cmd->execute();
        m_commands.clear();   // Create -> Store -> Execute -> Discard
    }
private:
    vector<unique_ptr<Command>> m_commands;
};

// ============================================================
// Run session (orchestrator, fixed phase order)
// ============================================================

class RunSession {
public:
    RunSession(unique_ptr<IInputGenerator> inputGen,
        unique_ptr<IScoringRule> scoringRule,
        unique_ptr<IRewardRule> rewardRule,
        unique_ptr<ShopSystem> shop)
        : m_inputGen(move(inputGen)),
        m_scoringRule(move(scoringRule)),
        m_rewardRule(move(rewardRule)),
        m_shop(move(shop)) {}

    void StartRun(int totalRounds = 3) {
        cout << "=== RUN START ===\n";

        for (int round = 1; round <= totalRounds; ++round) {
            cout << "\nRound " << round << "\n";

            TurnInput input = m_inputGen->Generate();
            cout << "[PLAY] input generated: " << input.value << "\n";

            cout << "[PLAY] cards:";
            for (const Card& c : input.cards)
                cout << " " << c.ToString();
            cout << "\n";

            int baseScore = m_scoringRule->ComputeScore(input);
            cout << "[SCORE] base score: " << baseScore << "\n";

            int reward = m_rewardRule->ComputeReward(baseScore, round);

            m_money += reward;
            cout << "[REWARD] gain: " << reward << " | money: " << m_money << "\n";

            ShopInvoker invoker;
            invoker.addCommand(make_unique<OfferItemCommand>(m_shop.get()));
            invoker.addCommand(make_unique<SkipItemCommand>(m_shop.get()));
            invoker.executeAll();
        }

        cout << "\n=== RUN END ===\n";
        cout << "Final money: " << m_money << "\n";
    }

private:
    unique_ptr<IInputGenerator> m_inputGen;
    unique_ptr<IScoringRule>    m_scoringRule;
    unique_ptr<IRewardRule>     m_rewardRule;
    unique_ptr<ShopSystem>      m_shop;
    int m_money = 0;
};

// ============================================================
// main: wiring
// ============================================================

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    RunSession session(
        make_unique<RandomInputGenerator>(),
        make_unique<ChainScoringRule>(),
        make_unique<ModifiedRewardRule>(),
        make_unique<ShopSystem>()
    );

    session.StartRun(3);
    return 0;
}
