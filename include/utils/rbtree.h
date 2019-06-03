//
// Created by yangjiegogogo@gmail.com on 5/15/19.
//

#ifndef UTILS_RBTREE_H
#define UTILS_RBTREE_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "sys.h"
#include "debug.h"


#define RB_RED   (0UL)
#define RB_BLACK (1UL)


struct rbnode {
    uint64_t color;
    struct rbnode *  left;
    struct rbnode *  right;
    struct rbnode *  parent;
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

#define INSERT_RIGHT_SECOND()   \
            pp=parent->parent;\
            ppp=pp->parent;\
            if(parent==pp->left){\
            uncle=pp->right;\
            if(uncle==NULL || uncle->color==RB_BLACK){\
            parent->right=node->left;\
            node->left->parent=parent;\
            pp->left=node->right;\
            node->right->parent=pp;\
            node->left=parent;\
            node->right=pp;\
            node->color=RB_BLACK;\
            node->parent=ppp;\
            parent->parent=node;\
            pp->parent=node;\
            pp->color=RB_RED;\
            if(ppp==NULL){\
            root->rbnode=node;\
            return;\
            }\
            if(ppp->right==pp)\
            ppp->right=node;\
            else\
            ppp->left=node;\
            return;\
            } else{\
            node->parent=parent;\
            parent->right=node;\
            parent->color=RB_BLACK;\
            uncle->color=RB_BLACK;\
            if(ppp==NULL)\
            {\
            root->rbnode=pp;\
            return;\
            }\
            pp->color=RB_RED;\
            return;\
            }\
            } else{\
            uncle=pp->left;\
            if(uncle==NULL || uncle->color==RB_BLACK){\
            node->parent=parent;\
            pp->right=parent->left;\
            if(parent->left!=NULL)\
            parent->left->parent=pp;\
            parent->left=pp;\
            parent->right=node;\
            parent->parent=ppp;\
            parent->color=RB_BLACK;\
            pp->parent=parent;\
            pp->color=RB_RED;\
            if(ppp==NULL){\
            root->rbnode=parent;\
            return;\
            }\
            if(ppp->right==pp)\
            ppp->right=parent;\
            else\
            ppp->left=parent;\
            return;\
            } else{\
            node->parent=parent;\
            parent->right=node;\
            parent->color=RB_BLACK;\
            uncle->color=RB_BLACK;\
            if(ppp==NULL)\
            {\
            root->rbnode=pp;\
            return;\
            }\
            pp->color=RB_RED;\
            return;\
            }\
            }\

#define INSERT_LEFT_SECOND()   \
            pp=parent->parent;\
            ppp=pp->parent;\
            if(parent==pp->left){\
            uncle=pp->right;\
            if(uncle==NULL || uncle->color==RB_BLACK){\
            DBG("parent is left,uncle black");\
            node->parent=parent;\
            parent->color=RB_BLACK;\
            parent->left=node;\
            pp->left=parent->right;\
            if(parent->right!=NULL)\
            parent->right->parent=pp;\
            parent->right=pp;\
            parent->parent=ppp;\
            pp->parent=parent;\
            pp->color=RB_RED;\
            if(ppp==NULL){\
            root->rbnode=parent;\
            return;\
            }\
            if(ppp->right==pp)\
            ppp->right=parent;\
            else\
            ppp->left=parent;\
            return;\
            } else{\
            DBG("parent is left,uncle red");\
            node->parent=parent;\
            parent->color=RB_BLACK;\
            parent->left=node;\
            uncle->color=RB_BLACK;\
            if(ppp==NULL)\
            {\
            root->rbnode=pp;\
            return;\
            }\
            pp->color=RB_RED;\
            return;}\
            } else{\
            uncle=pp->left;\
            if(uncle==NULL || uncle->color==RB_BLACK){\
            DBG("parent is right,uncle black");\
            parent->left=node->right;\
            node->right->parent=parent;\
            pp->right=node->left;\
            node->left->parent=pp;\
            node->left=pp;\
            node->right=parent;\
            node->color=RB_BLACK;\
            node->parent=ppp;\
            parent->parent=node;\
            pp->parent=node;\
            pp->color=RB_RED;\
            if(ppp==NULL){\
            root->rbnode=node;\
            return;\
            }\
            if(ppp->right==pp)\
            ppp->right=node;\
            else\
            ppp->left=node;\
            return;\
            } else{\
            node->parent=parent;\
            parent->left=node;\
            parent->color=RB_BLACK;\
            uncle->color=RB_BLACK;\
            if(ppp==NULL)\
            {\
            root->rbnode=pp;\
            return;\
            }\
            pp->color=RB_RED;\
            return;\
            }\
            }\


#define INSERT_RIGHT_FIRST()   \
        pp=parent->parent;\
        ppp=pp->parent;\
        if(parent==pp->left){\
        uncle=pp->right;\
        if(uncle==NULL || uncle->color==RB_BLACK){\
        parent->right=NULL;\
        pp->left=NULL;\
        node->left=parent;\
        node->right=pp;\
        node->color=RB_BLACK;\
        node->parent=ppp;\
        parent->parent=node;\
        pp->parent=node;\
        pp->color=RB_RED;\
        if(ppp==NULL){\
        root->rbnode=node;\
        return;\
        }\
        if(ppp->right==pp)\
        ppp->right=node;\
        else\
        ppp->left=node;\
        return;\
        } else{\
        node->parent=parent;\
        parent->right=node;\
        parent->color=RB_BLACK;\
        uncle->color=RB_BLACK;\
        if(ppp==NULL)\
        {\
        root->rbnode=pp;\
        return;\
        }\
        pp->color=RB_RED;\
        if(ppp->color==RB_BLACK)\
        return;\
        node=pp;\
        parent=ppp;\
        if(parent->right==node)\
        {\
        INSERT_RIGHT_SECOND()\
        }\
        else\
        {INSERT_LEFT_SECOND()}\
        }\
        } else{\
        uncle=pp->left;\
        if(uncle==NULL || uncle->color==RB_BLACK){\
        node->parent=parent;\
        pp->right=parent->left;\
        if(parent->left!=NULL)\
        parent->left->parent=pp;\
        parent->left=pp;\
        parent->right=node;\
        parent->parent=ppp;\
        parent->color=RB_BLACK;\
        pp->parent=parent;\
        pp->color=RB_RED;\
        if(ppp==NULL){\
        root->rbnode=parent;\
        return;\
        }\
        if(ppp->right==pp)\
        ppp->right=parent;\
        else\
        ppp->left=parent;\
        return;\
        } else{\
        node->parent=parent;\
        parent->right=node;\
        parent->color=RB_BLACK;\
        uncle->color=RB_BLACK;\
        if(ppp==NULL)\
        {\
        root->rbnode=pp;\
        return;\
        }\
        pp->color=RB_RED;\
        if(ppp->color==RB_BLACK)\
        return;\
        node=pp;\
        parent=ppp;\
        if(parent->right==node)\
        {INSERT_RIGHT_SECOND()}\
        else\
        {INSERT_LEFT_SECOND()}\
        }\
        }\

#define INSERT_LEFT_FIRST() \
        pp=parent->parent;\
        ppp=pp->parent;\
        if(parent==pp->left){\
        uncle=pp->right;\
        if(uncle==NULL || uncle->color==RB_BLACK){\
        DBG("parent is left,uncle black");\
        node->parent=parent;\
        parent->color=RB_BLACK;\
        parent->left=node;\
        pp->left=parent->right;\
        if(parent->right!=NULL)\
        parent->right->parent=pp;\
        parent->right=pp;\
        parent->parent=ppp;\
        pp->parent=parent;\
        pp->color=RB_RED;\
        if(ppp==NULL){\
        root->rbnode=parent;\
        return;\
        }\
        if(ppp->right==pp)\
        ppp->right=parent;\
        else\
        ppp->left=parent;\
        return;\
        } else{\
        DBG("parent is left,uncle red");\
        node->parent=parent;\
        parent->color=RB_BLACK;\
        parent->left=node;\
        uncle->color=RB_BLACK;\
        if(ppp==NULL)\
        {\
        root->rbnode=pp;\
        return;\
        }\
        pp->color=RB_RED;\
        if(ppp->color==RB_BLACK)\
        return;\
        node=pp;\
        parent=ppp;\
        if(parent->right==node)\
        {INSERT_RIGHT_SECOND()}\
        else\
        {INSERT_LEFT_SECOND()}\
        }\
        } else{\
        uncle=pp->left;\
        if(uncle==NULL || uncle->color==RB_BLACK){\
        DBG("parent is right,uncle black");\
        parent->left=NULL;\
        pp->right=NULL;\
        node->left=pp;\
        node->right=parent;\
        node->color=RB_BLACK;\
        node->parent=ppp;\
        parent->parent=node;\
        pp->parent=node;\
        pp->color=RB_RED;\
        if(ppp==NULL){\
        root->rbnode=node;\
        return;\
        }\
        if(ppp->right==pp)\
        ppp->right=node;\
        else\
        ppp->left=node;\
        return;\
        } else{\
        node->parent=parent;\
        parent->left=node;\
        parent->color=RB_BLACK;\
        uncle->color=RB_BLACK;\
        if(ppp==NULL)\
        {\
        root->rbnode=pp;\
        return;\
        }\
        pp->color=RB_RED;\
        if(ppp->color==RB_BLACK)\
        return;\
        node=pp;\
        parent=ppp;\
        if(parent->right==node)\
        {INSERT_RIGHT_SECOND()}\
        else\
        {INSERT_LEFT_SECOND()}\
        }\
        }\



ABS_INLINE void __rbtree_insert_left_finally(struct rbroot * root,struct rbnode * parent,struct rbnode * node,struct rbnode * pp,struct rbnode * ppp,struct rbnode * uncle){

}

ABS_INLINE void __rbtree_insert_right_finally(struct rbroot * root,struct rbnode * parent,struct rbnode * node,struct rbnode * pp,struct rbnode * ppp,struct rbnode * uncle){

    pp=parent->parent;
    ppp=pp->parent;
    if(parent==pp->left){
        uncle=pp->right;
        if(uncle==NULL || uncle->color==RB_BLACK){
            parent->right=node->left;
            node->left->parent=parent;
            pp->left=node->right;
            node->right->parent=pp;
            node->left=parent;
            node->right=pp;
            node->color=RB_BLACK;
            node->parent=ppp;
            parent->parent=node;
            pp->parent=node;
            pp->color=RB_RED;
            if(ppp==NULL){
                root->rbnode=node;
                return;
            }
            if(ppp->right==pp)
                ppp->right=node;
            else
                ppp->left=node;
            return;
        } else{
            node->parent=parent;
            parent->right=node;
            parent->color=RB_BLACK;
            uncle->color=RB_BLACK;
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }
            pp->color=RB_RED;
            return;
        }

    } else{
        uncle=pp->left;
        if(uncle==NULL || uncle->color==RB_BLACK){
            node->parent=parent;
            pp->right=parent->left;
            parent->left->parent=pp;
            parent->left=pp;
            parent->right=node;
            parent->parent=ppp;
            parent->color=RB_BLACK;
            pp->parent=parent;
            pp->color=RB_RED;
            if(ppp==NULL){
                root->rbnode=parent;
                return;
            }
            if(ppp->right==pp)
                ppp->right=parent;
            else
                ppp->left=parent;
            return;
        } else{
            node->parent=parent;
            parent->right=node;
            parent->color=RB_BLACK;
            uncle->color=RB_BLACK;
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }
            pp->color=RB_RED;
            return;
        }
    }
}


ABS_INLINE void rbtree_insert_left(struct rbroot * root,struct rbnode * parent,struct rbnode * node){
    struct rbnode * uncle;
    struct rbnode * pp;
    struct rbnode * ppp;


    //parent is black
    if(parent->color==RB_BLACK) {
        parent->left = node;
        node->parent = parent;
        return;
    }

    INSERT_LEFT_FIRST()

}

ABS_INLINE void rbtree_insert_right(struct rbroot * root,struct rbnode * parent,struct rbnode * node){
    struct rbnode * uncle;
    struct rbnode * pp;
    struct rbnode * ppp;



    //parent is black
    if(parent->color==RB_BLACK) {
        parent->right = node;
        node->parent = parent;
        return;
    }


    INSERT_RIGHT_FIRST()



}





#endif //UTILS_RBTREE_H
