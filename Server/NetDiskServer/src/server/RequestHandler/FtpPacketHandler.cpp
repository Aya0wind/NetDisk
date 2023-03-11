//
// Created by li on 2020/3/25.
//

#include "RequestHandler/FtpPacketHandler.h"

#include <asio.hpp>
#include <iostream>

#include "FtpConnection/FtpConnection.h"
#include "mysql/SqlService.h"
bool FtpPacketHandler::handleFtpPacket(const FtpPacket& packet, const FtpConnectionPtr& connection)
{
    if (packet.type == FtpType::Request)
    {
        if (this->handleFtpRequest(packet.cmd, packet.arg, connection))
        {
            connection->clearBuffer();
            connection->readNextFtpPacket();
        }
    }
    else if (packet.type == FtpType::Respond)
    {
        if (this->handleFtpRespond(packet.cmd, packet.arg, connection))
        {
            connection->clearBuffer();
            connection->readNextFtpPacket();
        }
    }
    return true;
}

bool FtpPacketHandler::handleFtpRequest(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection)
{
    switch (stateMachine.getCurrentState())
    {
        case State::NOLOGIN:
        {
            if (cmd == FtpCommand::USER)
            {
                SqlService service(connection->getSqlConnection());
                auto queryResult = service.queryUserInfo(arg);
                if (queryResult.second)
                {
                    client = queryResult.first;
                    stateMachine.getNewAction(Action::Login);
                    connection->sendFtpRespond(FtpCommand::NEEDPASS, "");
                    return true;
                }
                else
                {
                    connection->sendFtpRespond(FtpCommand::NOUSER, "");
                    return true;
                }
            }
        }
        break;
        case State::NEEDPASS:
        {
            if (cmd == FtpCommand::PASS)
            {
                if (client.pwd == arg)
                {
                    stateMachine.getNewAction(Action::PASS);
                    connection->sendFtpRespond(FtpCommand::LOGINOK, "");
                    return true;
                }
                else
                {
                    stateMachine.getNewAction(Action::PASS);
                    connection->sendFtpRespond(FtpCommand::PASSINCORRECT, "");
                    return true;
                }
            }
        }
        break;
        case State::BUSY:
        {
            return onBusy(cmd, arg, connection);
        }
        break;
        case State::READY:
        {
            return onReady(cmd, arg, connection);
        }
        break;
        default:
            break;
    }
    connection->sendFtpRespond(FtpCommand::UNKNOWNCMD, "");
    return false;
}
bool FtpPacketHandler::handleFtpRespond(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection)
{
    return false;
}
bool FtpPacketHandler::onBusy(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection)
{
    switch (cmd)
    {
        case FtpCommand::GET:

            break;
        case FtpCommand::PUT:
            break;
        case FtpCommand::RGET:
            break;
        case FtpCommand::RPUT:
            break;
        case FtpCommand::CD:
            break;
        case FtpCommand::PWD:
            break;
        case FtpCommand::LS:
            break;
        case FtpCommand::MKDIR:
            break;
        case FtpCommand::RMDIR:
            break;
        default:
            break;
    }
    return false;
}
bool FtpPacketHandler::onReady(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection)
{
    switch (cmd)
    {
        case FtpCommand::GET:
            break;
        case FtpCommand::PUT:
            break;
        case FtpCommand::RGET:
            break;
        case FtpCommand::RPUT:
            break;
        case FtpCommand::CD:
            break;
        case FtpCommand::PWD:
            break;
        case FtpCommand::LS:
            break;
        case FtpCommand::MKDIR:
            break;
        case FtpCommand::RMDIR:
            break;
        default:
            break;
    }
    return false;
}
