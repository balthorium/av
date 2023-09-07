#include "AvButton.hpp"

AvButton::AvButton() : color(BLUE), daisy_index(0), button_address(0)
{
}

AvButton::AvButton(Color color, byte daisyAddress, byte buttonAddress) : color(color), daisy_index(daisyAddress), button_address(buttonAddress)
{
}

AvButton::AvButton(const AvButton &button) : color(button.color), daisy_index(button.daisy_index), button_address(button.button_address)
{
}

AvButton &AvButton::operator=(const AvButton &rhs)
{
    color = rhs.color;
    daisy_index = rhs.daisy_index;
    button_address = rhs.button_address;
}

bool AvButton::operator==(const AvButton &rhs) const
{
    return (daisy_index == rhs.daisy_index) && (button_address == rhs.button_address);
}

std::vector<AvButton> red_buttons = {
    AvButton(AvButton::Color::RED, 1, 0x01),
    AvButton(AvButton::Color::RED, 1, 0x80),
    AvButton(AvButton::Color::RED, 1, 0x40),
    AvButton(AvButton::Color::RED, 1, 0x04),
    AvButton(AvButton::Color::RED, 1, 0x08),
    AvButton(AvButton::Color::RED, 1, 0x10)};

std::vector<AvButton> green_buttons = {
    AvButton(AvButton::Color::GREEN, 1, 0x02),
    AvButton(AvButton::Color::GREEN, 2, 0x02),
    AvButton(AvButton::Color::GREEN, 1, 0x20),
    AvButton(AvButton::Color::GREEN, 0, 0x04)};

std::vector<AvButton> yellow_buttons = {
    AvButton(AvButton::Color::YELLOW, 0, 0x01),
    AvButton(AvButton::Color::YELLOW, 2, 0x01),
    AvButton(AvButton::Color::YELLOW, 2, 0x40),
    AvButton(AvButton::Color::YELLOW, 2, 0x10),
    AvButton(AvButton::Color::YELLOW, 0, 0x20),
    AvButton(AvButton::Color::YELLOW, 0, 0x08)};

std::vector<AvButton> blue_buttons = {
    AvButton(AvButton::Color::BLUE, 2, 0x04),
    AvButton(AvButton::Color::BLUE, 2, 0x80),
    AvButton(AvButton::Color::BLUE, 2, 0x20),
    AvButton(AvButton::Color::BLUE, 0, 0x40),
    AvButton(AvButton::Color::BLUE, 0, 0x10),
    AvButton(AvButton::Color::BLUE, 0, 0x02)};

AvButton blue_button_ul(AvButton::Color::BLUE, 0, 0x40);
AvButton blue_button_ur(AvButton::Color::BLUE, 2, 0x20);

AvButton blue_button_ll(AvButton::Color::BLUE, 0, 0x02);
AvButton blue_button_lr(AvButton::Color::BLUE, 2, 0x04);
