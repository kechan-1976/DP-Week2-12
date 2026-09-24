#include "RandomInputGenerator.h"
#include <cstdlib>

TurnInput RandomInputGenerator::generate() {
    return { rand() % 10 + 1 };
}
