//
// Created by li on 2020/3/25.
//
#define STRINGNIFY(N) #N
#include "FtpConnection/FtpPacket.h"
std::string FtpPacket::toString() const
{
    std::string res;
    switch (this->type)
    {
        case FtpType::Request:
            res += "Request: ";
            break;
        case FtpType::Respond:
            res += "Respond: ";
            break;
        case FtpType::Error:
            res += "Error: ";
            break;
    }
    res += getFtpCommandName(cmd);
    res += "\r\n";
    res += "arg: ";
    res += this->arg;
    return res;
}
FtpPacket::FtpPacket(const std::string& buffer)
{
    auto packet = ( FtpPacket* )buffer.c_str();
    auto packetType = ( FtpType )ntohs(( uint16_t )packet->type);
    auto packetCmd = ( FtpCommand )ntohs(( uint16_t )packet->cmd);
    if (packetType != FtpType::Request && packetType != FtpType::Respond)
    {
        this->type = FtpType::Error;
    }
    else
    {
        this->type = packetType;
    }
    this->cmd = packetCmd;
    this->arg = std::string(buffer.begin() + 2 * sizeof(uint16_t), buffer.end() - 2);
}
const char* getFtpCommandName(FtpCommand cmd)
{
    switch (cmd)
    {
        case FtpCommand ::PORT:
            return STRINGNIFY(PORT);
        case FtpCommand::USER:
            return STRINGNIFY(USER);

        case FtpCommand::GET:
            return STRINGNIFY(GET);

        case FtpCommand::PUT:
            return STRINGNIFY(PUT);

        case FtpCommand::CD:
            return STRINGNIFY(CD);

        case FtpCommand::PWD:
            return STRINGNIFY(PWD);

        case FtpCommand::LS:
            return STRINGNIFY(LS);

        case FtpCommand::MKDIR:
            return STRINGNIFY(MKDIR);

        case FtpCommand::RGET:
            return STRINGNIFY(RGET);

        case FtpCommand::RPUT:
            return STRINGNIFY(RPUT);

        case FtpCommand::RMDIR:
            return STRINGNIFY(RMDIR);

        case FtpCommand::PASS:
            return STRINGNIFY(PASS);

        case FtpCommand::NEEDPASS:
            return STRINGNIFY(NEEDPASS);

        case FtpCommand::NOUSER:
            return STRINGNIFY(NOUSER);

        case FtpCommand::LOGINOK:
            return STRINGNIFY(LOGINOK);

        case FtpCommand::PASSINCORRECT:
            return STRINGNIFY(PASSINCORRECT);
        case FtpCommand::UNKNOWNCMD:
            return STRINGNIFY(UNKNOWNCMD);  //未知命令
        default:
            return "";
    }
}