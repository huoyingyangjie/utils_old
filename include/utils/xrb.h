//
// Created by yangjiegogogo@gmail.com on 6/25/19.
//

#ifndef UTILS_XRB_H
#define UTILS_XRB_H


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



ABS_INLINE void rbtree_init_node(struct rbnode * node,struct rbnode * nil){
    node->color=RB_RED;
    node->parent=nil;
    node->right=nil;
    node->left=nil;
}

/*
 * initialize red black tree root node , make it as empty tree
 *
 * */

ABS_INLINE void rbtree_init_root(struct rbroot * root,struct rbnode * nil){
    root->rbnode=nil;
}

#define INSERT_RIGHT_SECOND()   \
            pp=parent->parent;\
            ppp=pp->parent;\
            if(parent==pp->left){\
            uncle=pp->right;\
            if(uncle==nil || uncle->color==RB_BLACK){\
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
            if(ppp==nil){\
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
            if(ppp==nil)\
            {\
            root->rbnode=pp;\
            return;\
            }\
            pp->color=RB_RED;\
            return;\
            }\
            } else{\
            uncle=pp->left;\
            if(uncle==nil || uncle->color==RB_BLACK){\
            node->parent=parent;\
            pp->right=parent->left;\
            if(parent->left!=nil)\
            parent->left->parent=pp;\
            parent->left=pp;\
            parent->right=node;\
            parent->parent=ppp;\
            parent->color=RB_BLACK;\
            pp->parent=parent;\
            pp->color=RB_RED;\
            if(ppp==nil){\
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
            if(ppp==nil)\
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
            if(uncle==nil || uncle->color==RB_BLACK){\
            DBG("parent is left,uncle black");\
            node->parent=parent;\
            parent->color=RB_BLACK;\
            parent->left=node;\
            pp->left=parent->right;\
            if(parent->right!=nil)\
            parent->right->parent=pp;\
            parent->right=pp;\
            parent->parent=ppp;\
            pp->parent=parent;\
            pp->color=RB_RED;\
            if(ppp==nil){\
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
            if(ppp==nil)\
            {\
            root->rbnode=pp;\
            return;\
            }\
            pp->color=RB_RED;\
            return;}\
            } else{\
            uncle=pp->left;\
            if(uncle==nil || uncle->color==RB_BLACK){\
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
            if(ppp==nil){\
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
            if(ppp==nil)\
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
        if(uncle==nil || uncle->color==RB_BLACK){\
        parent->right=nil;\
        pp->left=nil;\
        node->left=parent;\
        node->right=pp;\
        node->color=RB_BLACK;\
        node->parent=ppp;\
        parent->parent=node;\
        pp->parent=node;\
        pp->color=RB_RED;\
        if(ppp==nil){\
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
        if(ppp==nil)\
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
        if(uncle==nil || uncle->color==RB_BLACK){\
        node->parent=parent;\
        pp->right=parent->left;\
        if(parent->left!=nil)\
        parent->left->parent=pp;\
        parent->left=pp;\
        parent->right=node;\
        parent->parent=ppp;\
        parent->color=RB_BLACK;\
        pp->parent=parent;\
        pp->color=RB_RED;\
        if(ppp==nil){\
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
        if(ppp==nil)\
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
        if(uncle==nil || uncle->color==RB_BLACK){\
        DBG("parent is left,uncle black");\
        node->parent=parent;\
        parent->color=RB_BLACK;\
        parent->left=node;\
        pp->left=parent->right;\
        if(parent->right!=nil)\
        parent->right->parent=pp;\
        parent->right=pp;\
        parent->parent=ppp;\
        pp->parent=parent;\
        pp->color=RB_RED;\
        if(ppp==nil){\
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
        if(ppp==nil)\
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
        if(uncle==nil || uncle->color==RB_BLACK){\
        DBG("parent is right,uncle black");\
        parent->left=nil;\
        pp->right=nil;\
        node->left=pp;\
        node->right=parent;\
        node->color=RB_BLACK;\
        node->parent=ppp;\
        parent->parent=node;\
        pp->parent=node;\
        pp->color=RB_RED;\
        if(ppp==nil){\
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
        if(ppp==nil)\
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



ABS_INLINE void rbtree_insert_left(struct rbroot * root,struct rbnode * parent,struct rbnode * node,struct rbnode * nil){
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

ABS_INLINE void rbtree_insert_right(struct rbroot * root,struct rbnode * parent,struct rbnode * node,struct rbnode * nil){
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


#define REPLACE_NODE    if(replace->color==RB_RED){\
                        *replace=*node;\
                        replace->left->parent=replace;\
                        replace->right->parent=replace;\
                        if(replace->parent->left==replace)\
                        replace->parent->left=replace;\
                        else\
                        replace->parent->right=replace;\
                        return;\
                        }\
                        *replace=*node;\
                        replace->left->parent=replace;\
                        replace->right->parent=replace;\
                        if(replace->parent->left==replace)\
                        replace->parent->left=replace;\
                        else\
                        replace->parent->right=replace;\


ABS_INLINE void rbtree_delete(struct rbroot * root,struct rbnode * node,struct rbnode * nil){
    struct rbnode * current;
    struct rbnode * replace;
    struct rbnode * sibling;
    struct rbnode * parent;

    //find replace node
    if(node->right!=nil)
    {
        replace=node->right;
        while (replace->left!=nil)
            replace=replace->left;



    }
    else
    {
        if(node->left==nil)
            replace=node;
        else
            replace=node->left;
    }

    //keep replace and node , we don't delete any node,we just adjust tree , delete it at last


    current=replace;

    if(current->color==RB_RED)
    {
        goto exchange1;
    }

    if(current->right!=nil&&current->right->color==RB_RED)
    {
        current->right->color=RB_BLACK;
        goto exchange1;
    }

    if(current->left!=nil&&current->left->color==RB_RED){
        current->left->color=RB_BLACK;
        goto exchange1;
    }


    loop:

    if(current->parent!=nil)
    {

    }
    else
    {
        root->rbnode=current;
        goto exchange1;
    }

    exchange1:

    if(replace->parent!=nil)
    {
        if(replace->parent->left==replace)
        {
            if(replace->left!=nil)
            {
                replace->parent->left = replace->left;
                replace->left=replace->parent;
                goto exchange2;
            }
            if(replace->right!=nil)
            {
                replace->parent->left = replace->right;
                replace->right=replace->parent;
                goto exchange2;
            }
        }
        else
        {
            if(replace->left!=nil)
            {
                replace->parent->right = replace->left;
                replace->left=replace->parent;
                goto exchange2;
            }
            if(replace->right!=nil)
            {
                replace->parent->right = replace->right;
                replace->right=replace->parent;
                goto exchange2;
            }
        }
    }
    else
    {
        if(replace->left!=nil) {
            replace->left->parent = nil;
            root->rbnode=replace->left;
            goto exchange2;
        }

        if(replace->right!=nil)
        {
            replace->right->parent=nil;
            root->rbnode=replace->right;
            goto exchange2;
        }
    }

    exchange2:

    *replace=*node;
    if(node->parent!=nil)
    {
        if(node->parent->left!=node)
            node->parent->left=replace;
        else
            node->parent->right=replace;
    } else{
        root->rbnode=replace;
    }

}



#endif //UTILS_XRB_H
