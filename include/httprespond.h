/*
 * 文件名称：httprespond.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 * 2014-4-10 首次编写
 *
 */
#ifndef __HTTPRESPOND_H__
#define __HTTPRESPOND_H__

#include "http.h"

class HttpRespond : public Http
{
public:
    struct fileInfo
    {
        int fd;
        unsigned long fileSize;
    };

    HttpRespond();

    int stateCode;
    void setPhrase(const string& text);

    void encode(char* ptr, int& len);
    string getContentType(const string& ext);

    void notFound();
    int resFile(const string& path);
    int isGetFile(fileInfo* info);


private:
    string phrase_;
    static map<string, string> mapContentType;
    static void addType();
    struct fileInfo info_;
   
    
};


#endif


