//
// Created by li on 2020/3/24.
//

#include "mysql/UserInfo/UserInfo.h"

#include <iostream>
std::ostream& operator<<(std::ostream& os, const UserInfo& info)
{
    os << '[' << info.id << ',' << info.name << ',' << info.pwd << ',' << info.maindir << ']';
    return os;
}
UserInfo UserInfo::deserilizeFromSqlQuery(const std::vector<std::string> res)
{
    return UserInfo{
        res[ 0 ],
        res[ 1 ],
        res[ 2 ],
        res[ 3 ],
    };
}
std::vector<const char*> UserInfo::getFields()
{
    return std::vector<const char*>{
        STRINGNIFY(id),
        STRINGNIFY(name),
        STRINGNIFY(pwd),
        STRINGNIFY(maindir),
    };
}
std::string UserInfo::serilizeValue()
{
    std::string res;
    ADD_MARK(res, id);
    res += ',';
    ADD_MARK(res, name);
    res += ',';
    ADD_MARK(res, pwd);
    res += ',';
    ADD_MARK(res, maindir);
    return res;
}
