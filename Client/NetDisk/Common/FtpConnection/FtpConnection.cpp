//
// Created by li on 2020/3/25.
//
#include "FtpConnection/FtpConnection.h"
#include "FtpConnection/FtpPacket.h"
#include <asio/read.hpp>
#include <asio/buffer.hpp>
#include <iostream>

FtpConnection::FtpConnection(asio::io_context &io,QObject* parent)
    :commandSocket_(io)
    ,dataSocket_(io)
    ,parent(parent)
{

}
void FtpConnection::connect(asio::ip::tcp::endpoint endpoint)
{
    auto connection=shared_from_this();
    //异步连接服务器，并等待服务器发送数据传送TCP连接的端口号
    commandSocket().async_connect(endpoint,
                                  [connection,this](const asio::error_code& err){
        if(err)
        {
            std::cout << err.message() << std::endl;
            emit connectOver("连接异常断开",false);
            return;
        }
        //连接成功，检查数据包
         asio::async_read_until(commandSocket_,asio::dynamic_buffer(connectionBuffer_),"\r\n",
                                [connection,this](const asio::error_code& err, size_t)
         {
                if(err)
                {
                     std::cout << err.message() << std::endl;
                     emit connectOver("连接异常断开",false);
                     return;
                }
             FtpPacket packet(connectionBuffer_);
             if(packet.cmd==FtpCommand::PORT)
             {
                 //数据包为PORT命令，连接服务器给定端口
                 auto serverAddress=commandSocket().remote_endpoint().address();
                 auto port=std::atoi(packet.arg.c_str());
                 asio::ip::tcp::endpoint serverDataEndPoint(serverAddress,port);
                 dataSocket_.async_connect(serverDataEndPoint,
                                           [connection,this](const asio::error_code& err)
                 {
                     if(err)
                     {
                          std::cout << err.message() << std::endl;
                          emit connectOver("连接异常断开",false);
                         return;
                     }
                     //命令和数据连接均已建立，连接成功
                     emit connectOver("连接成功",true);
                 });
             }
         });
    });
}

void FtpConnection::login(const QString &userName, const QString &passWord)
{
    auto connection=shared_from_this();
    this->sendFtpRequest(FtpCommand::USER,userName.toStdString());
    handler.setUserInfo(userName.toStdString(),passWord.toStdString());
    connection->clearBuffer();
    readNextFtpPacket();
}
void FtpConnection::readNextFtpPacket()
{
    auto connection = shared_from_this();
    //读下一个命令数据包
    asio::async_read_until(
            connection->commandSocket(), asio::dynamic_buffer(connectionBuffer_), "\r\n",
            [connection, this](const asio::error_code& err, size_t ) {
                if (err)
                {
                    std::cout << err.message() << std::endl;
                    return;
                }
                //处理命令
                FtpPacket packet(connectionBuffer_);
                std::cout<<packet.toString()<<std::endl;
                handler.handleFtpPacket(packet,connection);
            });
}

FtpConnection::~FtpConnection()
{
    std::cout<<"Connection delete!"<<std::endl;
}


//发送一个Ftp请求
void FtpConnection::sendFtpRequest(FtpCommand cmd, const std::string& arg)
{
    std::string packet;
    //主机字节序转网络字节序
    uint16_t type=htons((uint16_t)FtpType::Request);
    char* byte=(char*)&type;
    packet.push_back(*byte);
    packet.push_back(*(byte+1));
    uint16_t command=htons((uint16_t)cmd);
    byte=(char*)&command;
    packet.push_back(*byte);
    packet.push_back(*(byte+1));
    packet+=arg;
    packet+="\r\n";
    //异步发送数据包
    asio::async_write(this->commandSocket(),asio::buffer(packet),
        [](const asio::error_code& err,size_t ){
        if(err)
        {
            std::cout<<"请求发送失败，连接异常断开！将终止FTP连接."<<err.message()<<std::endl;
        }
    });
}
//发送一个Ftp响应
void FtpConnection::sendFtpRespond(FtpCommand cmd, const std::string& arg)
{
    std::string packet;
    uint16_t type=htons((uint16_t)FtpType::Request);
    char* byte=(char*)&type;
    packet.push_back(*byte);
    packet.push_back(*(byte+1));
    uint16_t command=htons((uint16_t)cmd);
    byte=(char*)&command;
    packet.push_back(*byte);
    packet.push_back(*(byte+1));
    packet+=arg;
    packet+="\r\n";
    asio::async_write(this->commandSocket(),asio::buffer(packet),
        [](const asio::error_code& err,size_t ){
        if(err)
        {
            std::cout<<"请求发送失败，连接异常断开！将终止FTP连接."<<err.message()<<std::endl;
        }
    });
}
