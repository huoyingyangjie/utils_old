//
// Created by yangjiegogogo@gmail.com on 5/15/19.
//

#ifndef UTILS_SYS_H
#define UTILS_SYS_H

#define likely(x)   __builtin_expect(!!(x),1)
#define unlikely(x) __builtin_expect(!!(x),0)

#endif //UTILS_SYS_H