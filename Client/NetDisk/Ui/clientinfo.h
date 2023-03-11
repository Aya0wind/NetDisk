#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include<QString>

struct Authority
{

};

class ClientInfo
{
   QString userName;
   QString passWord;
   Authority authority;
public:
   ClientInfo(){}
};

#endif // CLIENTINFO_H
