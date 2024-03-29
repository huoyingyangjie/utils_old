//
// Created by yangjiegogogo@gmail.com on 5/13/19.
//

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <execinfo.h>
#include "utils/debug.h"
#include <pthread.h>
#include <stdlib.h>

#define BACKTRACE_SIZE (16U)
#define FILE_NAME_WIDTH (5U)
#define TIMESTAMP_WIDTH (27U)

#define ERR_NOS(fmt,args...) ({debug_print_nos("ERR",__FILE__,__LINE__,fmt,##args);})

void print_hex(const void * buf,size_t len){
    size_t i=0;
    unsigned char *cptr=(unsigned char *)buf;
    for(i=0;i<len;++i){
        if((i%16)==0 && i!=0)
          printf("\n");
        if((i%8)==0)
            printf("\n");
        printf("%02x ",*(cptr+i));

    }
    printf("\n");
}

static pthread_mutex_t debug_mutex=PTHREAD_MUTEX_INITIALIZER;


static void print_foreword(const char *level,const char *file,const int line){
    char name[FILE_NAME_WIDTH+1];
    size_t i=0;
    const char *ptr=NULL;
    size_t  len=0;
    int  flag=0;
    struct timeval tv;
    char ts[TIMESTAMP_WIDTH+1];
    struct tm ltm;

    bzero(name,sizeof(name));
    ptr=strrchr(file,'/')?(strrchr(file,'/')+1):file;
    strncpy(name,ptr,FILE_NAME_WIDTH);
    len=strlen(name);
    flag=0;
    for(i=0;i<len;++i){
        if(name[i]=='.')
        {
            name[i]=' ';
            flag=1;
            continue;
        }
        if(flag==1)
            name[i]=' ';
    }

    if(gettimeofday(&tv,NULL)!=0)
    {
        sprintf(ts,"get time error=%03d----------",errno);
        goto ptn;
    }

    if(localtime_r(&tv.tv_sec,&ltm)==NULL)
    {
        sprintf(ts,"local time error           ");
        goto ptn;
    }

    sprintf(ts,"%04d-%02d-%02d %02d:%02d:%02d %03ld:%03ld",ltm.tm_year+1900,ltm.tm_mon+1,ltm.tm_mday,
            ltm.tm_hour,ltm.tm_min,ltm.tm_sec,tv.tv_usec/1000,tv.tv_usec%1000);

    ptn:

    printf("[%s][%s][%-4d][%-7d][%-7ld][%s]:",ts,name,line,getpid(),syscall(__NR_gettid),level);
}

void debug_print_nos(const char *level,const char *file,const int line,const char *fmt,...){
    va_list args;
    print_foreword(level,file,line);
    va_start(args,fmt);
    vprintf(fmt,args);
    printf("\n");
    va_end(args);

}


void debug_print_s(const char *level,const char *file,const int line,const char *fmt,...){
    pthread_mutex_lock(&debug_mutex);
    va_list args;
    print_foreword(level,file,line);
    va_start(args,fmt);
    vprintf(fmt,args);
    printf("\n");
    va_end(args);
    pthread_mutex_unlock(&debug_mutex);
}

static void segv_backtrace(int signo){
    int i,nptrs;
    void *buffer[BACKTRACE_SIZE];
    char **strings;
    nptrs=backtrace(buffer,BACKTRACE_SIZE);
    ERR_NOS("segment fault,as follows:");
    printf("Dump stack start...\n");
    printf("backtrace() returned %d addresses\n",nptrs);

    strings=backtrace_symbols(buffer,nptrs);
    if(strings==NULL)
    {
        ERR_NOS("backtrace_symbols failed,\"man backtrace_symbols\" no errno");
        goto exit;
    }

    for(i=0;i<nptrs;++i){
        printf(" [%02d] %s\n",i,strings[i]);
    }

    free(strings);

    printf("Dump stack end...\n");

    exit:

    signal(signo,SIG_DFL);

    raise(signo);

}

void segv_dump(){
    struct sigaction sig_act;
    sig_act.sa_handler=segv_backtrace;
    sigaction(SIGSEGV,&sig_act,NULL);
}
