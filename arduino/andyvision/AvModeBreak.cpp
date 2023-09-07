#include <ArduinoLog.h>
#include "AvModeBreak.hpp"
#include "AvButton.hpp"

struct AvModeBreak::Impl
{
    Impl(AvBoard &board, const std::vector<AvButton> &break_buttons, AvMode::State break_state) : 
        board(board), break_buttons(break_buttons), break_state(break_state), triggered(false) {}
    AvBoard &board;
    std::vector<AvButton> break_buttons;
    AvMode::State break_state;
    bool triggered;
};

AvModeBreak::AvModeBreak(AvBoard &board, const std::vector<AvButton> &break_buttons, AvMode::State break_state)
    : _impl{std::make_unique<Impl>(board, break_buttons, break_state)}
{
}

AvModeBreak::AvModeBreak(const AvModeBreak &that)
    : _impl{std::make_unique<Impl>(*that._impl)}
{
}

AvModeBreak &AvModeBreak::operator=(const AvModeBreak &that)
{
    _impl = std::make_unique<Impl>(*that._impl);
}

AvModeBreak::~AvModeBreak()
{
}

void AvModeBreak::setup()
{
    Log.noticeln("AvModeBreak setup");
    _impl->triggered = false;
}

AvMode::State AvModeBreak::loop()
{
    size_t pressed_buttons = 0;
    for (AvButton button : _impl->break_buttons) 
    {
        if (_impl->board.isPressed(button))
        {
            pressed_buttons++;
        }
    }
    if (pressed_buttons == _impl->break_buttons.size())
    {
        _impl->board.setLit(_impl->break_buttons);
        _impl->triggered = true;
    } else {
        if (_impl->triggered) 
        {
            return _impl->break_state;
        }
    }

    return AvMode::ABIDING;
}