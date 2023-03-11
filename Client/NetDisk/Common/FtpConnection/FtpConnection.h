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
#include <QObject>
#include"../clientpackethandler.h"
class FtpConnection :public QObject, public std::enable_shared_from_this<FtpConnection>
{
    Q_OBJECT
public:
    explicit FtpConnection(asio::io_context& io,QObject* parent=nullptr);

    //读取下一个数据包
    void readNextFtpPacket();

    //清除缓冲区
    void clearBuffer()
    {
        connectionBuffer_.clear();
    }
    //获取用于传送命令的TCP连接
    asio::ip::tcp::socket& commandSocket()
    {
        return commandSocket_;
    }
     //获取用于传送数据的TCP连接
    asio::ip::tcp::socket& dataSocket()
    {
        return dataSocket_;
    }
    ~FtpConnection();
    //发送一个Ftp请求
    void sendFtpRespond(FtpCommand cmd,const std::string& arg);
    //发送一个Ftp响应
    void sendFtpRequest(FtpCommand cmd,const std::string& arg);

    //尝试连接服务器
    void connect(asio::ip::tcp::endpoint endpoint);

    //尝试登录
    void login(const QString& userName,const QString& passWord);

    enum class ResultType
    {

    };
signals:
    //连接成功时发射信号
    void connectOver(const QString& message,bool isSucess);

    //登录完成时发射信号
    void LoginOver(const QString& message,bool isSucess);

    //收到命令结果时发射信号
    void CommandFinished(const QString& message,bool isSucess,ResultType type);


public:



    //连接完成时发射信号
    void emitConnectOver(const QString& message,bool isSucess)
    {emit connectOver(message,isSucess);}

    //登录完成时发射信号
    void emitLoginOver(const QString& message,bool isSucess)
    {emit LoginOver(message,isSucess);}

    //收到密码错误时发射信号
    void emitCommandFinished(const QString& message,bool isSucess,ResultType type)
    {emit CommandFinished(message,isSucess,type);}

private:
    asio::ip::tcp::socket commandSocket_;
    asio::ip::tcp::socket dataSocket_;
    std::string connectionBuffer_;
    ClientPacketHandler handler;
    QObject* parent;
};




