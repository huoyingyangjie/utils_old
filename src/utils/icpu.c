//
// Created by yangjiegogogo@gmail.com on 8/21/19.
//
#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include "utils/debug.h"

// first bind cpu

// second set policy

// thread set priority


int cpu_bpp_accelerate(int cpu_id, int priority){
    cpu_set_t mask;
    pthread_attr_t attr;
    struct sched_param param;
    int ret;

    if(cpu_id==-1)
        return 0;

    CPU_ZERO(&mask);
    CPU_SET(cpu_id,&mask);

    if((ret=pthread_attr_init(&attr))!=0)
        return ret;

    if((ret=pthread_setaffinity_np(pthread_self(), sizeof(mask),&mask))!=0)
        return ret;

    param.__sched_priority=priority;

    if((ret=pthread_attr_setschedparam(&attr,&param))!=0)
        return ret;

    return 0;
}
