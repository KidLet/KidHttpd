/*
 * 文件名称：queue_test.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月13日 首次编写
 */

#include "queue.h"

int main() {
	Queue<int> queue;
	int i, value;
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	cout<<"pushing..."<<endl;
	for(i = 0; i < 10; i++) {
		queue.push_back(a[i]);
	}
	cout<<"size: "<<queue.size()<<endl;
	cout<<"poping..."<<endl;
	while(i > 0) {
		queue.pop_front(value);
		cout<<value<<endl;
		i--;
	}
	cout<<"pushing front..."<<endl;
	for(i = 0; i < 10; i++) {
			queue.push_front(a[i]);
		}
	while(i > 0) {
			queue.pop_front(value);
			cout<<value<<endl;
			i--;
	}

	return 0;
}

