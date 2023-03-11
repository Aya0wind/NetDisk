//
// Created by li on 2020/3/26.
//

#include "mysql/SqlService.h"

#include "mysql/UserInfo/UserInfo.h"
std::pair<UserInfo, bool> SqlService::queryUserInfo(const std::string& name)
{
    std::string where = "name='";
    where += name;
    where += '\'';
    auto queryResult = connection.execSqlSelect<UserInfo>("user", where);
    if (queryResult.empty())
        return std::make_pair(UserInfo(), false);
    else
        return std::make_pair(queryResult[ 0 ], true);
}
std::pair<UserInfo, bool> SqlService::queryUserAuthority(const std::string& name)
{
    return std::make_pair(UserInfo(), false);
}
