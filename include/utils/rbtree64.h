//
// Created by yangjiegogogo@gmail.com on 5/21/19.
//

#ifndef UTILS_RBTREE64_H
#define UTILS_RBTREE64_H

#include "rbtree.h"
#include "debug.h"

struct rbnode64 {
    struct rbnode node;
    uint64_t key;
    void * data;
};

ABS_INLINE struct rbnode64 * rbtree64_insert(struct rbroot * root,struct rbnode64 * node){

    struct rbnode * tmp;
    struct rbnode * last;

    tmp=root->rbnode;

    // root is null
    if(unlikely(tmp==NULL))
    {
        node->node.color=RB_BLACK;
        root->rbnode=&node->node;
        return NULL;
    }

    DBG("rbtree64: root node=%lu",(uint64_t)root->rbnode);

    DBG("rbtree64: searching last node");

    do{

        DBG("rbtree64: key=%lu",((struct rbnode64*)tmp)->key);

        if( ((struct rbnode64*)tmp)->key==node->key ){
            return (struct rbnode64*)tmp;
        }
        last=tmp;
        tmp=((struct rbnode64*)tmp)->key > node->key ? tmp->left : tmp->right;
        DBG("rbtree64: tmp=%lu",(uint64_t)tmp);

    }while(tmp!=NULL);

    DBG("rbtree64: inserting node");

    if(((struct rbnode64*)last)->key > node->key){
        rbtree_insert_left(root,last,&node->node);
        return NULL;
    }


    rbtree_insert_right(root,last,&node->node);
    return NULL;
}

ABS_INLINE struct rbnode64 * rbtree_search(struct rbroot * root,uint64_t key){

    struct rbnode * tmp;

    tmp=root->rbnode;
    // root is null
    if(unlikely(tmp==NULL))
    {
        return NULL;
    }

    do{
        if( ((struct rbnode64*)tmp)->key==key ){
            return (struct rbnode64*)tmp;
        }

        tmp=((struct rbnode64*)tmp)->key > key ? tmp->left : tmp->right;

    }while(tmp!=NULL);

    return NULL;
}




#endif //UTILS_RBTREE64_H
