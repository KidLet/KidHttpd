#include "httprespond.h"
#include "util.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctime>


map<string, string> HttpRespond::mapContentType;

HttpRespond::HttpRespond()
{
    if(HttpRespond::mapContentType.size() == 0)
    {
        addType();
    }
    info_.fd = -1;
}

HttpRespond::~HttpRespond()
{
    if(info_.fd != -1)
    {
        ::close(info_.fd);
        info_.fd = -1;
    }
}


void HttpRespond::setPhrase(const string& text)
{
    phrase_ = text;
    return ;
}

void HttpRespond::notFound()
{
    buildBase();
    
    stateCode = 404;
    setPhrase("not found");
    setHeader("Content-Type", "text/html");

    string text = "<html><body>not found</body></html>";
    content.clear();
    content.assign(text.begin(), text.end());
    setHeader("Content-Length", tostr<size_t>(content.size()) );

    info_.fd = -1;

}

void HttpRespond::notImplement()
{
    buildBase();
    
    stateCode = 501;
    setPhrase("not Implement");
    setHeader("Content-Type", "text/html");

    string text = "<html><body>not Implement</body></html>";
    content.clear();
    content.assign(text.begin(), text.end());
    setHeader("Content-Length", tostr<size_t>(content.size()) );

    info_.fd = -1;
    
}

// 生成基本的回包头格式
void HttpRespond::buildBase(time_t lastModify)
{
    time_t now = time(NULL);

    if(lastModify != -1)
    {
        setHeader("Last-Modified", timeToStr(lastModify));
    }
    
    version = Http11;
    setHeader("connection", "close");
    setHeader("Server", "KidHttpd/0.1");
    setHeader("Date", timeToStr(now));
    content.clear();
    
}

void HttpRespond::serverError()
{
    buildBase();
    
    stateCode = 500;
    setPhrase("Server Error");
    setHeader("Content-Type", "text/html");

    string text = "<html><body>Server Error</body></html>";
    content.clear();
    content.assign(text.begin(), text.end());
    setHeader("Content-Length", tostr<size_t>(content.size()) );

    info_.fd = -1;
    
}

void HttpRespond::notModified()
{
    buildBase();
    
    stateCode = 304;
    setPhrase("Not Modified");
    info_.fd = -1;
    
}

void HttpRespond::encode(char* ptr, int& len)
{
    string tmp;
    tmp += "HTTP/";
    switch(version)
    {
        case Http10:
            tmp += "1.0 ";
            break;
        default:
            tmp += "1.1 ";
            break;
    }

    tmp += tostr<int>(stateCode) + " ";
    tmp += phrase_ + "\r\n";

    map<string, string>::const_iterator it = mapHeader.begin();
    
    for(; it!=mapHeader.end(); it++)
    {
        tmp += it->first + ": " + it->second + "\r\n";
    }

    tmp += "\r\n";
    if(content.size() > 0)
    {
        tmp.append(content.begin(), content.end());
        tmp += "\r\n\r\n";
    }

    tmp.copy(ptr, tmp.size(), 0);
    len = tmp.size();
}

string HttpRespond::getContentType(const string& ext ="")
{
    if(ext == "")
    {
        return "application/octet-stream";
    }
    map<string, string>::const_iterator it;
    it = mapContentType.find(ext);
    if(it == mapContentType.end())
        return "application/octet-stream";
    else
        return mapContentType[ext];
    return "";
}



int HttpRespond::resFile(const string& path, HttpRequest& myReq)
{
    int fd = open(path.c_str(), O_RDONLY);
    if(fd < 0)
    {
        return -1; 
        //Check;
    }

    unsigned long fileSize = -1;
    struct stat statBuf;
    if(fstat(fd, &statBuf) < 0)
    {
        ::close(fd);
        return -1;
    }

    //不是普通文件
    if(! S_ISREG(statBuf.st_mode) )
    {
        ::close(fd);
        return -2;
    }

    if(myReq.getHeader("If-Modified-Since") != "")
    {
        //Debug << "Last Time: " << strToTime(myReq.getHeader("If-Modified-Since")) << endl;
        //Debug << "Modify Time: " << statBuf.st_mtime << endl;

        time_t mtime = statBuf.st_mtime;
        struct tm* tmMtime = gmtime(&mtime);
        
        if( strToTime(myReq.getHeader("If-Modified-Since")) >= mktime(tmMtime) )
        {
            ::close(fd);
            notModified();
            return 0;
            
        }
    }

    fileSize = statBuf.st_size;
    info_.fd = fd;
    info_.fileSize = fileSize;
    
    content.clear();


    buildBase(statBuf.st_mtime);
    
    stateCode = 200;
    setPhrase("ok");

    vector<string> vecFile;
    
    Split( path.substr(path.find_last_of("/") + 1).c_str(), ".", vecFile);

    if(vecFile.size() >= 2)
    {
        setHeader("Content-Type", getContentType(vecFile[vecFile.size() - 1]));
    }
    else
    {
        setHeader("Content-Type", getContentType());
        
    }
    
    setHeader("Content-Length", tostr<size_t>(fileSize) );
    
    return 0;

    
}


int HttpRespond::isGetFile(fileInfo* info)
{
    if(info_.fd < 0)
        return -1;

    if(info != NULL)
    {
        info->fd = info_.fd;
        info->fileSize = info_.fileSize;
    }

    return 0;
}

void HttpRespond::addType()
{
    mapContentType["png"] = "application/x-png";
    mapContentType["gif"] = "image/gif";
    mapContentType["jpg"] = "image/jpeg";
    mapContentType["js"] = "application/x-javascript";
    mapContentType["html"] = "text/html";
    mapContentType["htm"] = "text/html";
    mapContentType["css"] = "text/css";
    mapContentType["txt"] = "text/plain";
}
