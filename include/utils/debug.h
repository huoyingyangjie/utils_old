// Authors: YangJie, <yangjiegogogo@gmail.com> on 8/16/19.

#ifndef UTILS_DEBUG_H
#define UTILS_DEBUG_H

#include <stdio.h>
#include <stdlib.h>


void segv_dump();

void debug_print_s(const char *level, const char * file, const int line, const char * fmt,...) __attribute__((format(printf,4,5)));

#define DIE(fmt,args...)  ({debug_print_s("DIE",__FILE__,__LINE__,fmt,##args);exit(1);})

#ifndef NDEBUG

#define DBG(fmt,args...)  ({debug_print_s("DBG",__FILE__,__LINE__,fmt,##args);})

#else

#define DBG(fmt,args...)

#endif

#define WRN(fmt,args...) ({debug_print_s("WRN",__FILE__,__LINE__,fmt,##args);})

#define INF(fmt,args...) ({debug_print_s("INF",__FILE__,__LINE__,fmt,##args);})

#define ERR(fmt,args...) ({debug_print_s("ERR",__FILE__,__LINE__,fmt,##args);})

void print_hex(const void *buf,size_t len);

#endif //UTILS_DEBUG_H
