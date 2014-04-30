#include "connection.h"
#include "reactor.h"
#include "server.h"
#include "util.h"
#include "lock.h"

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>

Mutex mutexExit;

Connection::Connection() :
        sock(new Socket())
{
    readBufLen = 0;
    writeBufLen = 0;
    hasWriteLen = 0;
    hasFileLen = 0;
    hasTailLen = 0;
    
    state_ = close;


}

void Connection::setReactor(Reactor* ReactorPtr)
{
    myReactorPtr = ReactorPtr;
    state_ = connect;

    Task* task = new Task();
    *task = std::bind(&Connection::handleLogic, this);
    Server::getInstance()->getPool()->add( task );
}

Reactor* Connection::getReactor()
{
    return myReactorPtr;
}

void Connection::onRead()
{
    if(state_ == close)
        return ;

    int len = sock->recv(readBuf + readBufLen, 65536 - readBufLen);
    readBufLen += len;
    Debug << "Read Len: " << len << endl;

    if(len == 0)
    {
        onClose();
        return ;
    }

    if(len > 0 && state_ != close)
    {
        cond_.signal();
    }
}

void Connection::onWrite()
{
    if(state_ == close)
        return ;

    const char *ptr = "\r\n\r\n";

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
        Debug << "Write Content!" << endl;
        //Debug << endl << string(writeBuf, hasFileLen) << endl;
        HttpRespond::fileInfo info;

        int iRet = respond.isGetFile(&info);
        if(iRet == 0)
        {

            if(hasFileLen)//文件发送完毕后追加结尾\r\n\r\n
            {
                Debug << "Write Content Tail!" << endl;
                iRet = sock->send(ptr + hasTailLen, 4 - hasTailLen);
                if(iRet > 0)
                {
                    hasTailLen += iRet;
                }

                if(hasTailLen == 4)
                    onClose();

                return ;
                
            }
            
            errno = 0;
            iRet = sendfile(sock->getFd(), info.fd, NULL, info.fileSize);


            if(errno == EAGAIN)
                Debug << "EAGAIN" << endl;
            else if(errno == EBADF)
                Debug << "EBADF" << endl;
            else if(errno == EFAULT)
                Debug << "EFAULT" << endl;
            else if(errno == EINVAL )
                Debug << "EINVAL" << endl;
            else if(errno == EIO)
                Debug << "EIO" << endl;
            
            if(iRet >= 0)//文件数据发送完毕
            {

                assert(info.fileSize ==(unsigned int) iRet);
                
                hasFileLen = info.fileSize;
                ::close(info.fd);
                
            }
            else
            {
                Debug << "sendfile SockFD: " << sock->getFd() << " file fd:" << info.fd << endl;
               
            }
        }
        else
        {
            //myReactorPtr->poller->ctl(sock->getFd(), EventType::R);
            onClose();
        }
        
        
    }

}

void Connection::onClose()
{
    if(state_ == close)
    {
        return ;
    }
    cond_.signal();
    state_ = close;

    Debug << sock->getFd() << endl;
    
}

Connection::~Connection()
{
    Debug<<"Connection out , FD:" << sock->getFd() << endl;
    assert(state_ == close);
    cond_.signal();
    mutexExit.lock();
    mutexExit.unlock();
}

void Connection::handleLogic()
{
    Debug << "Have Lock:" << pthread_self() <<  endl;
    LockT<Mutex> lock(mutexExit);

    while(1)
    {

        switch(state_)
        {
            case connect:
                if(handleGetHeader())
                    break;
                else
                {
                    mutex_.lock();
                    cond_.wait(mutex_);
                    mutex_.unlock();
                }
                break;
                
            case reqHeader:
                handleRespond();
                break;

            case resWrite:
                handleWrite();
                return ;

            case error:
                Debug << "Http Error" << endl;
                return ;
            case close:
                return ;
            default:
                return ;
        }
        
    }

    
}

bool Connection::handleGetHeader()
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

        return true;
        //handleLogic();
    }
    else
    {
        Debug << "no found header end flag| read len:" << readBufLen << "|FD:" << sock->getFd() << endl;;
        return false;
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
        Debug << "FD: " << sock->getFd() << endl;
        state_ = resWrite;
    }
    else
    {
        respond.notImplement();

        respond.encode(writeBuf, writeBufLen);
        state_ = resWrite;
        
    }
    
}

void Connection::handleWrite()
{
    myReactorPtr->poller->ctl(sock->getFd(), EventType::W);
   
}
