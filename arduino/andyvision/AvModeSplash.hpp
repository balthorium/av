#pragma once

#include <memory>
#include "AvMode.hpp"
#include "AvBoard.hpp"

class AvModeSplash : public AvMode 
{
public:
    AvModeSplash(AvBoard &board);
    AvModeSplash(const AvModeSplash &that);
    virtual AvModeSplash &operator=(const AvModeSplash &that);
    virtual ~AvModeSplash();

    virtual void setup();
    virtual State loop();

    struct Impl;

private:
    std::unique_ptr<Impl> _impl;
};