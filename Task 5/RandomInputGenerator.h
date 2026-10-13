#pragma once
#include "IInputGenerator.h"

class RandomInputGenerator : public IInputGenerator {
public:
    TurnInput Generate() override;
};
