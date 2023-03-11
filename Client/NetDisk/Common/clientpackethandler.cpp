#include "clientpackethandler.h"


//
// Created by li on 2020/3/25.
//

#include "clientpackethandler.h"
#include <asio.hpp>
#include <iostream>
#include "FtpConnection/FtpConnection.h"
#include "FtpConnection/FtpPacket.h"
bool ClientPacketHandler::handleFtpPacket(const FtpPacket& packet, const FtpConnectionPtr& connection)
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

bool ClientPacketHandler::handleFtpRequest(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection)
{
   return false;
}
bool ClientPacketHandler::handleFtpRespond(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection)
{
    switch(cmd)
    {
     case FtpCommand::NEEDPASS:
     {
        connection->sendFtpRequest(FtpCommand::PASS,userInfo.pwd);
     }
     break;
     case FtpCommand::PASSINCORRECT:
     {
        connection->emitLoginOver("密码错误",false);
     }
     break;
     case FtpCommand::NOUSER:
     {
        connection->emitLoginOver("用户不存在！",false);
     }
     break;
     case FtpCommand::LOGINOK:
     {
        connection->emitLoginOver("登录成功！",true);
     }
        break;
     case FtpCommand::FILEEXIST:
     {

     }
        break;
     case FtpCommand::UNKNOWNCMD:
     {

     }
        break;
     default:return false;
     }
    return true;
}


std::ostream& operator<<(std::ostream& os, const UserInfo& info)
{
    os << '[' << info.id << ',' << info.name << ',' << info.pwd << ',' << info.maindir << ']';
    return os;
}
