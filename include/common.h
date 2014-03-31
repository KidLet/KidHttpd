/*
 * 文件名称：common.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史:
 *	2014-2-17 首次编写
 *	2014-3-30 添加 Debug 宏，便于调试输出
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <cassert>
#include <unistd.h>
using namespace std;


#ifndef NULL
#define NULL 0
#endif

#define Debug cout << "File:" << __FILE__ << " Line:" << __LINE__ << " Fun:" << __FUNCTION__ << " | "

#endif
