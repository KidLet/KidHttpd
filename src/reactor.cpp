#include "reactor.h"
#include "server.h"
#include <bits/shared_ptr.h>
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

        Server::getInstance()->gLock.lock();
        if(connMap.find(list[i].fd) != connMap.end() && connMap[list[i].fd]->getStatus() == Connection::State::close
           && connMap[list[i].fd]->getWorkerState() == 1)
        {
            Debug << "Erase connMap fd:" << list[i].fd << endl;
            poller->del(list[i].fd);
            connMap.erase(list[i].fd);
            Server::getInstance()->gLock.unlock();
            continue;

        }
        Server::getInstance()->gLock.unlock();

        if(list[i].type == EventType::RW)
        {
            //Debug << "ReadWrite Event fd:" << list[i].fd << endl;
            if(this->writeCB_)
                this->writeCB_(list[i].fd);
            if(this->readCB_)
                this->readCB_(list[i].fd);
        }
        else if(list[i].type == EventType::W)
        {
            //Debug << "Write Event fd:" << list[i].fd << endl;
            if(this->writeCB_)
                this->writeCB_(list[i].fd);
        }
        else
        {
            //Debug << "read Event fd:" << list[i].fd << endl;
            if(this->readCB_)
            {
                //Debug << "excute read Event fd:" << list[i].fd << endl;
                this->readCB_(list[i].fd);
            }
        }

        
    }


    //Debug << "Cur have " << connMap.size() << " Connections" << endl;


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
    else
    {
        Debug << "onRead Not Found FD:" << fd << endl;
        poller->del(fd);
    }
}

void Reactor::onWrite(int fd)
{
    if(connMap.find(fd) != connMap.end())
    {
        connMap[fd]->onWrite();
    }
    else
    {
        Debug << "onWrite Not Found FD:" << fd << endl;
        poller->del(fd);
    }
    
}
