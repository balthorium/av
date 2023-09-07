#pragma once

#include <Arduino.h>
#include <vector>

struct AvButton
{

    enum Color
    {
        BLUE,
        GREEN,
        YELLOW,
        RED
    };

    AvButton();
    AvButton(Color color, byte daisy_index, byte button_address);
    AvButton(const AvButton &button);
    virtual ~AvButton(){};

    virtual AvButton &operator=(const AvButton &rhs);
    virtual bool operator==(const AvButton &rhs) const;

    Color color;
    byte daisy_index;
    byte button_address;
};

extern std::vector<AvButton> red_buttons;
extern std::vector<AvButton> green_buttons;
extern std::vector<AvButton> yellow_buttons;
extern std::vector<AvButton> blue_buttons;

extern AvButton blue_button_ul;
extern AvButton blue_button_ur;

extern AvButton blue_button_ll;
extern AvButton blue_button_lr;