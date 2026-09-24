#pragma once
#include "TurnInput.h"

class IInputGenerator {
public:
    virtual TurnInput generate() = 0;
    virtual ~IInputGenerator() = default;
};
