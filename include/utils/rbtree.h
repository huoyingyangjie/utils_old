//
// Created by yangjiegogogo@gmail.com on 5/15/19.
//

#ifndef UTILS_RBTREE_H
#define UTILS_RBTREE_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "sys.h"



#define RB_RED   (0UL)
#define RB_BLACK (1UL)


struct rbnode {
    uint64_t color;
    struct rbnode *  left;
    struct rbnode *  right;
    struct rbnode *  parent;
    struct rbnode ** parent_leg;
};


struct rbroot {
    struct rbnode * rbnode;
};

ABS_INLINE void rbtree_init_node(struct rbnode * node){
    node->color=RB_RED;
    node->parent=NULL;
    node->right=NULL;
    node->left=NULL;
}

/*
 * initialize red black tree root node , make it as empty tree
 *
 * */

ABS_INLINE void rbtree_init_root(struct rbroot * root){
    root->rbnode=NULL;
}


ABS_INLINE void __rbtree_insert_fix(struct rbroot * root,struct rbnode * parent,struct rbnode * node){

    struct rbnode * pp;

    if(parent->color==RB_BLACK){
        return;
    }

    pp=parent->parent;

    if(pp->parent!=NULL)
    {
        parent->parent_leg=pp->parent_leg;
        *(pp->parent_leg)=parent;
        pp->parent=parent;
        pp->parent_leg=&parent->right;
        pp->left=pp->right;
        parent->right=pp;
        parent->parent=pp;
        pp->color=RB_BLACK;
        parent->color=RB_RED;
        node->color=RB_BLACK;

        if(parent->parent==RB_RED){
            if(  (*parent->parent_leg)== parent->parent->right )
                rbtree_insert_right(root,parent->parent,parent);
            rbtree_insert_left(root,parent->parent,parent);
        }
        return;
    }

    pp->parent=parent;
    pp->parent_leg=&parent->right;
    pp->left=pp->right;
    parent->parent_leg=NULL;
    parent->parent=NULL;
    parent->right=pp;
    parent->color=RB_BLACK;
    node->color=RB_BLACK;
    pp->color=RB_BLACK;

    //set root
    root->rbnode=parent;

    return;
}


ABS_INLINE void rbtree_insert_left(struct rbroot * root,struct rbnode * parent,struct rbnode * node){

    parent->left=node;
    node->parent=parent;
    node->parent_leg=&parent->left;

    __rbtree_insert_fix(root,parent,node);

    return ;
}

ABS_INLINE void rbtree_insert_right(struct rbroot * root,struct rbnode * parent,struct rbnode * node){

    parent->right=parent->left;
    parent->left=node;
    node->parent=parent;
    node->parent_leg=&parent->left;

    __rbtree_insert_fix(root,parent,node);

    return;
}



#endif //UTILS_RBTREE_H
