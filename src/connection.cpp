#include "connection.h"
#include "reactor.h"
#include "server.h"
#include "util.h"

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>

Connection::Connection() :
        sock(new Socket())
{
    readBufLen = 0;
    writeBufLen = 0;
    hasWriteLen = 0;
    hasFileLen = 0;
    
    state_ = close;

    
}

void Connection::setReactor(Reactor* ReactorPtr)
{
    myReactorPtr = ReactorPtr;
    state_ = connect;
}

Reactor* Connection::getReactor()
{
    return myReactorPtr;
}

void Connection::onRead()
{
    int len = sock->recv(readBuf + readBufLen, 256);
    readBufLen += len;
    Debug << "Read Len: " << len << endl;

    if(len == 0)
    {
        onClose();
        return ;
    }

    handleLogic(len);
}

void Connection::onWrite()
{
    if(hasWriteLen < writeBufLen)
    {
        Debug << "Write Header!" << endl;
        int iRet = sock->send(writeBuf + hasWriteLen, writeBufLen - hasWriteLen);
        if(iRet >= 0)
        {
            hasWriteLen += iRet;
        }
    }
    else
    {
        Debug << endl << string(writeBuf, hasFileLen) << endl;
        HttpRespond::fileInfo info;

        int iRet = respond.isGetFile(&info);
        if(iRet == 0)
        {
            iRet = sendfile(sock->getFd(), info.fd, NULL, info.fileSize);
            if(iRet >= 0)
            {
                sock->send("\r\n\r\n", 4);
                onClose();
            }
            else
            {
               
            }
        }
        else
        {
            onClose();
        }
        
        
    }

}

void Connection::onClose()
{
    //myReactorPtr->connMap.erase(sock->getFd());
    if(state_ == close)
    {
        return ;
    }
    state_ = close;
    myReactorPtr->poller->del(sock->getFd());

    HttpRespond::fileInfo info;
    int iRet = respond.isGetFile(&info);

    if(iRet == 0)
    {
        ::close(info.fd);
    }
    Debug << endl;
    
}

void Connection::handleLogic(int len = 0)
{
    switch(state_)
    {
        case connect:
            handleGetHeader(len);
            break;
        case reqHeader:
            handleRespond();
            break;
        case resWrite:
            handleWrite();
            break;
        case error:
            Debug << "Http Error" << endl;
            return ;
        case close:
            return ;
        default:
            break;
    }
}

void Connection::handleGetHeader(int len)
{
    
    string tmp (readBuf, readBufLen);
    string::size_type pos = string::npos;

    if( (pos = tmp.find("\r\n\r\n")) != string::npos )
    {
        //Debug << "found header:" << endl << string(readBuf, pos) << endl;
        headerEndPos = pos;

        if(request.parse(readBuf, headerEndPos) == 0)
        {
            state_ = reqHeader;
        }
        else
        {
            state_ = error;
        }
        handleLogic();
    }
    else
    {
        Debug << "no found header end flag" << endl;;
    }
    
}

void Connection::handleGetContent(int len)
{
    string text(readBuf + headerEndPos + 1, readBuf + readBufLen);
    string::size_type pos;

    if( (pos = text.find("\r\n\r\n")) != string::npos)
    {
        contentEndPos = pos + 2;
        state_ = reqHandle;
    }

}

void Connection::handleRespond()
{
    if(request.getMethod() == HttpRequest::GET)
    {

        Configure& conf = *Server::getInstance()->getConf();
        
        if(respond.resFile(conf.getValue("path") + request.getURI(), request) != 0)
        {
            vector<string> vecFile;
            Split(conf.getValue("default_files").c_str(), ",", vecFile);

            auto it = vecFile.begin();

            for(; it!=vecFile.end(); it++)
            {
                if(respond.resFile(conf.getValue("path") +
                                   request.getURI() + "/" + *it, request ) == 0)
                    break;

            }
            if(it == vecFile.end())
                respond.notFound();
        }
        respond.encode(writeBuf, writeBufLen);
        Debug << endl <<string(writeBuf, writeBufLen) << endl;
        state_ = resWrite;
    }
    else
    {
        respond.notImplement();

        respond.encode(writeBuf, writeBufLen);
        state_ = resWrite;
        
    }
    handleLogic();
    
}

void Connection::handleWrite()
{
    myReactorPtr->poller->ctl(sock->getFd(), EventType::RW);
   
}
