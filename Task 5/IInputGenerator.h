#pragma once
#include "TurnInput.h"

class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput Generate() = 0;
};
