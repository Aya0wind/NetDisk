cmake_minimum_required(VERSION 3.15)
project(NetDiskServer)
set(CMAKE_CXX_STANDARD 14)

set(asio_DIR ${CMAKE_CURRENT_SOURCE_DIR}/asiolib/share/asio)
find_package(asio CONFIG REQUIRED)


set(SERVER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/server)
set(SQL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/mysql)
set(FTPCON_DIR ${SERVER_DIR}/FtpConnection)
set(REQU_HANDLER_DIR ${SERVER_DIR}/RequestHandler)
set(FILE_STREAM__DIR ${SERVER_DIR}/Filestream)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/server)


file(GLOB SERVER_SRC
        ${SERVER_DIR}/main.cpp
        ${SERVER_DIR}/NetDiskServer.cpp
        )

file(GLOB FTPCON_SRC
        ${FTPCON_DIR}/FtpConnection.cpp
        ${FTPCON_DIR}/FtpPacket.cpp
        )

file(GLOB SQL_SRC
        ${SQL_DIR}/SqlConnection.cpp
        ${SQL_DIR}/UserInfo.cpp
        ${SQL_DIR}/SqlService.cpp
        )

file(GLOB REQU_HANDLER_SRC
        ${REQU_HANDLER_DIR}/FtpPacketHandler.cpp
        ${REQU_HANDLER_DIR}/StateMachine.cpp
        )

file(GLOB FILE_STREAM_SRC
        ${FILE_STREAM__DIR}/FileStream.cpp
        )

file(GLOB TEST_SRC
        ${SERVER_SRC}
        ${FTPCON_SRC}
        ${REQU_HANDLER_SRC}
        ${SQL_SRC}
        #${FILE_STREAM_SRC}
        )


link_libraries("/usr/local/Cellar/mysql/8.0.19/lib/libmysqlclient.dylib"
        "/usr/local/opt/openssl/lib/libcrypto.dylib"
        "/usr/local/opt/openssl/lib/libssl.dylib"
        )

add_executable(Server ${SERVER_SRC} ${SQL_SRC} src/server/Logger/Logger.cpp src/server/Logger/Logger.h)
add_executable(Test ${TEST_SRC})
target_link_libraries(Server PUBLIC asio::asio)
target_link_libraries(Test PUBLIC asio::asio)