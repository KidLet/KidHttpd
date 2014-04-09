#include "http.h"

string Http::getHeader(const string& key)
{
    if(mapHeader.find(key) != mapHeader.end())
        return mapHeader[key];
    return "";
}

int Http::setHeader(const string& key, const string& val)
{
    mapHeader[key] = val;
    return 0;
}
