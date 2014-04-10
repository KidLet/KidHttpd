/*
 * 文件名称：cond.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月1日 首次编写
 */
#include <assert.h>
#include <errno.h>
#include <sys/time.h>
#include <iostream>
#include "cond.h"

using namespace std;

Cond::Cond(const Mutex* thread_mutex):cmutex_(thread_mutex) {
	int rc;
	pthread_condattr_t attr;
	rc = pthread_condattr_init(&attr);
	assert(rc == 0);

	rc = pthread_cond_init(&cond_, &attr);
	assert(rc == 0);

	rc = pthread_condattr_destroy(&attr);
	assert(rc == 0);
}

Cond::~Cond() {
	int rc;
	rc = pthread_cond_destroy(&cond_);
	assert(rc == 0);
}

void Cond::wait() {
	pthread_cond_wait(&cond_, &cmutex_->mutex_);
}

bool Cond::timedwait(int millsecond) {
	timespec time = abstime(millsecond);
	int rc = pthread_cond_timedwait(&cond_, &cmutex_->mutex_, &time);
	/*if(rc == ETIMEDOUT)
		cout<<"time pout"<<endl;*/


	return (rc == 0);
}

void Cond::signal() {
	pthread_cond_signal(&cond_);
}

void Cond::broadcast() {
	pthread_cond_broadcast(&cond_);
}

timespec Cond::abstime(int millsecond) {
    struct timeval tv;
    timespec ts;

    gettimeofday(&tv, 0);

    int64_t it  = tv.tv_sec * (int64_t)1000000 + tv.tv_usec + (int64_t)millsecond * 1000;
    tv.tv_sec   = it / (int64_t)1000000;
    tv.tv_usec  = it % (int64_t)1000000;

    ts.tv_sec   = tv.tv_sec;
    ts.tv_nsec  = tv.tv_usec * 1000;

    return ts;
}
