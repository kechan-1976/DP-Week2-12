#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "RunSession.h"
#include "RandomInputGenerator.h"
#include "SimpleScoringRule.h"
#include "ModifiedRewardRule.h"

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    
    RunSession session(
        std::make_unique<RandomInputGenerator>(),
        std::make_unique<SimpleScoringRule>(),
        std::make_unique<ModifiedRewardRule>()
    );
    
    session.run();
    
    return 0;
}
