/*
 * 文件名称：connection.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 * 2014-3-2 首次编写
 *
 */
#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include "common.h"
#include "socket.h"
#include <string>
#include <vector>

class Reactor;

class Connection
{
public:
    Connection();
    void setReactor(Reactor* ReactorPtr);
    Reactor* getReactor();
    

    ~Connection(){Debug<<"Connection out" << endl;}
    unique_ptr<Socket> sock;

private:
    friend class Reactor;
    Reactor* myReactorPtr;
    //vector<char> readBuf;
    char readBuf[65536];
    int readBufLen;
    
    char writeBuf[65536];
    int writeBufLen;
    //vector<char> writeBuf;
    void onRead();

    
    
};

#endif
