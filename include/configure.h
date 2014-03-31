/*
 * 文件名称：configure.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月2日
 *
 *
 */
#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#include "common.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Configure {

public:
	Configure():delimeter_('='), comment_('#'){}
	Configure(string filename, char delimeter='=', char comment='#');


	void parseFile(string filename, char delimeter='=', char comment='#'); //解析Conf文件
	string trim(string str);	//去掉空格

	string getValue(string key); 	//根据key返回value

	void render(); 	//输出结果

private:
	map<string, string> conf_content;	//保存配置文件的key-value键值对
	char delimeter_;	//key-value之间的分隔符
	char comment_; 	//注释
};

#endif
