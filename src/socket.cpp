/*
 * 文件名称：socket.cpp
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 *  2013-3-24 首次编写
 */
#include "common.h"
#include "socket.h"
#include <arpa/inet.h>  // for inet_aton
#include <netinet/in.h> // for sockaddr_in
#include <cstring>      // for bzero
#include <fcntl.h>      // for fcntl

Socket::Socket()
{
    bIsOwner_ = false;
    iFd_ = -1;
    iDomain_ = AF_INET;
}

Socket::Socket(int iType, int iDomain)
{
    iFd_ = -1;
    bIsOwner_ = false;

    iFd_ = socket(iDomain, iType, 0);
    iDomain_ = iDomain;

    if(iFd_ >=0)
    {
        bIsOwner_ = true;
    }
}

Socket::Socket(int fd)
{
    Socket::init(fd, true, AF_INET);
}

Socket::~Socket()
{
    if(bIsOwner_ == true && iFd_ >= 0)
    {
        ::close(iFd_);
        Debug << "Socket: " << iFd_ << " Delete" << endl;
        iFd_ = -1;
    }
}

int Socket::setReUse(bool bIsReUse)
{
    int opt = 1;
    return setsockopt(iFd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
}

void Socket::setOwner(bool bIsOwner)
{
    if(iFd_ >= 0)
    {
        bIsOwner_ = bIsOwner;
    }
}

void Socket::init(int iFd, bool bIsOwner, int iDomain)
{
    if(iFd_ != -1)
    {
        Socket::close();
    }

    iFd_ = iFd;
    bIsOwner_ = bIsOwner;
    iDomain_ = iDomain;
}

int Socket::create(int iType, int iDomain)
{
    if(iFd_ != -1)
    {
        Socket::close();
    }

    iFd_ = socket(iDomain, iType, 0);
    iDomain_ = iDomain;

    if(iFd_ >=0)
    {
        bIsOwner_ = true;
    }
    return iFd_;
    
}


int Socket::parseAddr(const string& sAddr, struct in_addr& stInAddr)
{
    int iRet = inet_aton(sAddr.c_str(), &stInAddr);
    return iRet;
}

int Socket::connect(const string& sIp, unsigned int iPort)
{
    struct sockaddr_in stSockAddrIn;
    
    parseAddr(sIp, stSockAddrIn.sin_addr);
    bzero(&stSockAddrIn, sizeof(stSockAddrIn));

    stSockAddrIn.sin_family = AF_INET;
    stSockAddrIn.sin_port = (in_port_t) iPort;
    
    int iRet = ::connect(iFd_, (sockaddr*) &stSockAddrIn, sizeof(stSockAddrIn));

    return iRet;
    
}

int Socket::accept(Socket& client, bool isBlock)
{
    struct sockaddr_in stSockAddrIn;
    socklen_t iSockLen;
    int iRet;

    if(isBlock)
        iRet = ::accept4(iFd_, (struct sockaddr*) &stSockAddrIn, &iSockLen, 0);
    else 
        iRet = ::accept4(iFd_, (struct sockaddr*) &stSockAddrIn, &iSockLen, SOCK_NONBLOCK);

    Debug << "Socket::accept fd:" << iFd_ << endl;
    if(iRet >= 0)
    {
        client.init(iRet, true, iDomain_);
    }
    else
    {
        return iRet;
    }
    
    return 0;
}

int Socket::bind(const string& sBindIp, unsigned int iPort)
{
    struct sockaddr_in stSockAddrIn;

    bzero(&stSockAddrIn, sizeof(stSockAddrIn));
    parseAddr(sBindIp, stSockAddrIn.sin_addr);

    stSockAddrIn.sin_family = iDomain_;
    stSockAddrIn.sin_port = htons( (uint16_t)iPort);

    
    int iRet = ::bind(iFd_, (struct sockaddr*) &stSockAddrIn, sizeof(stSockAddrIn));
    return iRet;
}


int Socket::listen(int iBackLog)
{
    int iRet = ::listen(iFd_, iBackLog);
    return iRet;
}

int Socket::getFd()
{
    return iFd_;
}


int Socket::close()
{
    if(iFd_ != -1)
    {
        int iRet = ::close(iFd_);
        if(iRet == 0)
        {
            iFd_ = -1;
            iDomain_ = AF_INET;
            bIsOwner_ = false;
        }
        return iRet;
    }
    else
        return 0;
}

int Socket::shutdown(int iHow)
{
    return ::shutdown(iFd_, iHow);
}

int Socket::send(const void* pvBuf, size_t iLen)
{
    return ::write(iFd_, (void*) pvBuf, iLen);
}

int Socket::recv(const void* pvBuf, size_t iLen)
{
    return ::read(iFd_, (void*)pvBuf, iLen);
}

int Socket::setBlock(bool isBlock)
{
    int val = 0;
    if( (val = fcntl(iFd_, F_GETFL, 0)) == -1 )
        return -1;

    if(isBlock)
    {
        val = val & (~O_NONBLOCK);
    }
    else
    {
        val = val | O_NONBLOCK;
    }

    return fcntl(iFd_, F_SETFL, val);
    
}
