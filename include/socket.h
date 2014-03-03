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
    Socket();
    ~Socket();
    void init(int iFd, bool bIsOwner = true, int iDomain = AF_INET);
    int create(int iType = SOCK_STREAM, int iDomain = AF_INET);

    int connect(const string& sIp, unsigned int iPort);
    int accept(Socket& client);
    int bind(const string& sBindIp, unsigned int iPort);
    int listen(int iBackLog = 1024);

    int recv(void* pvBuf, size_t iLen);
    int send(void* pvBuf, size_t iLen);

    static int parseAddr(const string& sAddr, struct in_addr& stInAddr);
    
    int getFd();
    void setOwner(bool isOwner = true);

    int close();
    int shutdown(int iHow = SHUT_RDWR);
    
private:
    int iFd_;
    bool bIsOwner_;
    int iDomain_;
    
};

#endif
