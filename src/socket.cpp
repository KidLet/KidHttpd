/*
 * 文件名称：socket.cpp
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月24日
 *
 */
#include "socket.h"
#include <arpa/inet.h>  // for inet_aton
#include <netinet/in.h> // for sockaddr_in
#include <cstring>      // for bzero

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

    iFd_ = socket(iType, iDomain, 0);
    iDomain = iDomain_;

    if(iFd_ >=0)
    {
        bIsOwner_ = true;
    }
}

Socket::~Socket()
{
    if(bIsOwner_ == true && iFd_ >= 0)
    {
        ::close(iFd_);
        iFd_ = -1;
    }
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

int Socket::create(int iType = SOCK_STREAM, int iDomain = AF_INET)
{
    if(iFd_ != -1)
    {
        Socket::close();
    }

    iFd_ = socket(iType, iDomain, 0);
    iDomain = iDomain_;

    if(iFd_ >=0)
    {
        bIsOwner_ = true;
    }
    
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

int Socket::accept(Socket& client)
{
    struct sockaddr_in stSockAddrIn;
    socklen_t iSockLen;

    int iRet = ::accept(iFd_, (struct sockaddr*) &stSockAddrIn, &iSockLen);
    if(iRet >= 0)
    {
        client.init(iRet, true, iDomain_);
    }
    else
    {
        return -1;
    }
    
    return 0;
}

int Socket::bind(const string& sBindIp, unsigned int iPort)
{
    struct sockaddr_in stSockAddrIn;

    bzero(&stSockAddrIn, sizeof(stSockAddrIn));
    parseAddr(sBindIp, stSockAddrIn.sin_addr);
    stSockAddrIn.sin_family = iDomain_;
    stSockAddrIn.sin_port = htons(iPort);
    
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
