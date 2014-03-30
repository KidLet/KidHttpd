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
	Configure();
	Configure(string filename, string delimeter="=", string comment="#");


	void parseFile(string filename="/etc/httpd.conf", string delimeter="=", string comment="#"); //解析Conf文件
	bool fileExists(string filename);
	string trim(const string str);	//去掉空格

	string getValue(string key); 	//根据key返回value
	bool keyExists(string key);

	void render(); 	//输出结果

	string getDelimeter() { return _delimeter; };
	string getComment(){ return _comment; };
	void setDelimeter(string delimeter) { _delimeter = delimeter; };
	void setComment(string comment) {_comment = comment; };

private:
	map<string, string> conf_content;	//保存配置文件的key-value键值对
	string _delimeter;	//key-value之间的分隔符
	string _comment; 	//注释
};

#endif
