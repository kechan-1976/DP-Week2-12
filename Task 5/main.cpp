#include <memory>
#include <ctime>
#include <cstdlib>
#include "RunSession.h"
#include "RandomInputGenerator.h"
#include "ChainScoringRule.h"
#include "ModifiedRewardRule.h"
#include "ShopSystem.h"


int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    RunSession session(
        std::make_unique<RandomInputGenerator>(),
        std::make_unique<ChainScoringRule>(),
        std::make_unique<ModifiedRewardRule>(),
        std::make_unique<ShopSystem>()
    );

    session.StartRun(3);
    return 0;
}
