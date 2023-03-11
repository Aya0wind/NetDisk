#pragma once
//
// Created by li on 2020/3/25.
//

#include <cstdint>
/// Ftp命令
enum class FtpCommand : uint16_t
{
    REQUEST = 0,  // Ftp请求
    PORT,         //发送端口号
    USER,         //登录
    PASS,         //密码
    GET,          //下载文件
    PUT,          //上传文件
    RGET,         //断点下载
    RPUT,         //断点上传
    CD,           //进入指定目录
    PWD,          //当前目录
    LS,           //列出当前目录的文件
    MKDIR,        //新建指令目录
    RMDIR,        //删除指定目录

    RESPOND = 1000,  // Ftp响应
    NEEDPASS,        //用户存在，需要密码
    PASSINCORRECT,   //密码错误
    NOUSER,          //用户不存在
    LOGINOK,         //登录成功
    FILEEXIST,       //文件存在
    UNKNOWNCMD       //未知命令

};
const char* getFtpCommandName(FtpCommand cmd);


/// Ftp报文类型
enum class FtpType : uint16_t
{
    Request,  //请求
    Respond,  //响应
    Error     //错误
};
