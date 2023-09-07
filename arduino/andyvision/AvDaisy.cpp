#include <ArduinoLog.h>
#include "AvDaisy.hpp"
#include "Wire.h"

struct AvDaisy::Impl
{
  Impl() : i2c_address(0x0), lit_buttons(0x0) {}
  byte i2c_address;
  byte lit_buttons;
};

void _setLit(const std::unique_ptr<AvDaisy::Impl> &_impl)
{
  Log.traceln("[lighting %X, %X]", _impl->i2c_address, _impl->lit_buttons);
  Wire.beginTransmission(_impl->i2c_address);
  Wire.write(0x12); // write to GPIOA
  Wire.write(_impl->lit_buttons);
  Wire.endTransmission();
}

AvDaisy::AvDaisy(byte i2c_address)
    : _impl{std::make_unique<Impl>()}
{
  _impl->i2c_address = i2c_address;
}

AvDaisy::AvDaisy(const AvDaisy &that)
    : _impl{std::make_unique<Impl>(*that._impl)}
{
}

AvDaisy &AvDaisy::operator=(const AvDaisy &that)
{
    _impl = std::make_unique<Impl>(*that._impl);
}

AvDaisy::~AvDaisy()
{
}

void AvDaisy::setup()
{
  Wire.beginTransmission(_impl->i2c_address);
  Wire.write(0x00); // configure IODIRA register
  Wire.write(0x00); // set all pins on A to outputs
  Wire.endTransmission();
}

byte AvDaisy::getI2cAddress() const
{
  return _impl->i2c_address;
}

byte AvDaisy::getPressed() const
{
  Wire.beginTransmission(_impl->i2c_address);
  Wire.write(0x13); // read from GPIOB
  Wire.endTransmission();
  Wire.requestFrom(_impl->i2c_address, 1);
  int pressed_buttons = Wire.read();
  if (pressed_buttons > 0)
  {
    Log.traceln("[pressed %X, %X]", _impl->i2c_address, pressed_buttons);
  }
  return pressed_buttons;
}

void AvDaisy::setLit(byte lit_buttons)
{
  _impl->lit_buttons |= lit_buttons;
  _setLit(_impl);
}

void AvDaisy::setUnlit(byte unlit_buttons)
{
  _impl->lit_buttons &= _impl->lit_buttons ^ unlit_buttons;
  _setLit(_impl);
}

byte AvDaisy::getLit() const
{
  return _impl->lit_buttons;
}
