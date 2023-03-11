#pragma once
//
// Created by li on 2020/3/26.
//
#include "mysql/SqlConnection.h"
#include "mysql/UserInfo/UserInfo.h"

class SqlService
{
    SqlConnection& connection;

public:
    explicit SqlService(SqlConnection& connection)
        : connection(connection)
    {
    }
    /*
   * 查询用户信息
   * @param name 用户名
   * @return pair第一个元素表示用户信息，第二个元素表示用户是否存在
   * @type UserInfo 用户信息类型
   */
    std::pair<UserInfo, bool> queryUserInfo(const std::string& name);
    /*
   * 查询用户权限
   * @param name 用户名
   * @return pair第一个元素表示用户信息，第二个元素表示用户是否存在
   * @type UserInfo 用户信息类型
   */
    std::pair<UserInfo, bool> queryUserAuthority(const std::string& name);
};
