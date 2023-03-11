//
// Created by li on 2020/3/26.
//

#include "RequestHandler/StateMachine.h"
State StateMachine::getNewAction(Action action)
{
    switch (this->currentState)
    {
        case State::NOLOGIN:
            if (action == Action::Login)
                currentState = State::NEEDPASS;
            break;
        case State::NEEDPASS:
            if (action == Action::PASS)
                currentState = State::READY;
            break;
        case State::READY:
        {
            switch (action)
            {
                case Action::CMD_SEND_START:
                    break;
                case Action::CMD_SEND_OVER:
                    break;
                case Action::CMD_REC_START:
                    break;
                case Action::CMD_REC_OVER:
                    break;
                default:
                    break;
            }
        }
        break;
        case State::BUSY:
        {
            switch (action)
            {
                case Action::CMD_SEND_START:
                    break;
                case Action::CMD_SEND_OVER:
                    break;
                case Action::CMD_REC_START:
                    break;
                case Action::CMD_REC_OVER:
                    break;
                default:
                    break;
            }
        }
        break;
        default:
            break;
    }
    return this->currentState;
}
