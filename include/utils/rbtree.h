//
// Created by yangjiegogogo@gmail.com on 5/15/19.
//

#ifndef UTILS_RBTREE_H
#define UTILS_RBTREE_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "sys.h"


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



/*
 * @return:last node
 *
 * */


ABS_INLINE struct rbnode * __rbtree_insert_find(struct rbnode * root,uint64_t key){
    struct rbnode * tmp=root;
    struct rbnode * last=tmp;
    while(tmp!=NULL){
        if(tmp->key==key)
            return NULL;
        last=tmp;
        tmp=tmp->key > key?tmp->left:tmp->right;
    }
    return last;
}


/*
 * @return: root node
 *
 * */

ABS_INLINE struct rbnode *rbtree_insert(struct rbnode *root, struct rbnode * node){

    struct rbnode * last;


    node->color=RB_RED;
    node->left=NULL;
    node->right=NULL;


    if(unlikely(root!=NULL))
    {
        node->color=RB_BLACK;
        return node;
    }

    last=__rbtree_insert_find(root,node->key);

    if(last==NULL)
        return NULL;




    return 0;

}



/*
 * @return: NULL ->don't find , other -> find
 *
 * */
ABS_INLINE struct rbnode * rbtree_find(struct rbnode * root,uint64_t key){

    struct rbnode * tmp=root;

    while(tmp!=NULL){
        if(tmp->key==key)
            return tmp;
        tmp=tmp->key > key?tmp->left:tmp->right;
    }

    return tmp;
}


#endif //UTILS_RBTREE_H
