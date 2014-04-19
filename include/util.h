/*
 * 文件名称：util.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史:
 *	2014-4-16 首次编写
 */

#ifndef __UTIL_H__
#define __UTIL_H__ 

#include "common.h"
#include <vector>
#include <sstream>

int Split(const char* str, const char* delimeter, vector<string>& vec);

template<class T>
string tostr(const T& t)
{
    stringstream ss;
    string str;
    ss << t;
    ss >> str;
    return str;
}
#endif
