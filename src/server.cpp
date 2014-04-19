/*
 * 文件名称：server.cpp
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 *  2014-3-2 首次编写
 *
 */
#include <unistd.h>
#include "server.h"

Server::Server() : configure_()
{
    status_ = INIT;
    proxy_= NULL;
}

Server::~Server()
{
    if(proxy_ != NULL)
        delete proxy_;
}

int Server::start()
{
    proxy_ = new Access(2);

    proxy_->start();

    while(status_ != STOPED)
    {
        sleep(1);
    }
    
    
    return 0;
}
