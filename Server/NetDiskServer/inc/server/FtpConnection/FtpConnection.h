#pragma once
//
// Created by li on 2020/3/25.
//
#include <asio/buffer.hpp>
#include <asio/io_service.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/read_until.hpp>
#include <asio/write.hpp>

#include "Command/command.h"
#include "RequestHandler/FtpPacketHandler.h"
/// Ftp连接类
class FtpConnection : public std::enable_shared_from_this<FtpConnection>
{
public:
    /*
     * 构造FtpConnection
     * @param 绑定的io_context
     * @param 数据库连接
     */
    explicit FtpConnection(asio::io_context& io,SqlConnection& sqlConnection)
        : commandSocket_(io)
        , dataSocket_(io)
        , sqlConnection(sqlConnection)
        , handler(sqlConnection)
    {
    }

    ~FtpConnection();
    /*
     * 读取下一个数据包并处理
     */
    void readNextFtpPacket();
    /*
     * 清除接收缓冲区
     */
    void clearBuffer()
    {
        connectionBuffer_.clear();
    }
    /*
     * 获取命令TCP连接
     * @return TCP连接
     */
    asio::ip::tcp::socket& commandSocket()
    {
        return commandSocket_;
    }
    /*
     * 获取数据TCP连接
     * @return TCP连接
     */
    asio::ip::tcp::socket& dataSocket()
    {
        return dataSocket_;
    }

    /*
     * 发送一个Ftp响应
     * @param cmd Ftp命令
     * @param arg Ftp命令参数
     */
    void sendFtpRespond(FtpCommand cmd, const std::string& arg);

    /*
     * 发送一个Ftp请求
     * @param cmd Ftp命令
     * @param arg Ftp命令参数
     */
    void sendFtpRequest(FtpCommand cmd, const std::string& arg);
    /*
     * 获取数据库连接
     * @return 数据库连接
     */
    SqlConnection& getSqlConnection() const
    {
        return sqlConnection;
    }

private:
    asio::ip::tcp::socket commandSocket_;
    asio::ip::tcp::socket dataSocket_;
    FtpPacketHandler handler;
    std::string connectionBuffer_;
    SqlConnection& sqlConnection;
};
