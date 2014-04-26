#include "httprequest.h"
#include "util.h"
#include <regex.h>

HttpRequest::Method HttpRequest::getMethod()
{
    return method_;
}

void HttpRequest::setMethod(Method m)
{
    method_ = m;
}

int HttpRequest::parse(char* ptr, size_t len)
{
    vector<string> vecHeader;
    vector<string> vecStr; //存放分割字符的临时变量

    Split(ptr, "\r\n", vecHeader);

    for(size_t i=0; i<vecHeader.size(); i++)
    {
        if(i == 0) //请求行
        {
            Split(vecHeader[i].c_str(), " ", vecStr);
            if(vecStr.size() != 3)
            {
                return -1;
            }

            if(vecStr[0].compare("GET") == 0)
                method_ = GET;
            else if(vecStr[0].compare("POST") == 0)
                method_ = POST;
            else
                method_ = UNKNOW;

            uri_ = vecStr[1];

            if(vecStr[2].substr(0, 5).compare("HTTP/") == 0 )
            {
                if(vecStr[2].substr(5).compare("1.1") == 0)
                {
                    version = Http11;
                }
                else if(vecStr[2].substr(5).compare("1.0") == 0)
                {
                    version = Http10;
                }
                else
                    version = HttpUnknow;
            }
            else
            {
                return -1;
            }

            //Debug << "Method:" << method_ << " uri: " << uri_ << " version: " << version << endl;
            
        }
        else
        {
            Split(vecHeader[i].c_str(), ": ", vecStr);
            if(vecStr.size() != 2)
                return -1;
            
            setHeader(vecStr[0], vecStr[1]);
            //Debug << "key:" << vecStr[0] << " value:" << vecStr[1] << endl;
        }
    }

    return 0;
    
}


string HttpRequest::getURI()
{
    return uri_;
}
