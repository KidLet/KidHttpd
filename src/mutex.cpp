/*
 * 文件名称：mutex.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月1日 首次编写
 */

#include <assert.h>
#include <errno.h>
#include <iostream>

#include "mutex.h"
#include "common.h"

using namespace std;

Mutex::Mutex() {
	int rc;
	pthread_mutexattr_t attr;

	rc = pthread_mutexattr_init(&attr);
	assert(rc == 0);

	rc = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	assert(rc == 0);

	rc = pthread_mutex_init(&mutex_, &attr);
	assert(rc == 0);

	rc = pthread_mutexattr_destroy(&attr);
	assert(rc == 0);
}

Mutex::~Mutex() {
	int rc;

	rc = pthread_mutex_destroy(&mutex_);
	assert(rc == 0);
}

void Mutex::lock() {
	int rc = pthread_mutex_lock(&mutex_);

    Check;
	assert(rc == 0);
}

bool Mutex::trylock() {
	int rc = pthread_mutex_trylock(&mutex_);
	if(rc != 0)
		if(rc == EBUSY)
			cout<<"busy"<<endl;

	return (rc == 0);
}

void Mutex::unlock() {
	int rc = pthread_mutex_unlock(&mutex_);
	assert(rc == 0);
}

