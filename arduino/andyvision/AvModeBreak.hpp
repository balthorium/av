#pragma once

#include <memory>
#include "AvMode.hpp"
#include "AvBoard.hpp"

class AvModeBreak : public AvMode 
{
public:
    AvModeBreak(AvBoard &board, const std::vector<AvButton> &break_buttons, AvMode::State break_state);
    AvModeBreak(const AvModeBreak &that);
    virtual AvModeBreak &operator=(const AvModeBreak &that);
    virtual ~AvModeBreak();

    virtual void setup();
    virtual State loop();

    struct Impl;

private:
    std::unique_ptr<Impl> _impl;
};