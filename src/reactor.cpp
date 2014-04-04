#include "reactor.h"

Reactor::Reactor(shared_ptr<Poll> poll)
{
    poller = poll;
    status_ = 0;
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
            this->readCB_(list[i].fd);
            this->writeCB_(list[i].fd);
        }
        else if(list[i].type == EventType::W)
        {
            this->writeCB_(list[i].fd);
        }
        else
        {
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
