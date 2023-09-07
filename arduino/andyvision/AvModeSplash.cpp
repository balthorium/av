#include <ArduinoLog.h>
#include "AvModeSplash.hpp"
#include "AvButton.hpp"
#include "AvModeGame.hpp"

struct AvModeSplash::Impl
{
    Impl(AvBoard &board) : board(board),
                           start_time(0),
                           next_interval(0),
                           cycle_limit(3),
                           interval_limit(0) {}
    AvBoard &board;
    std::vector<std::vector<AvButton>> button_sets;
    unsigned long start_time;
    unsigned long next_interval;
    unsigned long cycle_limit;
    unsigned long interval_limit;
};

AvModeSplash::AvModeSplash(AvBoard &board)
    : _impl{std::make_unique<Impl>(board)}
{
    _impl->button_sets.push_back(red_buttons);
    _impl->button_sets.push_back(green_buttons);
    _impl->button_sets.push_back(yellow_buttons);
    _impl->button_sets.push_back(blue_buttons);
    _impl->interval_limit = _impl->cycle_limit * _impl->button_sets.size();
}

AvModeSplash::AvModeSplash(const AvModeSplash &that)
    : _impl{std::make_unique<Impl>(*that._impl)}
{
}

AvModeSplash &AvModeSplash::operator=(const AvModeSplash &that)
{
    _impl = std::make_unique<Impl>(*that._impl);
}

AvModeSplash::~AvModeSplash()
{
}

void AvModeSplash::setup()
{
    Log.noticeln("AvModeSplash setup");
    _impl->start_time = millis();
    _impl->next_interval = 0;
}

AvMode::State AvModeSplash::loop()
{
    unsigned long interval = (millis() - _impl->start_time) / 500;
    if (interval >= _impl->next_interval)
    {
        _impl->board.clear();
        _impl->board.setLit(_impl->button_sets[interval % _impl->button_sets.size()]);
        _impl->next_interval = interval + 1;
    }
    return (_impl->next_interval > _impl->interval_limit) ? AvMode::RUNNING_LVL_0 : AvMode::INITIALIZING;
}