//
// Created by li on 2020/3/24.
//

#include "mysql/SqlConnection.h"

#include <iostream>

SqlConnection::SqlConnection(
    const std::string& host, u_int16_t port, const std::string& userName, const std::string& password,
    const std::string& database)
{
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, host.c_str(), userName.c_str(), password.c_str(), database.c_str(), port, NULL, 0))
    {
        std::cerr << "Failed to connect to database: Error: " << mysql_error(&conn) << '\n';
        exit(0);
    }
    std::cerr << "Successfully connected to Database.\n";
}

SqlConnection::~SqlConnection()
{
    mysql_close(&this->conn);
}
