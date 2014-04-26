/*
 * 文件名称：singleton.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 *  2014-3-2 首次编写
 */
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "common.h"
#include "mutex.h"

template <class T>
class Singleton
{
public:
    static T* getInstance();

protected:
    Singleton(){};    
    
private:
    static T* pInstance_;
    static Mutex mutex_;

};

template <class T>
T* Singleton<T>::pInstance_ = NULL;

template <class T>
Mutex Singleton<T>::mutex_;

template <class T>
T* Singleton<T>::getInstance()
{
    if(pInstance_ == NULL)
    {
        mutex_.lock();
        if(pInstance_ == NULL)
            pInstance_ = new T;
        mutex_.unlock();

        return pInstance_ ;	
    }
    else
        return pInstance_;
}

#endif
