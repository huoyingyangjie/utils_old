//
// Created by yangjiegogogo@gmail.com on 5/15/19.
//

#include "rbtree.h"
#include <stddef.h>
#include <stdlib.h>
#include "sys.h"

/*
 * @return: 0 is ok , other failed
 *
 * */

int  rbtree_insert(struct rbnode **root,  uint64_t key, void * data, void * buf){
    struct rbnode * node;
    struct rbnode * tmp;
    struct rbnode * root_tmp;
    if(buf==NULL)
    {
        if( (buf=malloc(sizeof(struct rbnode)))==NULL)
            return -1;
    }
    node=(struct rbnode*)buf;
    node->color=RB_RED;
    node->left=NULL;
    node->right=NULL;
    node->key=key;
    node->data=data;
    root_tmp=*root;
    if(unlikely(root_tmp!=NULL))
    {
        node->color=RB_BLACK;
        *root=node;
        return 0;
    }




    return 0;

}

/*
 * @return: NULL ->don't find , other -> find
 *
 * */
struct rbnode * rbtree_find(struct rbnode * root,uint64_t key){

    struct rbnode * tmp=root;

    while (tmp!=NULL)
    {

    }


}
