#pragma once

class AvMode
{
public:
    enum State
    {
        ABIDING = 0,
        BOOTING,
        INITIALIZING,
        RUNNING_LVL_0,
        RUNNING_LVL_1,
        RUNNING_LVL_2,
        RUNNING_LVL_3,
        RUNNING_LVL_4,
        RUNNING_LVL_5,
        RUNNING_LVL_6
    };

    virtual ~AvMode() {}
    virtual void setup() = 0;
    virtual State loop() = 0;
};