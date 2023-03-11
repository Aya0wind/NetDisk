#pragma once
//
// Created by li on 2020/3/24.
//
#include <mysql/mysql.h>

#include <string>
#include <vector>

#include "SqlField.h"

class SqlConnection
{
    MYSQL conn;

public:
    /*
     * 构造SqlConnection
     * @param host 数据库IP
     * @param port 数据库端口
     * @param userName 用户名
     * @param password 密码
     * @param database 数据库名
    */
    SqlConnection(
        const std::string& host, u_int16_t port, const std::string& userName, const std::string& password,
        const std::string& database);
    /*
     * 执行sql select查询
     * @param tableName 表名
     * @param where 条件，如 name='abc'
     * @return 查询结果
     * @generic FieldType 字段类型
     */
    template <typename FieldType>
    std::vector<FieldType> execSqlSelect(const std::string& tableName, const std::string& where)
    {
        std::string sqlQuery = "SELECT ";
        auto field = FieldType::getFields();
        for (auto e : field)
        {
            sqlQuery.append(e);
            sqlQuery.push_back(',');
        }
        sqlQuery.pop_back();
        sqlQuery += " FROM ";
        sqlQuery += tableName;
        if (!where.empty())
        {
            sqlQuery += " WHERE ";
            sqlQuery += where;
        }
        int status = mysql_query(&this->conn, sqlQuery.c_str());
        std::vector<FieldType> fields;
        if (status)
            return fields;
        MYSQL_ROW row;
        MYSQL_RES* res_set = mysql_store_result(&conn);
        int count = mysql_num_rows(res_set);
        if (count)
        {
            while ((row = mysql_fetch_row(res_set)) != NULL)
            {
                std::vector<std::string> res;
                for (int i = 0; i < mysql_num_fields(res_set); i++)
                {
                    res.emplace_back(row[ i ] != NULL ? row[ i ] : "NULL");
                }
                FieldType field = FieldType::deserilizeFromSqlQuery(res);
                fields.emplace_back(field);
            }
        }
        return fields;
    }

    /*
    * 执行sql insert插入
    * @param datas 插入的数据集合
    * @param tableName 表名
    * @param where 条件，如 name='abc'
    * @return 插入是否成功
    * @generic FieldType 字段类型
    */
    template <typename FieldType>
    bool execSqlInsert(const std::vector<FieldType> datas, const std::string& tableName, const std::string& where)
    {
        std::string sqlQuery = "INSERT INTO ";
        sqlQuery += tableName;
        sqlQuery += '(';
        auto field = FieldType::getFields();
        for (auto e : field)
        {
            sqlQuery += e;
            sqlQuery.push_back(',');
        }
        sqlQuery.pop_back();
        sqlQuery += ") VALUES";
        for (auto e : datas)
        {
            sqlQuery += '(';
            sqlQuery += e.serilizeValue();
            sqlQuery += ')';
            sqlQuery += ',';
        }
        sqlQuery.pop_back();
        if (!where.empty())
        {
            sqlQuery += " WHERE ";
            sqlQuery += where;
        }
        int status = mysql_query(&this->conn, sqlQuery.c_str());
        return !status;
    }
    ~SqlConnection();
};
