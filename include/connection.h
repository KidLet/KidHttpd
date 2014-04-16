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
#include "httprequest.h"
#include <string>
#include <vector>

class Reactor;

class Connection
{
public:
    Connection();
    void setReactor(Reactor* ReactorPtr);
    Reactor* getReactor();

    HttpRequest request;
    HttpRespond respond;
    


    ~Connection(){Debug<<"Connection out" << endl;}
    unique_ptr<Socket> sock;

private:
    friend class Reactor;
    Reactor* myReactorPtr;


    char readBuf[65536];
    int readBufLen;
    
    char writeBuf[65536];
    int writeBufLen;

    void onRead();
    void onClose();
    
    void handleLogic(int len);
    void handleGetHeader(int len);
    void handleGetContent(int len);
    void handleRespond();

    enum State
    {
        close,
        connect,
        reqHeader, //header载入完毕
        reqContent,//content载入完毕
        reqHandle,
        resWrite,
        error
    };

    State state_;
    size_t headerEndPos;
    size_t contentEndPos;


    
    
};

#endif
