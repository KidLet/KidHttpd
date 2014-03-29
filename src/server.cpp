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

Server::Server() : configure_("./www", 8000)
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
    proxy_ = new Access();

    proxy_->start();

    while(status_ != STOPED)
    {
        sleep(1);
    }
    
    
    return 0;
}
