#include "connection.h"
#include "reactor.h"
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

    if(len == 0)
    {
        onClose();
        return ;
    }

    handleLogic(len);
    Debug << endl;
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
    myReactorPtr->poller->del(sock->getFd());
    myReactorPtr->connMap.erase(sock->getFd());

    //HttpRespond::fileInfo info;
    respond.isGetFile(NULL);

    /*if(iRet == 0)
    {
        ::close(info.fd);
        }*/
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
        Debug << "found header:" << endl << string(readBuf, pos) << endl;
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
        if(respond.resFile("/home/kidlet/Work/KidHttpd/www/" + request.getURI()) != 0)
        {
            respond.notFound();
        }
        respond.encode(writeBuf, writeBufLen);
        Debug << endl <<string(writeBuf, writeBufLen) << endl;
        state_ = resWrite;
    }
    else
    {
        respond.stateCode = 502;
        respond.setPhrase("Not Implement");
        respond.version = Http::Version::Http11;
        respond.setHeader("connection:", "close");
        respond.setHeader("Content-Type", "text/html");
        respond.content.clear();

        respond.encode(writeBuf, writeBufLen);
        state_ = resWrite;
        
    }
    handleLogic();
    
}

void Connection::handleWrite()
{
    myReactorPtr->poller->ctl(sock->getFd(), EventType::RW);
   
}
