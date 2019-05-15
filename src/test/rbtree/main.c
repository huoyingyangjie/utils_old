//
// Created by yangjiegogogo@gmail.com on 5/15/19.
//

#include "utils/rbtree.h"
#include <stddef.h>
#include <stdio.h>

/**
 * test rbtree_find
 *
 */

#define RB_FIND_KEY(x) (uint64_t)x,rbtree_find(&node13,x)==NULL?0:1

void test_rbtree_find(){
    struct rbnode node13={.key=13,.color=RB_BLACK};
    struct rbnode node8 ={ .key=8,.color=RB_RED};
    struct rbnode node17={.key=17,.color=RB_RED};
    struct rbnode node1 ={.key=1,.color=RB_BLACK};
    struct rbnode node11={.key=11,.color=RB_BLACK};
    struct rbnode node15={.key=15,.color=RB_BLACK};
    struct rbnode node25={.key=25,.color=RB_BLACK};
    struct rbnode node6={.key=6,.color=RB_RED};
    struct rbnode node22={.key=22,.color=RB_RED};
    struct rbnode node27={.key=27,.color=RB_RED};

    node13.left=&node8;
    node13.right=&node17;
    node8.left=&node1;
    node8.right=&node11;
    node17.left=&node15;
    node17.right=&node25;
    node1.left=NULL;
    node1.right=&node6;
    node11.left=NULL;node11.right=NULL;
    node15.left=NULL;node15.right=NULL;
    node25.left=&node22;node25.right=&node27;
    node6.left=NULL;node6.right=NULL;
    node22.left=NULL;node22.right=NULL;
    node27.left=NULL;node27.right=NULL;

    //exist
    printf("key=%lu,find=%d\n",RB_FIND_KEY(13));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(8));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(17));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(1));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(11));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(15));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(25));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(6));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(22));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(27));
    //no exist
    printf("key=%lu,find=%d\n",RB_FIND_KEY(20));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(21));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(100));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(100000));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(2));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(3));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(4));
    printf("key=%lu,find=%d\n",RB_FIND_KEY(10));

}



int main(int argc,char *argv[]){
    test_rbtree_find();
}