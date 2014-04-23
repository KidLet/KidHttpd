/*
 * 文件名称：util.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史:
 *	2014-4-16 首次编写
 *  2014-4-23 添加 toint, strToTime, timeToStr
 *            
 */

#ifndef __UTIL_H__
#define __UTIL_H__ 

#include "common.h"
#include <vector>
#include <sstream>

int Split(const char* str, const char* delimeter, vector<string>& vec);

string timeToStr(const time_t time);
time_t strToTime(const string& str);


template<class T>
string tostr(const T& t)
{
    stringstream ss;
    string str;
    ss << t;
    ss >> str;
    return str;
}

template<class T = string>
int toint(const T& str)
{
    stringstream ss;
    int ret;
    ss << str;
    ss >> ret;
    return ret;
}
#endif
