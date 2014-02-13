#ifndef __SINGLETON_H__
#define __SINGLETON_H__
template <typename T>
class singleton
{
public:
    T* getInstance();

private:
    static T* _pInstance;
    singleton(){};

}

#endif
