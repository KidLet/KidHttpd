/*
 * 文件名称：server.cpp
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月2日
 *
 */
#include <unistd.h>
#include "server.h"

Server::Server() : _configure("./www", 8000)
{
    _status = INIT;
    _accessor = NULL;
}

Server::~Server()
{
    if(_accessor != NULL)
        delete _accessor;
}

int Server::start()
{
    _accessor = new Access(&_configure);

    while(_status != STOPED)
    {
        sleep(1);
    }
    
    
    
    _status = STARTED;
    return 0;
}
