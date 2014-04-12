/*
 * 文件名称：httprequest.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 * 2014-4-12 首次编写
 *
 */
#ifndef __HTTPREQUEST_H__
#define __HTTPREQUEST_H__

#include "http.h"

class HttpRequest : public Http
{
public:
    enum Method
    { GET, POST, UNKNOW };

    Method getMethod();
    void setMethod(Method m); 

private:
    Method method_;
    string path_;
    string queryString_;
    
};


#endif

