#pragma once
//
// Created by li on 2020/3/25.
//
#include <memory>

#include "FtpConnection/FtpPacket.h"
#include "StateMachine.h"
#include "mysql/SqlConnection.h"
#include "mysql/UserInfo/UserInfo.h"
class FtpConnection;
using FtpConnectionPtr = std::shared_ptr<FtpConnection>;

class FtpPacketHandler
{
    SqlConnection& sqlConnection;
    StateMachine stateMachine;
    UserInfo client;
public:
    explicit FtpPacketHandler(SqlConnection& sqlConnection)
        : sqlConnection(sqlConnection)
        , stateMachine(State::NOLOGIN)
    {
    }
    /*
     * 处理Ftp数据包
     * @param packet 用户名
     * @param connection 所在的FtpConnection
     * @return 是否继续接收下一个包
     */
    bool handleFtpPacket(const FtpPacket& packet, const FtpConnectionPtr& connection);
    /*
     * 处理Ftp请求
     * @param packet 用户名
     * @param connection 所在的FtpConnection
     * @return 是否继续接收下一个包
     */
    bool handleFtpRequest(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection);
    /*
     * 处理Ftp响应
     * @param cmd Ftp命令
     * @param arg Ftp命令参数
     * @param arg 所在的FtpConnection
     * @return 是否继续接收下一个包
     */
    bool handleFtpRespond(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection);
    /*
      * 正在发送文件时的处理函数
      * @param cmd Ftp命令
      * @param arg Ftp命令参数
      * @param arg 所在的FtpConnection
      * @return 是否继续接收下一个包
      */
    bool onBusy(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection);
    /*
      * 正在接收文件时的处理函数
      * @param cmd Ftp命令
      * @param arg Ftp命令参数
      * @param arg 所在的FtpConnection
      * @return 是否继续接收下一个包
      */
    bool onReady(FtpCommand cmd, const std::string& arg, const FtpConnectionPtr& connection);
};
