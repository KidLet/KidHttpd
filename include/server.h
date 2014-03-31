/*
 * 文件名称：server.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 *  2014-2-17 首次编写
 */
#ifndef __SERVER_H__
#define __SERVER_H__

#include "singleton.h"
#include "configure.h"
#include "access.h"

enum STATUS
{
    INIT,
    STARTED,
    STOPED
};


class Server : public Singleton<Server>
{
public:
    int start();
    int stop();

    Server();
    ~Server();
    
private:
    Configure configure_;
    bool status_;
    Access* proxy_;

};


#endif
