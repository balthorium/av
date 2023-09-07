#pragma once

#include <memory>
#include "AvMode.hpp"
#include "AvBoard.hpp"

class AvModeBootstrap : public AvMode 
{
public:
    AvModeBootstrap(AvBoard &board);
    AvModeBootstrap(const AvModeBootstrap &that);
    virtual AvModeBootstrap &operator=(const AvModeBootstrap &that);
    virtual ~AvModeBootstrap();

    virtual void setup();
    virtual State loop();

    struct Impl;

private:
    std::unique_ptr<Impl> _impl;
};