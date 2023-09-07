#pragma once

#include <memory>
#include "AvMode.hpp"
#include "AvBoard.hpp"

class AvModeGame : public AvMode
{
public:
    AvModeGame(AvBoard &board, int level);
    AvModeGame(const AvModeGame &that);
    virtual AvModeGame &operator=(const AvModeGame &that);
    virtual ~AvModeGame();

    virtual void setup();
    virtual State loop();

    struct Impl;

private:
    std::unique_ptr<Impl> _impl;
};