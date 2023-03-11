#pragma once
#include <asio/io_service.hpp>
#include <asio/ip/tcp.hpp>
#include <memory>
#include <utility>
#include <vector>
#include "mysql/SqlConnection.h"
class FtpConnection;
using FtpConnectionPtr = std::shared_ptr<FtpConnection>;
//服务器
class NetDiskServer
{
public:
    NetDiskServer(asio::io_context& io,
        const asio::ip::tcp::endpoint& ep,
        const std::string& host,
        uint16_t port,
        const std::string& userName,
        const std::string& passWord,
        const std::string& dataBaseName
        )
        : io_(io)
        , serverPoint(ep)
        , acceptor_(io, ep)
        , sqlConnection(host,port,userName,passWord,dataBaseName)
    {
    }
    //开始接收客户端连接
    void startAccept();

private:
    asio::io_context& io_;
    asio::ip::tcp::endpoint serverPoint;
    asio::ip::tcp::acceptor acceptor_;
    SqlConnection sqlConnection;
    //建立新的Ftp连接
    void establishFtpConnection(FtpConnectionPtr connection);
};