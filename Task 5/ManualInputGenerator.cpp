#include "ManualInputGenerator.h"
#include "CardBuilder.h"

TurnInput ManualInputGenerator::Generate() {
    return TurnInput{ 3, BuildHandForRank(3) };
}
