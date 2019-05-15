//
// Created by yangjiegogogo@gmail.com on 5/15/19.
//

#ifndef UTILS_RBTREE_H
#define UTILS_RBTREE_H

#include <stdint.h>

enum rbcolor{
    RB_RED=0,
    RB_BLACK=1,
};

struct rbnode {
    uint64_t key;
    void * data;
    struct rbnode * left;
    struct rbnode * right;
    enum rbcolor color;
};

#endif //UTILS_RBTREE_H
