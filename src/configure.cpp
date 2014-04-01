/*
 * 文件名称：configure.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014-3-31 首次编写
 */

#include "configure.h"

void Configure::parseFile(string filename, char delimeter, char comment) {
	ifstream ifs(filename.c_str());
	string line = "", key, value;
	string::size_type pos;
	conf_content.clear();

	while(!ifs.eof()) {
		getline(ifs, line);
		if(line.empty() || line.at(0) == comment)
			continue;

		line = line.substr(0, line.find(comment));

		if((pos = line.find(delimeter)) == string::npos)
			continue;

		key = trim(line.substr(0, pos));
		value = trim(line.substr(pos+1, line.size() - pos - 1));

		if(!key.empty())
			conf_content[key] = value;

	}
	ifs.close();
}

string Configure::trim(string str) {
	if(str.empty())
		return str;
	static const char ignore[]  = " \t\n\r\0\x0B";
	string::size_type pos, pos2;
	pos = str.find_first_not_of(ignore);
	if(pos == string::npos)
		return str;
	pos2 = str.find_last_not_of(ignore);
	str = str.substr(pos, pos2 - pos + 1);
	return str;
}

void Configure::render() {
	map<string, string>::iterator it;
	for(it = conf_content.begin(); it != conf_content.end(); it++) {
		cout<<(*it).first<< ": " << (*it).second<<endl;
	}
}

string Configure::getValue(string key) {
	return conf_content[key];
}
