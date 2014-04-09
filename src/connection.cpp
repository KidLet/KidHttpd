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
    sock->recv(readBuf, 256);
}
