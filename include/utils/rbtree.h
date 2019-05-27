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


ABS_INLINE void rbtree_insert_left(struct rbroot * root,struct rbnode * parent,struct rbnode * node){

    struct rbnode * uncle;
    struct rbnode * pp;
    struct rbnode * ppp;

    DIE("goto die");

    again:

    if(parent->color==RB_BLACK) {
        parent->left = node;
        node->parent = parent;
        return;
    }

    pp=parent->parent;

    if(parent==pp->left){
        uncle=pp->right;
        if(uncle==NULL || uncle->color==RB_BLACK){
            ppp=pp->parent;

            parent->left=node;
            pp->parent=parent;
            pp->left=NULL;
            parent->right=pp;
            node->parent=parent;
            parent->color=RB_BLACK;
            pp->color=RB_RED;

            if(ppp==NULL){
                root->rbnode=parent;
                parent->parent=NULL;
                return;
            }


            if(ppp->right==pp){
                ppp->right=parent;
            }
            ppp->left=parent;
            parent->parent=ppp;
            return;

        } else{

            parent->left=node;
            node->parent=parent;

            parent->color=RB_BLACK;
            uncle->color=RB_BLACK;
            pp->color=RB_RED;

            ppp=pp->parent;

            if(ppp==NULL)
            {
                root->rbnode=pp;
                pp->color=RB_BLACK;
                return;
            }

            node=pp;
            parent=ppp;
            goto again;
        }


    } else{
        uncle=pp->left;
        if(uncle==NULL || uncle->color==RB_BLACK){
            ppp=pp->parent;

            if(ppp==NULL){
                root->rbnode=node;
                parent->parent=node;
                pp->parent=node;
                pp->right=NULL;
                node->left=pp;
                node->right=parent;
                node->color=RB_BLACK;
                pp->color=RB_RED;
                return;
            }


            if(ppp->right==pp){
                ppp->right=node;
            }
            ppp->left=node;
            node->parent=ppp;
            return;

        } else{

            parent->left=node;
            node->parent=parent;

            parent->color=RB_BLACK;
            uncle->color=RB_BLACK;
            pp->color=RB_RED;

            ppp=pp->parent;

            if(ppp==NULL)
            {
                root->rbnode=pp;
                pp->color=RB_BLACK;
                return;
            }

            node=pp;
            parent=ppp;
            goto again;
        }

    }




}

ABS_INLINE void rbtree_insert_right(struct rbroot * root,struct rbnode * parent,struct rbnode * node){
    struct rbnode * uncle;
    struct rbnode * pp;
    struct rbnode * ppp;

    again:

    if(parent->color==RB_BLACK) {
        parent->right = node;
        node->parent = parent;
        return;
    }

    pp=parent->parent;


    if(parent==pp->left){
        uncle=pp->right;
        if(uncle==NULL || uncle->color==RB_BLACK){

            DBG("into parent left , uncle black");

            ppp=pp->parent;

            node->left=parent;
            node->right=pp;
            pp->parent=node;
            parent->parent=node;
            pp->left=NULL;

            pp->color=RB_RED;
            node->color=RB_BLACK;

            if(ppp==NULL){
                root->rbnode=node;
                return;
            }


            if(ppp->right==pp)
                ppp->right=node;
            else
                ppp->left=node;
            node->parent=ppp;
            return;

        } else{

            DBG("into parent left , uncle red");
            parent->right=node;
            node->parent=parent;

            parent->color=RB_BLACK;
            uncle->color=RB_BLACK;


            ppp=pp->parent;

            if(ppp==NULL)
            {
                root->rbnode=pp;
                pp->color=RB_BLACK;
                return;
            }

            pp->color=RB_RED;

            node=pp;
            parent=ppp;
            goto again;
        }


    } else{
        uncle=pp->left;
        if(uncle==NULL || uncle->color==RB_BLACK){

            DBG("into parent right , uncle black");

            ppp=pp->parent;

            pp->right=parent->left;
            parent->left=pp;
            parent->right=node;
            pp->parent=parent;
            parent->color=RB_BLACK;
            pp->color=RB_RED;
            node->parent=parent;

            if(ppp==NULL){
                root->rbnode=parent;
                parent->parent=NULL;
                return;
            }


            if(ppp->right==pp)
                ppp->right=parent;
            else
                ppp->left=parent;
            parent->parent=ppp;
            return;

        } else{
            DBG("into parent right , uncle red");
            parent->right=node;
            node->parent=parent;

            parent->color=RB_BLACK;
            uncle->color=RB_BLACK;


            ppp=pp->parent;

            if(ppp==NULL)
            {
                root->rbnode=pp;
                pp->color=RB_BLACK;
                return;
            }

            pp->color=RB_RED;

            node=pp;
            parent=ppp;
            if(parent->right==node)
                goto again;
            else{
                again2:
                if(parent->color==RB_BLACK) {
                    parent->left = node;
                    node->parent = parent;
                    return;
                }

                pp=parent->parent;

                if(parent==pp->left){
                    uncle=pp->right;
                    if(uncle==NULL || uncle->color==RB_BLACK){
                        ppp=pp->parent;

                        pp->left=parent->right;
                        parent->left=node;
                        pp->parent=parent;
                        parent->right=pp;
                        node->parent=parent;
                        parent->color=RB_BLACK;
                        pp->color=RB_RED;

                        if(ppp==NULL){
                            root->rbnode=parent;
                            parent->parent=NULL;
                            return;
                        }


                        if(ppp->right==pp)
                            ppp->right=parent;
                        else
                             ppp->left=parent;
                        parent->parent=ppp;
                        return;

                    } else{

                        parent->left=node;
                        node->parent=parent;

                        parent->color=RB_BLACK;
                        uncle->color=RB_BLACK;


                        ppp=pp->parent;

                        if(ppp==NULL)
                        {
                            root->rbnode=pp;
                            pp->color=RB_BLACK;
                            return;
                        }

                        pp->color=RB_RED;

                        node=pp;
                        parent=ppp;
                        if(parent->right==node)
                            goto again;
                        else
                            goto again2;
                    }


                } else{
                    uncle=pp->left;
                    if(uncle==NULL || uncle->color==RB_BLACK){
                        ppp=pp->parent;

                        pp->parent=node;
                        pp->right=NULL;
                        node->left=pp;
                        node->right=parent;
                        node->color=RB_BLACK;
                        pp->color=RB_RED;

                        if(ppp==NULL){
                            root->rbnode=node;
                            parent->parent=node;

                            return;
                        }


                        if(ppp->right==pp)
                            ppp->right=node;
                        else
                            ppp->left=node;
                        node->parent=ppp;
                        return;

                    } else{

                        parent->left=node;
                        node->parent=parent;

                        parent->color=RB_BLACK;
                        uncle->color=RB_BLACK;


                        ppp=pp->parent;

                        if(ppp==NULL)
                        {
                            root->rbnode=pp;
                            pp->color=RB_BLACK;
                            return;
                        }

                        pp->color=RB_RED;

                        node=pp;
                        parent=ppp;
                        if(parent->right==node)
                            goto again;
                        else
                            goto again2;
                    }

                }
            }
        }

    }

}



#endif //UTILS_RBTREE_H
