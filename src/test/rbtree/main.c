//
// Created by yangjiegogogo@gmail.com on 5/15/19.
//

#include "utils/rbtree64.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "utils/debug.h"
/**
 * test rbtree_find
 *
 */


#define NODE_NUMBER (20UL)

void test_rbtree_insert_and_find(){

    uint64_t i=0;
    uint64_t j=0;
    struct rbroot root;
    struct rbnode64 * node;
    rbtree_init_root(&root);

    struct rbnode64 nodes[NODE_NUMBER];

    uint64_t keys[]={5,10,15,20,25,30,35,40,45,50,55,60,53,52,44,39,29,19,9,8};


    while (i<NODE_NUMBER)
    {
        node=&nodes[i];
        if(node==NULL)
            DIE("malloc failed=%s",strerror(errno));
        rbtree_init_node(&node->node);
        node->key=keys[i];
        INF("inserting node-->%lu",node->key);
        rbtree64_insert(&root,node);
        ++i;


        DBG("root=%lu",((struct rbnode64*)root.rbnode)->key);
        for(j=0;j<i;++j) {
            node=&nodes[j];
            DBG("left=%lu,right=%lu,self=%lu,parent=%lu,key=%lu,color=%s", (uint64_t) node->node.left,
                (uint64_t) node->node.right, (uint64_t) &node->node,  (uint64_t) node->node.parent,(uint64_t) node->key,
                node->node.color==RB_RED?"red":"black");
        }




    }



}



int main(int argc,char *argv[]){
    test_rbtree_insert_and_find();
    return 0;
}