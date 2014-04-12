#include "httprequest.h"
HttpRequest::Method HttpRequest::getMethod()
{
    return method_;
}

void HttpRequest::setMethod(Method m)
{
    method_ = m;
}
