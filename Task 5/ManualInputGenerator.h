#pragma once
#include "IInputGenerator.h"

class ManualInputGenerator : public IInputGenerator {
public:
    TurnInput Generate() override;
};
