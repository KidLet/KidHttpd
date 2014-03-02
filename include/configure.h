/*
 * 文件名称：configure.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月2日
 *
 */
#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#include "common.h"
#include <string>
using namespace std;

class Conf
{
public:
    string getPath();
    unsigned short getPort(){return _port;}

    bool setPath(string path);
    bool setPort(unsigned port);
    bool loadFile();

    Conf(string path="./www", unsigned short port=80)
	: _path(path), _port(port)
    {cout << "Conf start:" << port << endl;}

private:
    string _path;
    unsigned short _port;
};

#endif
