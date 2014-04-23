/*
 * 文件名称：connection.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 * 2014-3-2 首次编写
 * 2014-4-23 添加多文档支持
 */
#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include "common.h"
#include "socket.h"
#include "httprequest.h"
#include "httprespond.h"
#include <string>
#include <vector>

class Reactor;

class Connection
{
public:
    Connection();
    ~Connection(){Debug<<"Connection out" << endl;}
    
    void setReactor(Reactor* ReactorPtr);
    Reactor* getReactor();
    int getStatus(){return state_;}

    HttpRequest request;
    HttpRespond respond;
    
    unique_ptr<Socket> sock;

private:
    friend class Reactor;
    Reactor* myReactorPtr;


    char readBuf[65536];
    int readBufLen;
    
    char writeBuf[65536];
    int writeBufLen;
    int hasWriteLen;
    ssize_t hasFileLen;

    void onRead();
    void onWrite();
    void onClose();
    
    void handleLogic(int len);
    void handleGetHeader(int len);
    void handleGetContent(int len);
    void handleRespond();
    void handleWrite();

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
