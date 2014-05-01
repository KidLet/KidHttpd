/*
 * 文件名称：httprespond.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 * 2014-4-10 首次编写
 * 2014-4-23 添加 Modify 支持
 */
#ifndef __HTTPRESPOND_H__
#define __HTTPRESPOND_H__

#include "http.h"
#include "httprequest.h"

class HttpRespond : public Http
{
public:
    struct fileInfo
    {
        int fd;
        unsigned long fileSize;
    };

    HttpRespond();
    ~HttpRespond();

    int stateCode;
    void setPhrase(const string& text);

    void encode(char* ptr, int& len);
    string getContentType(const string& ext);

    void notFound();
    void notImplement();
    void serverError();
    void notModified();
    void buildBase(time_t lastModify = -1);

    int resFile(const string& path, HttpRequest& myReq);
    int isGetFile(fileInfo* info);


private:
    string phrase_;
    static map<string, string> mapContentType;
    static void addType();
    struct fileInfo info_;
   
    
};


#endif


