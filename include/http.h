/*
 * 文件名称：http.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 * 2014-4-10 首次编写
 *
 */
#ifndef __HTTP_H__
#define __HTTP_H__

#include "common.h"
#include <vector>
#include <map>


class Http
{
public:
    enum Version
    {
        Http10,
        Http11,
        HttpUnknow
    };

    Version version;
    vector<char> content;
    string getHeader(const string& key);
    int setHeader(const string& key, const string& value);

private:
    map<string, string> mapHeader;
};


#endif
