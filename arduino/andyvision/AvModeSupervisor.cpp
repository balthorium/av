#include <ArduinoLog.h>
#include <map>
#include "AvModeSupervisor.hpp"
#include "AvBoard.hpp"
#include "AvModeBootstrap.hpp"
#include "AvModeSplash.hpp"
#include "AvModeGame.hpp"
#include "AvModeBreak.hpp"

struct AvModeSupervisor::Impl
{
    Impl() : 
        board(3), 
        state(AvMode::BOOTING), 
        stateMachine {
            { 
                AvMode::BOOTING, 
                { 
                    std::shared_ptr<AvMode>(new AvModeBootstrap(board)) 
                } 
            },
            { 
                AvMode::INITIALIZING, 
                { 
                    std::shared_ptr<AvMode>(new AvModeSplash(board)) 
                } 
            },
            { 
                AvMode::RUNNING_LVL_0, 
                { 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ul, blue_button_ur }, AvMode::State::RUNNING_LVL_1)), 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ll, blue_button_lr }, AvMode::State::INITIALIZING )), 
                    std::shared_ptr<AvMode>(new AvModeGame(board, 0)) 
                } 
            },
            { 
                AvMode::RUNNING_LVL_1, 
                { 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ul, blue_button_ur }, AvMode::State::RUNNING_LVL_2)), 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ll, blue_button_lr }, AvMode::State::INITIALIZING )), 
                    std::shared_ptr<AvMode>(new AvModeGame(board, 1)) 
                } 
            },
            { 
                AvMode::RUNNING_LVL_2, 
                { 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ul, blue_button_ur }, AvMode::State::RUNNING_LVL_3)), 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ll, blue_button_lr }, AvMode::State::INITIALIZING )), 
                    std::shared_ptr<AvMode>(new AvModeGame(board, 2)) 
                } 
            },
            { 
                AvMode::RUNNING_LVL_3, 
                { 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ul, blue_button_ur }, AvMode::State::RUNNING_LVL_4)), 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ll, blue_button_lr }, AvMode::State::INITIALIZING )), 
                    std::shared_ptr<AvMode>(new AvModeGame(board, 3)) 
                } 
            },
            { 
                AvMode::RUNNING_LVL_4, 
                { 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ul, blue_button_ur }, AvMode::State::RUNNING_LVL_5)), 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ll, blue_button_lr }, AvMode::State::INITIALIZING )), 
                    std::shared_ptr<AvMode>(new AvModeGame(board, 4)) 
                } 
            },
            { 
                AvMode::RUNNING_LVL_5, 
                { 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ul, blue_button_ur }, AvMode::State::RUNNING_LVL_6)), 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ll, blue_button_lr }, AvMode::State::INITIALIZING )), 
                    std::shared_ptr<AvMode>(new AvModeGame(board, 5)) 
                } 
            },
            { 
                AvMode::RUNNING_LVL_6, 
                { 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ul, blue_button_ur }, AvMode::State::RUNNING_LVL_0)), 
                    std::shared_ptr<AvMode>(new AvModeBreak(board, std::vector<AvButton> { blue_button_ll, blue_button_lr }, AvMode::State::INITIALIZING )), 
                    std::shared_ptr<AvMode>(new AvModeGame(board, 6))
                } 
            }
        } {}
    AvBoard board;
    AvMode::State state;
    std::map<AvMode::State, std::vector<std::shared_ptr<AvMode>>> stateMachine;
};

void _setupActiveModes(const std::unique_ptr<AvModeSupervisor::Impl> &_impl)
{
    for (std::shared_ptr<AvMode> mode : _impl->stateMachine[_impl->state])
    {
        mode->setup();
    }
}

AvModeSupervisor::AvModeSupervisor()
    : _impl{std::make_unique<Impl>()}
{
}

AvModeSupervisor::AvModeSupervisor(const AvModeSupervisor &that)
    : _impl{std::make_unique<Impl>(*that._impl)}
{
}

AvModeSupervisor &AvModeSupervisor::operator=(const AvModeSupervisor &that)
{
    _impl = std::make_unique<Impl>(*that._impl);
}

AvModeSupervisor::~AvModeSupervisor()
{
}

void AvModeSupervisor::setup()
{
    Log.noticeln("AvModeSupervisor setup");
    _setupActiveModes(_impl);
}

void AvModeSupervisor::loop()
{
    for (std::shared_ptr<AvMode> mode : _impl->stateMachine[_impl->state])
    {
        AvMode::State new_state = mode->loop();
        if (new_state != _impl->state && new_state != AvMode::ABIDING) 
        {
            _impl->state = new_state;
            _setupActiveModes(_impl);
            break;
        }
    }
}