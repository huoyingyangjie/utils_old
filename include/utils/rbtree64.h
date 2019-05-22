//
// Created by yangjiegogogo@gmail.com on 5/21/19.
//

#ifndef UTILS_RBTREE64_H
#define UTILS_RBTREE64_H

#include "rbtree.h"


struct rbnode64 {
    struct rbnode node;
    uint64_t key;
    void * data;
};

ABS_INLINE struct rbnode64 * rbtree_insert(struct rbroot * root,struct rbnode64 * node){

    struct rbnode * tmp=root->rbnode;

    // root is null
    if(unlikely(tmp==NULL))
    {
        node->node.color=RB_BLACK;
        root->rbnode=node;
        return NULL;
    }

    while (tmp!=NULL){
        if( ((struct rbnode64*)tmp)->key==node->key ){
            return (struct rbnode64*)tmp;
        }
        tmp=((struct rbnode64*)tmp)->key > node->key ? tmp->left : tmp->right;
    }

    if(((struct rbnode64*)tmp)->key > node->key){
        rbtree_insert_left(root,tmp,node);
        return NULL;
    }

    rbtree_insert_right(root,tmp,node);
    return NULL;
}

ABS_INLINE struct rbnode64 * rbtree_find(){

}




#endif //UTILS_RBTREE64_H
