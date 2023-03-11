//
// Created by li on 2020/3/25.
//

#include "NetDiskServer.h"

#include <asio/write.hpp>
#include <iostream>

#include "FtpConnection/FtpConnection.h"
#include "FtpConnection/FtpPacket.h"
void NetDiskServer::startAccept()
{
    auto connection = std::make_shared<FtpConnection>(io_,this->sqlConnection);
    acceptor_.async_accept(connection->commandSocket(), [connection, this](const asio::error_code& err) {
        if (err)
        {
            std::cout << "accept err:" << err.message() << "\n";
            return;
        }
        std::cout << "accept new client!" << std::endl;
        establishFtpConnection(connection);
        this->startAccept();
    });
}
void NetDiskServer::establishFtpConnection(FtpConnectionPtr connection)
{
    uint16_t port = 1024 + rand() % 40000;
    connection->sendFtpRespond(FtpCommand::PORT, std::to_string(port));

    auto remote_endpoint = connection->commandSocket().remote_endpoint();
    auto clientPoint = asio::ip::tcp::endpoint(remote_endpoint.address(), port);
    auto acceptor = std::make_shared<asio::ip::tcp::acceptor>(io_, clientPoint);

    std::cout << "create new data connect which is:" << serverPoint.address().to_string() << ' ' << serverPoint.port()
              << std::endl;
    auto overTimeTimer= std::make_shared<asio::steady_timer>(io_,std::chrono::seconds(5));
    overTimeTimer->async_wait([acceptor,overTimeTimer](const asio::error_code& err){
        acceptor->close();
    });
    acceptor->async_accept(connection->dataSocket(), [connection, acceptor,overTimeTimer](const asio::error_code& err) {
        if (err)
        {
            std::cout << "ftp connection error!,over time or " << err.message() << "\n";
            return;
        }
        overTimeTimer->cancel();
        std::cout << "ftp connection established!" << std::endl;
        connection->readNextFtpPacket();
    });
}
