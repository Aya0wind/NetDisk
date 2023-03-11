//
// Created by li on 2020/3/25.
//
#include "FtpConnection/FtpConnection.h"

#include <asio/buffer.hpp>
#include <iostream>

void FtpConnection::readNextFtpPacket()
{
    auto connection = shared_from_this();
    //读取一个Ftp命令
    asio::async_read_until(
        connection->commandSocket(), asio::dynamic_buffer(connectionBuffer_), "\r\n",
        [connection, this](const asio::error_code& err, size_t len) {
            if (err)
            {
                std::cout << err.message() << std::endl;
                return;
            }
            FtpPacket packet(this->connectionBuffer_);
            std::cout << packet.toString() << std::endl;
            handler.handleFtpPacket(packet,connection);
        });
}
FtpConnection::~FtpConnection()
{
    std::cout << "连接已断开" << std::endl;
    commandSocket_.close();
    dataSocket_.close();
}

void FtpConnection::sendFtpRequest(FtpCommand cmd, const std::string& arg)
{
    std::string packet;
    //主机字节序转网络字节序
    uint16_t type = htons(( uint16_t )FtpType::Request);
    char* byte = ( char* )&type;
    packet.push_back(*byte);
    packet.push_back(*(byte + 1));
    uint16_t command = htons(( uint16_t )cmd);
    byte = ( char* )&command;
    packet.push_back(*byte);
    packet.push_back(*(byte + 1));
    packet += arg;
    packet += "\r\n";
    //异步发送数据包
    asio::async_write(this->commandSocket(), asio::buffer(packet), [](const asio::error_code& err, size_t len) {
        if (err)
        {
            std::cout << "请求发送失败，连接异常断开！将终止FTP连接." << err.message() << std::endl;
        }
    });
}
void FtpConnection::sendFtpRespond(FtpCommand cmd, const std::string& arg)
{
    std::string packet;
    //主机字节序转网络字节序
    uint16_t type = htons(( uint16_t )FtpType::Respond);
    char* byte = ( char* )&type;
    packet.push_back(*byte);
    packet.push_back(*(byte + 1));
    uint16_t command = htons(( uint16_t )cmd);
    byte = ( char* )&command;
    packet.push_back(*byte);
    packet.push_back(*(byte + 1));
    packet += arg;
    packet += "\r\n";
    //异步发送数据包
    asio::async_write(this->commandSocket(), asio::buffer(packet), [](const asio::error_code& err, size_t len) {
        if (err)
        {
            std::cout << "请求发送失败，连接异常断开！将终止FTP连接." << err.message() << std::endl;
        }
    });
}
