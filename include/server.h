/*
 * 文件名称：server.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年2月17日
 *
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
    Conf configure_;
    bool status_;
    Access* proxy_;

};


#endif
