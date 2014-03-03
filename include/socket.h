/*
 * 文件名称：socket.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月23日
 *
 */
#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
using namespace std;

class Socket
{
public:
    Socket(int iType = SOCK_STREAM, int iDomain = AF_INET);
    Socket(int iFd);
    Socket();
    ~Socket();
    int connect(const string& sIp, unsigned int iPort);
    int accept(Socket& client);
    int bind(const string& sBindIp, unsigned int iPort);
    int listen(int iBackLog);
    int recv(void* pvBuf, size_t iLen);
    int send(void* pvBuf, size_t iLen);
    int getFd();
    int close();
    int shutdown();
    int create(int iType = SOCK_STREAM, int iDomain = AF_INET);
    void setOwner(bool isOwner = true);
    static int parseAddr(const string& sAddr, struct in_addr& stInAddr);
    
private:
    int iFd_;
    bool bIsOwner_;
    int iDomain_;
    int iType_;
    
};

#endif
