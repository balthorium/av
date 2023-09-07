#pragma once

#include "AvDaisy.hpp"
#include "AvButton.hpp"
#include <memory>

class AvBoard
{
public:
    AvBoard(int daisyCount);
    AvBoard(const AvBoard &that);
    virtual AvBoard &operator=(const AvBoard &that);
    virtual ~AvBoard();

    virtual void setup();
    virtual bool isPressed(const AvButton &button);
    virtual void setLit(const AvButton &button);
    virtual void setLit(const std::vector<AvButton> &buttons);
    virtual void setUnlit(const AvButton &button);
    virtual void clear();
    virtual void test();

    struct Impl;

private:
    std::unique_ptr<Impl> _impl;
};