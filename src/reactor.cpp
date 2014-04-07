#include "reactor.h"
using namespace std::placeholders;
Reactor::Reactor(shared_ptr<Poll> poll)
{
    poller = poll;
    status_ = 0;
    readCB_ = bind(&Reactor::onRead, this, _1);
    writeCB_ = bind(&Reactor::onWrite, this, _1);
}

void Reactor::run()
{
    this->status_ = 1;
    
    while(this->status_ == 1)
        this->loop(-1);
}

void Reactor::stop()
{
    this->status_ = 0;
}

int Reactor::loop(int timeOut)
{
    vector< Event > list;
    int iNumFds = poller->poll(-1, list);

    for(int i=0; i<iNumFds; i++)
    {
        if(list[i].type == EventType::RW)
        {
            if(this->writeCB_)
                this->writeCB_(list[i].fd);
            if(this->readCB_)
                this->readCB_(list[i].fd);
        }
        else if(list[i].type == EventType::W)
        {
            if(this->writeCB_)
                this->writeCB_(list[i].fd);
        }
        else
        {
            if(this->readCB_)
                this->readCB_(list[i].fd);
        }
        
    }
    return 0;
}

void Reactor::setOnRead( callBackFunc cb )
{
    readCB_ = cb;
}

void Reactor::setOnWrite( callBackFunc cb )
{
    writeCB_ = cb;
}

void Reactor::onRead(int fd)
{
    if(connMap.find(fd) != connMap.end())
    {
        connMap[fd]->onRead();
    }
}

void Reactor::onWrite(int fd)
{
    
}
