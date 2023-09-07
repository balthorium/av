#include <Wire.h>
#include <ArduinoLog.h>
#include "AvModeBootstrap.hpp"

struct AvModeBootstrap::Impl
{
    Impl(AvBoard &board) : board(board) {}
    AvBoard &board;
};

AvModeBootstrap::AvModeBootstrap(AvBoard &board)
    : _impl{std::make_unique<Impl>(board)}
{
}

AvModeBootstrap::AvModeBootstrap(const AvModeBootstrap &that)
    : _impl{std::make_unique<Impl>(*that._impl)}
{
}

AvModeBootstrap &AvModeBootstrap::operator=(const AvModeBootstrap &that)
{
    _impl = std::make_unique<Impl>(*that._impl);
}

AvModeBootstrap::~AvModeBootstrap()
{
}

void AvModeBootstrap::setup()
{
    Log.noticeln("AvModeBootstrap setup");
    randomSeed(analogRead(0));
    Serial.begin(9600);
    Log.begin(LOG_LEVEL_NOTICE, &Serial);
    Wire.begin();
    _impl->board.setup();
}

AvMode::State AvModeBootstrap::loop()
{
    return INITIALIZING;
}