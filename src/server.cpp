/*
 * 文件名称：server.cpp
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 *  2014-3-2 首次编写
 *
 */
#include "server.h"
#include "util.h"

Server::Server() : configure_()
{
    status_ = INIT;
    proxy_= NULL;
    configure_.parseFile("conf/http.conf");
}

Server::~Server()
{
    if(proxy_ != NULL)
        delete proxy_;
}

int Server::start()
{
    int reactors_num = 2;
    int worker_num = 10;

    if(toint(configure_.getValue("reactors_num")) > 1)
    {
        reactors_num = 1 + toint(configure_.getValue("reactors_num"));
    }

    if(toint(configure_.getValue("worker_num")) > 0)
    {
        worker_num = toint(configure_.getValue("worker_num"));
    }
    
    proxy_ = new Access(reactors_num);
    pool_ = new ThreadPool();
    pool_->init(worker_num);
    

    proxy_->start();
    pool_->start();

    while(status_ != STOPED)
    {
        sleep(1);
    }
    
    
    return 0;
}
