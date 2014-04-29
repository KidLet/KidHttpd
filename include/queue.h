/*
 * 文件名称：queue.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014-4-5 首次编写
 *  2014-4-13 通过继承ThreadLock对Mutex和Cond进行进一步封装
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "threadlock.h"

#include <deque>
using namespace std;


template<typename T, typename D = deque<T>>
class Queue :public ThreadLock {
	typedef D queue_type;
public:
    Queue() : size_(0){};
    ~Queue() {};

    bool pop_front(T& t, int millsecond = 0);
    void push_back(T& t);
    void push_back(queue_type& qt);
    void push_front(T& t);
    void push_front(queue_type& qt);

    void notifyT();		//通知等待在队列的所有线程都醒来
    size_t size();
    void clear();
    bool empty();

private:
    queue_type queue_;
    size_t size_;
};

template<typename T, typename D>
bool Queue<T, D>::pop_front(T& t, int millsecond) {
	Lock lock(*this);
	if(queue_.empty()) {
		if(millsecond == 0) {
			return false;
		}
		if(millsecond == -1)
			wait();
		else {
			if(!timedwait(millsecond)) {
				return false;
			}
		}
	}
	if(queue_.empty()) {
		return false;
	}

	t = queue_.front();
	queue_.pop_front();
	assert(size_ >= 0);
	size_--;

	return true;
}

template<typename T, typename D>
void Queue<T, D>::push_back(T& t) {
	Lock lock(*this);
	queue_.push_back(t);
	size_++;
	cond_.signal();
}

template<typename T, typename D>
void Queue<T, D>::push_back(queue_type& qt) {
	Lock lock(*this);
	typename queue_type::const_iterator it;
	for(it = qt.begin(); it != qt.end(); it++) {
		queue_.push_back(*it);
		size_++;
		cond_.signal();
	}
}

template<typename T, typename D>
void Queue<T, D>::push_front(T& t) {
	Lock lock(*this);
	queue_.push_front(t);
	size_++;
	cond_.signal();
}

template<typename T, typename D>
void Queue<T, D>::push_front(queue_type& qt) {
	Lock lock(*this);
	typename queue_type::const_iterator it;
	for(it = qt.begin(); it != qt.end(); it++) {
		queue_.push_front(*it);
		size_++;
		cond_.signal();
	}
}

template<typename T, typename D>
void Queue<T, D>::notifyT() {
	cond_.broadcast();
}

template<typename T, typename D>
size_t Queue<T, D>::size() {
	Lock lock(*this);
	return size_;
}

template<typename T, typename D>
void Queue<T, D>::clear() {
	Lock lock(*this);
	queue_.clear();
	size_ = 0;
}

template<typename T, typename D>
bool Queue<T, D>::empty() {
	Lock lock(*this);
	return queue_.empty();
}
#endif
