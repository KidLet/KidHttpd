#include "connection.h"

Connection::Connection() :
        sock(new Socket())
{
    
}

void Connection::setReactor(Reactor* ReactorPtr)
{
    myReactorPtr = ReactorPtr;
}

Reactor* Connection::getReactor()
{
    return myReactorPtr;
}

void Connection::onRead()
{
    char buf[256];
    int len = sock->recv(buf, 256);
    sock->send(buf, len);
}
