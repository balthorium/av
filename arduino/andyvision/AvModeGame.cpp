#include <ArduinoLog.h>
#include "AvModeGame.hpp"
#include "AvButton.hpp"

struct AvModeGame::Impl
{
    Impl(AvBoard &board, int level) : board(board), level(level), start_time(0) {}
    AvBoard &board;
    int level;
    AvButton lighted_button;
    std::vector<AvButton> buttons;
    unsigned long start_time;
};

void _pick_lighted_button(std::unique_ptr<AvModeGame::Impl> &impl)
{
    AvButton prev_lighted_button(impl->lighted_button);
    do
    {
        impl->lighted_button = impl->buttons[random((impl->buttons).size())];
    } while (impl->lighted_button == prev_lighted_button);
}

AvModeGame::AvModeGame(AvBoard &board, int level)
    : _impl{std::make_unique<Impl>(board, level)}
{
}

AvModeGame::AvModeGame(const AvModeGame &that)
    : _impl{std::make_unique<Impl>(*that._impl)}
{
}

AvModeGame &AvModeGame::operator=(const AvModeGame &that)
{
    _impl = std::make_unique<Impl>(*that._impl);
}

AvModeGame::~AvModeGame()
{
}

void AvModeGame::setup()
{
    Log.noticeln("AvModeGame setup, level %d", _impl->level);
    if (_impl->level < 4) _impl->buttons.insert(_impl->buttons.end(), red_buttons.begin(), red_buttons.end());
    if (_impl->level > 0 && _impl->level < 5) _impl->buttons.insert(_impl->buttons.end(), green_buttons.begin(), green_buttons.end());
    if (_impl->level > 1 && _impl->level < 6) _impl->buttons.insert(_impl->buttons.end(), yellow_buttons.begin(), yellow_buttons.end());
    if (_impl->level > 2) _impl->buttons.insert(_impl->buttons.end(), blue_buttons.begin(), blue_buttons.end());
    _impl->start_time = millis();
    _pick_lighted_button(_impl);
    _impl->board.clear();
    _impl->board.setLit(_impl->buttons);
}

AvMode::State AvModeGame::loop()
{

    // select a new button to light if the correct button is pressed
    if (_impl->board.isPressed(_impl->lighted_button))
    {
        _impl->board.setLit(_impl->lighted_button);
        _pick_lighted_button(_impl);
    }

    // blink the selected button
    if (((millis() - _impl->start_time) / 250) % 2 == 0)
    {
        _impl->board.setLit(_impl->lighted_button);
    }
    else
    {
        _impl->board.setUnlit(_impl->lighted_button);
    }

    return ABIDING;
}