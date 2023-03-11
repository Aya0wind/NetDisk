#pragma once
//
// Created by li on 2020/3/24.
//
#include <string>
#include <vector>

#include "mysql/SqlField.h"
#define ADD_MARK(STR, FIELD) \
    res += '\'';             \
    res += FIELD;            \
    res += '\''

struct UserInfo
{
    std::string id;
    std::string name;
    std::string pwd;
    std::string maindir;
    static UserInfo deserilizeFromSqlQuery(const std::vector<std::string> res);
    static std::vector<const char*> getFields();
    std::string serilizeValue();
    friend std::ostream& operator<<(std::ostream& os, const UserInfo& info);
};
