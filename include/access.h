/*
 * 文件名称：access.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月2日
 *
 */
#ifndef __ACCESS_H__
#define __ACCESS_H__

#include "common.h"
#include "configure.h"

class Access
{
public:
    Access(Conf* configure);
private:
    int _listen;
};


#endif
