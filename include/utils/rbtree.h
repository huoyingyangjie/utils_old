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

    at_left:

    pp=parent->parent;
    ppp=pp->parent;



    if(parent==pp->left){
        uncle=pp->right;
        if(uncle==NULL || uncle->color==RB_BLACK){
            DBG("parent is left,uncle black");
            //set I
            node->parent=parent;

            //set parent
            parent->color=RB_BLACK;
            parent->left=node;
            pp->left=parent->right;//special
            if(parent->right!=NULL)
                parent->right->parent=pp;
            parent->right=pp;
            parent->parent=ppp;

            //set pp
            pp->parent=parent;
            pp->color=RB_RED;

            //set parent parent
            //@case1
            if(ppp==NULL){
                root->rbnode=parent;
                return;
            }
            //@case2
            if(ppp->right==pp)
                ppp->right=parent;
            else
                ppp->left=parent;

            return;


        } else{

            DBG("parent is left,uncle red");

            //set I
            node->parent=parent;

            //set parent
            parent->color=RB_BLACK;
            parent->left=node;

            //set uncle
            uncle->color=RB_BLACK;

            //set pp
            //@case1
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }

            pp->color=RB_RED;

            if(ppp->color==RB_BLACK)
                return;

            //reset node

            node=pp;
            parent=ppp;
            if(parent->right==node)
                goto at_right;
            else
                goto at_left;
        }


    } else{
        uncle=pp->left;
        if(uncle==NULL || uncle->color==RB_BLACK){
            DBG("parent is right,uncle black");

            //pre set
            parent->left=node->right;
            if(node->right!=NULL)
               node->right->parent=parent;
            pp->right=node->left;
            if(node->left!=NULL)
               node->left->parent=pp;


            //set I
            node->left=pp;
            node->right=parent;
            node->color=RB_BLACK;
            node->parent=ppp;

            //set parent
            parent->parent=node;

            //set pp
            pp->parent=node;
            pp->color=RB_RED;

            //@case1
            if(ppp==NULL){
                root->rbnode=node;
                return;
            }

            //@case2
            if(ppp->right==pp)
                ppp->right=node;
            else
                ppp->left=node;


            return;


        } else{
            //set I
            node->parent=parent;

            //set parent
            parent->left=node;
            parent->color=RB_BLACK;


            //set uncle
            uncle->color=RB_BLACK;

            //@case1
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }
            //@case2
            pp->color=RB_RED;

            if(ppp->color==RB_BLACK)
                return;

            //reset node

            node=pp;
            parent=ppp;
            if(parent->right==node)
                goto at_right;
            else
                goto at_left;
        }

    }

    at_right:

    DBG("at_right");

    //parent is red

    //set pp,ppp
    pp=parent->parent;
    ppp=pp->parent;



    if(parent==pp->left){
        uncle=pp->right;
        if(uncle==NULL || uncle->color==RB_BLACK){

            DBG("into parent left , uncle black");

            //pre set
            parent->right=node->left;
            if(node->left!=NULL)
                node->left->parent=parent;
            pp->left=node->right;
            if(node->right!=NULL)
                node->right->parent=pp;

            //set I
            node->left=parent;
            node->right=pp;
            node->color=RB_BLACK;
            node->parent=ppp;

            //set parent
            parent->parent=node;


            //set pp
            pp->parent=node;
            pp->color=RB_RED;

            //set I parent
            //@case1
            if(ppp==NULL){
                root->rbnode=node;
                return;
            }
            //@case2
            if(ppp->right==pp)
                ppp->right=node;
            else
                ppp->left=node;

            return;


        } else{

            DBG("into parent left , uncle red");

            //set I
            node->parent=parent;

            //set parent
            parent->right=node;
            parent->color=RB_BLACK;

            //set uncle
            uncle->color=RB_BLACK;

            //set pp
            //@case1
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }
            //@case2
            pp->color=RB_RED;

            if(ppp->color==RB_BLACK)
                return;

            //reset node

            node=pp;
            parent=ppp;

            if(parent->right==node)
                goto at_right;
            else
                goto at_left;
        }


    } else{

        uncle=pp->left;
        if(uncle==NULL || uncle->color==RB_BLACK){

            //set I
            node->parent=parent;

            //set parent
            pp->right=parent->left;//pre setting
            if(parent->left!=NULL)
                parent->left->parent=pp;
            parent->left=pp;
            parent->right=node;
            parent->parent=ppp;
            parent->color=RB_BLACK;

            //set pp
            pp->parent=parent;
            pp->color=RB_RED;

            //set parent parnet
            //@case1
            if(ppp==NULL){
                root->rbnode=parent;
                return;
            }
            //@case2
            if(ppp->right==pp)
                ppp->right=parent;
            else
                ppp->left=parent;
            DBG("return");
            return;

        } else{
            DBG("into parent right , uncle red,parent=%lu,node=%lu,pp=%lu",(uint64_t)parent,(uint64_t)node,(uint64_t)pp);

            //set I
            node->parent=parent;

            //set parent
            parent->right=node;
            parent->color=RB_BLACK;

            //set uncle
            uncle->color=RB_BLACK;

            //set pp

            //set pp parent
            //@case 1
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }

            pp->color=RB_RED;

            if(ppp->color==RB_BLACK)
                return;

            //reset node

            node=pp;
            parent=ppp;

            if(parent->right==node)
                goto at_right;
            else
                goto at_left;
        }

    }


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

    at_right:

    DBG("at_right");

    //parent is red

    //set pp,ppp
    pp=parent->parent;
    ppp=pp->parent;



    if(parent==pp->left){
        uncle=pp->right;
        if(uncle==NULL || uncle->color==RB_BLACK){

            DBG("into parent left , uncle black");

            //pre set
            parent->right=node->left;
            if(node->left!=NULL)
                node->left->parent=parent;
            pp->left=node->right;
            if(node->right!=NULL)
                node->right->parent=pp;

            //set I
            node->left=parent;
            node->right=pp;
            node->color=RB_BLACK;
            node->parent=ppp;

            //set parent
            parent->parent=node;


            //set pp
            pp->parent=node;
            pp->color=RB_RED;

            //set I parent
            //@case1
            if(ppp==NULL){
                root->rbnode=node;
                return;
            }
            //@case2
            if(ppp->right==pp)
                ppp->right=node;
            else
                ppp->left=node;

            return;


        } else{

            DBG("into parent left , uncle red");

            //set I
            node->parent=parent;

            //set parent
            parent->right=node;
            parent->color=RB_BLACK;

            //set uncle
            uncle->color=RB_BLACK;

            //set pp
            //@case1
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }
            //@case2
            pp->color=RB_RED;

            if(ppp->color==RB_BLACK)
                return;

            //reset node

            node=pp;
            parent=ppp;

            if(parent->right==node)
                goto at_right;
            else
                goto at_left;
        }


    } else{

        uncle=pp->left;
        if(uncle==NULL || uncle->color==RB_BLACK){

            //set I
            node->parent=parent;

            //set parent
            pp->right=parent->left;//pre setting
            if(parent->left!=NULL)
                parent->left->parent=pp;
            parent->left=pp;
            parent->right=node;
            parent->parent=ppp;
            parent->color=RB_BLACK;

            //set pp
            pp->parent=parent;
            pp->color=RB_RED;

            //set parent parnet
            //@case1
            if(ppp==NULL){
                root->rbnode=parent;
                return;
            }
            //@case2
            if(ppp->right==pp)
                ppp->right=parent;
            else
                ppp->left=parent;
            DBG("return");
            return;

        } else{
            DBG("into parent right , uncle red,parent=%lu,node=%lu,pp=%lu",(uint64_t)parent,(uint64_t)node,(uint64_t)pp);

            //set I
            node->parent=parent;

            //set parent
            parent->right=node;
            parent->color=RB_BLACK;

            //set uncle
            uncle->color=RB_BLACK;

            //set pp

            //set pp parent
            //@case 1
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }

            pp->color=RB_RED;

            if(ppp->color==RB_BLACK)
                return;

            //reset node

            node=pp;
            parent=ppp;

            if(parent->right==node)
                goto at_right;
            else
                goto at_left;
        }

    }




    at_left:

    pp=parent->parent;
    ppp=pp->parent;



    if(parent==pp->left){
        uncle=pp->right;
        if(uncle==NULL || uncle->color==RB_BLACK){
            DBG("parent is left,uncle black");
            //set I
            node->parent=parent;

            //set parent
            parent->color=RB_BLACK;
            parent->left=node;
            pp->left=parent->right;//special
            if(parent->right!=NULL)
                parent->right->parent=pp;
            parent->right=pp;
            parent->parent=ppp;

            //set pp
            pp->parent=parent;
            pp->color=RB_RED;

            //set parent parent
            //@case1
            if(ppp==NULL){
                root->rbnode=parent;
                return;
            }
            //@case2
            if(ppp->right==pp)
                ppp->right=parent;
            else
                ppp->left=parent;

            return;


        } else{

            DBG("parent is left,uncle red");

            //set I
            node->parent=parent;

            //set parent
            parent->color=RB_BLACK;
            parent->left=node;

            //set uncle
            uncle->color=RB_BLACK;

            //set pp
            //@case1
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }

            pp->color=RB_RED;

            if(ppp->color==RB_BLACK)
                return;

            //reset node

            node=pp;
            parent=ppp;
            if(parent->right==node)
                goto at_right;
            else
                goto at_left;
        }


    } else{
        uncle=pp->left;
        if(uncle==NULL || uncle->color==RB_BLACK){
            DBG("parent is right,uncle black");

            //pre set
            parent->left=node->right;
            if(node->right!=NULL)
                node->right->parent=parent;
            pp->right=node->left;
            if(node->left!=NULL)
                node->left->parent=pp;


            //set I
            node->left=pp;
            node->right=parent;
            node->color=RB_BLACK;
            node->parent=ppp;

            //set parent
            parent->parent=node;

            //set pp
            pp->parent=node;
            pp->color=RB_RED;

            //@case1
            if(ppp==NULL){
                root->rbnode=node;
                return;
            }

            //@case2
            if(ppp->right==pp)
                ppp->right=node;
            else
                ppp->left=node;


            return;


        } else{
            //set I
            node->parent=parent;

            //set parent
            parent->left=node;
            parent->color=RB_BLACK;


            //set uncle
            uncle->color=RB_BLACK;

            //@case1
            if(ppp==NULL)
            {
                root->rbnode=pp;
                return;
            }
            //@case2
            pp->color=RB_RED;

            if(ppp->color==RB_BLACK)
                return;

            //reset node

            node=pp;
            parent=ppp;
            if(parent->right==node)
                goto at_right;
            else
                goto at_left;
        }

    }

}





#endif //UTILS_RBTREE_H
