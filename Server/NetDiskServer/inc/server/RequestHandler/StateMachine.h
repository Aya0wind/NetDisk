#pragma once
//
// Created by li on 2020/3/26.
//
///状态
enum class State
{
    NOLOGIN,
    NEEDPASS,
    READY,
    BUSY,
};
///触发动作
enum class Action
{
    Login,
    PASS,
    CMD_GET,
    CMD_SEND_START,
    CMD_SEND_OVER,
    CMD_REC_START,
    CMD_REC_OVER,
};
//状态机
class StateMachine
{
    State currentState;

public:
    StateMachine()
        : currentState(State::NOLOGIN)
    {
    }
    StateMachine(State initState)
        : currentState(initState)
    {
    }
    //接收触发动作
    State getNewAction(Action action);
    void setState(State state)
    {
        currentState = state;
    }
    //当前状态
    State getCurrentState() const
    {
        return currentState;
    }
};
