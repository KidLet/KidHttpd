/*
 * 文件名称：configure_test.cpp
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：Zoey
 * 日期：2014年3月31日
 */
#include "configure.h"

int main() {
	Configure conf;
	string filename = "httpd.conf";
	conf.parseFile(filename);
	conf.render();
	return 0;
}


