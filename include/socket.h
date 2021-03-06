/*
 * 文件名称：socket.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史:
 *	2014-3-23 首次编写
 *	2014-3-30 添加reuse接口
 *  2014-4-6  添加新的构造函数,设置阻塞、非阻塞接口
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
    Socket(int iType, int iDomain);
    Socket(int fd);
    Socket();
    ~Socket();
    void init(int iFd, bool bIsOwner = true, int iDomain = AF_INET);
    int create(int iType = SOCK_STREAM, int iDomain = AF_INET);
    int setReUse(bool isReUse = true);

    int connect(const string& sIp, unsigned int iPort);
    int accept(Socket& client, bool isBlock = 1);
    int bind(const string& sBindIp, unsigned int iPort);
    int listen(int iBackLog = 1024);

    int recv(const void* pvBuf, size_t iLen);
    int send(const void* pvBuf, size_t iLen);

    static int parseAddr(const string& sAddr, struct in_addr& stInAddr);
    
    int getFd();
    void setOwner(bool isOwner = true);
    int setBlock(bool isBlock);

    int close();
    int shutdown(int iHow = SHUT_RDWR);
    
private:
    int iFd_;
    bool bIsOwner_;
    int iDomain_;
    
};

#endif
