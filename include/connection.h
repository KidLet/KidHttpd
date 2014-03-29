/*
 * 文件名称：connection.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月2日
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

    
};

#endif
