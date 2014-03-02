/*
 * 文件名称：access.cpp
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月2日
 *
 */
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "access.h"


Access::Access(Conf* configure)
{
    struct sockaddr_in servaddr;
    int opt = 1;

    _listen = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(configure->getPort());
    

    bind(_listen, (struct sockaddr*)&servaddr, sizeof(servaddr));

    listen(_listen, 100);
}
