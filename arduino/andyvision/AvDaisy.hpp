#pragma once

#include "Arduino.h"
#include <memory>

class AvDaisy
{
public:
    AvDaisy(byte i2c_address);
    AvDaisy(const AvDaisy &that);
    virtual AvDaisy &operator=(const AvDaisy &that);
    virtual ~AvDaisy();

    void setup();
    byte getI2cAddress() const;
    byte getPressed() const;
    void setLit(byte lit_buttons);
    void setUnlit(byte unlit_buttons);
    byte getLit() const;

    struct Impl;

private:
    std::unique_ptr<Impl> _impl;
};
