/*
 * 文件名称：connection.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 * 2014-3-2 首次编写
 *
 */
#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include "common.h"
#include <string>

const int MAX_HEAD_LEN = 2048;

class Connection
{
public:
    Socket sock;
    
    char* head[MAX_HEAD_LEN];
    char* content;
    unsigned int activeTime;

    ~Connection(){Debug<<"Connection out" << endl;}

    
};

#endif
