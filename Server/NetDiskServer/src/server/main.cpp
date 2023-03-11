#include <iostream>

#include "NetDiskServer.h"
#define LOG(X) std::cout << X << std::endl
int main()
{
    asio::io_context io(1);
    asio::ip::tcp::endpoint ep(asio::ip::make_address("127.0.0.1"), 45000);
    NetDiskServer hs(io, ep,"localhost", 0, "ftp", "123abc", "ftpserver");
    hs.startAccept();
    io.run();
    return 0;
}
