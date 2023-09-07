#pragma once

#include <memory>

class AvModeSupervisor
{
public:
    AvModeSupervisor();
    AvModeSupervisor(const AvModeSupervisor &that);
    virtual AvModeSupervisor &operator=(const AvModeSupervisor &that);
    virtual ~AvModeSupervisor();

    virtual void setup();
    virtual void loop();

    struct Impl;

private:
    std::unique_ptr<Impl> _impl;
};