#include "AvBoard.hpp"
#include "AvDaisy.hpp"

#include <vector>

struct AvBoard::Impl
{
    std::vector<AvDaisy> daisies;
};

AvBoard::AvBoard(int daisyCount)
    : _impl{std::make_unique<Impl>()}
{
    for (int i = 0; i < daisyCount; i++)
    {
        _impl->daisies.push_back(AvDaisy(0x20 + i));
    }
}

AvBoard::AvBoard(const AvBoard &that)
    : _impl{std::make_unique<Impl>(*that._impl)}
{
}

AvBoard &AvBoard::operator=(const AvBoard &that)
{
    _impl = std::make_unique<Impl>(*that._impl);
}

AvBoard::~AvBoard()
{
}

void AvBoard::setup()
{
    for (AvDaisy d : _impl->daisies)
    {
        d.setup();
    }
}

bool AvBoard::isPressed(const AvButton &button)
{
    return _impl->daisies[button.daisy_index].getPressed() & button.button_address;
}

void AvBoard::setLit(const AvButton &button)
{
    _impl->daisies[button.daisy_index].setLit(button.button_address);
}

void AvBoard::setLit(const std::vector<AvButton> &buttons)
{
    for (auto &button : buttons)
    {
        setLit(button);
    }
}

void AvBoard::setUnlit(const AvButton &button)
{
    _impl->daisies[button.daisy_index].setUnlit(button.button_address);
}

void AvBoard::clear()
{
    for (auto &daisy : _impl->daisies)
    {
        daisy.setUnlit(0xFF);
    }
}

void AvBoard::test()
{
    for (auto &daisy : _impl->daisies)
    {
        daisy.setLit(0xFF);
    }
}