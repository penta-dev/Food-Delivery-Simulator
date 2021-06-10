#pragma once
#include "ASSystem.h"
class ASFIFOSystem :
    public ASSystem
{
public:
    virtual void process(float time);
};

