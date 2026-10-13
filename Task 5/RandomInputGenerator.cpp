#include "RandomInputGenerator.h"
#include "CardBuilder.h"
#include <cstdlib>

TurnInput RandomInputGenerator::Generate() {
    int value = (std::rand() % 13) + 1;
    return TurnInput{ value, BuildHandForRank(value) };
}
