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
#include <unistd.h>

template <class T>
class Singleton
{
public:
    static T* getInstance();

protected:
    Singleton(){};    
    
private:
    static T* _pInstance;

};

template <class T>
T* Singleton<T>::_pInstance = NULL;

template <class T>
T* Singleton<T>::getInstance()
{
    if(_pInstance == NULL)
    {
	usleep(10000);
	return (_pInstance = new T);	
    }
    else
	return _pInstance;
}

#endif
