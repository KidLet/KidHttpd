/*
 * 文件名称：singleton.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 完成日期：2014年2月17日
 *
 */
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "common.h"

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
    return new T;
}

#endif
