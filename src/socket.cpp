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
}

Socket::Socket(int iType, int iDomain)
{
    iFd_ = -1;
    bIsOwner_ = false;

    iFd_ = socket(iType, iDomain, 0);

    if(iFd_ >=0)
    {
        bIsOwner_ = true;
    }
}

Socket::Socket(int iFd)
{
    if(iFd >= 0)
    {
        iFd_ = iFd;
        bIsOwner_ = false;
    }
}

Socket::~Socket()
{
    if(bIsOwner_ == true && iFd_ >= 0)
    {
        ::close(iFd_);
    }
}

void Socket::setOwner(bool bIsOwner)
{
    if(iFd_ >= 0)
    {
        bIsOwner_ = bIsOwner;
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
    return 0;
}
