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
    /*
     * 构造FtpPacket
     * @param 一个带结束符的，表示一个Ftp数据包的字节序列
     */
    explicit FtpPacket(const std::string& buffer);

    /*
     * 构造FtpPacket
     * @param type Ftp类型，有Request,Respond,Error
     * @param cmd  Ftp命令，详见enum FtpCommand
     * @param arg  Ftp命令参数
     */
    explicit FtpPacket(FtpType type, FtpCommand cmd, const std::string& arg)
        : type(type)
        , cmd(cmd)
        , arg(arg)
    {
    }

    /*
     * FtpPacket信息
     * @return FtpPacket信息，用于调试。
     */
    std::string toString() const;
};
