//
// Created by yangjiegogogo@gmail.com on 5/10/19.
//

#ifndef UTILS_DEBUG_H
#define UTILS_DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include "gversion.h"

#define VERSION_FMT_LEN (64U)

static int get_major_version(){
    return MAJOR_VERSION;
}

static int get_minor_version(){
    return MINOR_VERSION;
}

static char * get_version_hash(){
    return VERSION_HASH;
}

static char * get_version_branch(){
    return VERSION_BRANCH;
}

static char * get_build_timestamp(){
    return BUILD_TIMESTAMP;
}


static char * strfversion(){
    static char version[VERSION_FMT_LEN]="";
    snprintf(version,VERSION_FMT_LEN,"%d.%d %s %s at %s",get_major_version(),get_minor_version(),get_version_branch(),get_version_hash(),get_build_timestamp());
    return version;
}


void segv_dump();

void debug_print(const char *level, const char * file, const int line, const char * fmt,...) __attribute__((format(printf,4,5)));

#define DIE(fmt,args...)  ({debug_print("DIE",__FILE__,__LINE__,fmt,##args);exit(1);})

#ifndef NDEBUG

#define DBG(fmt,args...)  ({debug_print("DBG",__FILE__,__LINE__,fmt,##args);})

#else

#define DBG(fmt,args...)

#endif

#define WRN(fmt,args...) ({debug_print("WRN",__FILE__,__LINE__,fmt,##args);})

#define INF(fmt,args...) ({debug_print("INF",__FILE__,__LINE__,fmt,##args);})

#define ERR(fmt,args...) ({debug_print("ERR",__FILE__,__LINE__,fmt,##args);})

void print_hex(const void *buf,size_t len);

#endif //UTILS_DEBUG_H
