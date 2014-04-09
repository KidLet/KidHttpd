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


