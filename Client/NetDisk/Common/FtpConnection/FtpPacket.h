#pragma once
//
// Created by li on 2020/3/25.
//
#include <sstream>
#include <string>
#include <vector>
#include "Command/command.h"

class FtpPacket
{
public:
    FtpType type;
    FtpCommand cmd;
    std::string arg;
    explicit FtpPacket(const std::string& buffer);

    explicit FtpPacket(FtpType type, FtpCommand cmd, const std::string& arg)
        : type(type)
        , cmd(cmd)
        , arg(arg)
    {
    }

    std::string toString() const;
};
