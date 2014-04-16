#include "connection.h"
#include "reactor.h"
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

Connection::Connection() :
        sock(new Socket())
{
    readBufLen = 0;
    writeBufLen = 0;
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
}

void Connection::onClose()
{
    myReactorPtr->poller->del(sock->getFd());
    myReactorPtr->connMap.erase(sock->getFd());
    
}

void Connection::handleLogic(int len)
{
    switch(state_)
    {
        case connect:
            handleGetHeader(len);
            break;
        case reqHeader:
            handleRespond();
            break;
        case error:
            Debug << "Http Error" << endl;
        default:
            break;
            
    }
        
}

void Connection::handleGetHeader(int len)
{
    static char* ptrLast;
    if( len == readBufLen )
        ptrLast = readBuf;
    
    string tmp (ptrLast, (int)((readBuf + readBufLen) - ptrLast) );
    string::size_type pos = string::npos;

    if( (pos = tmp.find("\r\n\r\n")) != string::npos )
    {
        Debug << "found header:" << endl << string(readBuf, pos + int(ptrLast - readBuf)) << endl;
        headerEndPos = pos + (ptrLast - readBuf) + 2;

        if(request.parse(readBuf, headerEndPos) == 0)
        {
            state_ = reqHeader;
            handleLogic(0);
        }
        else
        {
            state_ = error;
        }
    }
    else
    {
        Debug << "no found header end flag" << endl;;
        ptrLast = readBuf + readBufLen - 3;
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
        string filePath = "/home/kidlet/Work/KidHttpd/www/" + request.getURI();
        int fd = open(filePath.c_str(), O_RDONLY);

        if(fd < 0)
        {
            respond.stateCode = 404;
            respond.setPhrase("not found"); 
        }
        
        
    }
    
}
