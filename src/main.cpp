/*
 * 文件名称：main.cpp
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 *  2014-2-17 首次编写
 */

#include <cstdio>
#include "server.h"

int main()
{
    Server::getInstance()->start();
    return 0;
}


