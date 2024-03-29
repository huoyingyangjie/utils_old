//
// Created by yangjiegogogo@gmail.com on 5/15/19.
//

#include "utils/rbtree64.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "utils/debug.h"
/**
 * test rbtree_find
 *
 */


#define NODE_NUMBER (1000UL)

#define NO_EXIST_TEST(x) node=rbtree64_search(&root,x);if(node!=NULL) DIE("no exist test failed,key=%lu",x);

#define A1 {1635473346,617602265,1451396207,639755663,331245221,797084493,1031290962,1828366978,272289527,316365231,1416474063,591907484,1457966533,12,34,58,345,456456}


#define A2 {899586652,654339113,1250575619,2067769305,1506386366,101035835,1718995144,331199135,1058168830,67730304,2138020356,1076550924,153956473,68293714,1554057185,168263314,2056467781,1716027025,10402866,1273790203,44107102,824123299,304271307}


void print_node(struct rbnode64 * node64){
    printf("\n");
    printf("node:key=%lu,self=%lu,parent=%lu,left=%lu,right=%lu,color=%s\n",node64->key,(uint64_t)(&node64->node),(uint64_t)node64->node.parent,(uint64_t)node64->node.left,(uint64_t)node64->node.right,
    node64->node.color==RB_RED?"red":"black");
    printf("\n");
}


void check_rule4(struct rbnode64 * node64){
    struct rbnode * node=&node64->node;
    if(node->color==RB_BLACK)
        return;
    if(node->parent!=NULL)
    {
        if(node->parent->color==RB_RED)
            DIE("self=%lu is red and parent=%lu is red",node64->key,((struct rbnode64*)node->parent)->key);
    }

    if(node->left!=NULL)
    {
        if(node->left->color==RB_RED)
            DIE("self=%lu is red and left child=%lu is red",node64->key,((struct rbnode64*)node->left)->key);
    }

    if(node->right!=NULL)
    {
        if(node->right->color==RB_RED)
            DIE("self=%lu is red and right=%lu is red",node64->key,((struct rbnode64*)node->right)->key);
    }

}

struct rbroot* test_rbtree_insert_and_find(){

    uint64_t i=0;
    uint64_t j=0;
    static struct rbroot root;
    struct rbnode64 * node;

    static struct rbnode64 nodes[NODE_NUMBER];

    uint64_t keys[]=A2;

    uint64_t keys_size=sizeof(keys)/ sizeof(uint64_t);

    again:

    i=0;

    srand(time(0));

    rbtree_init_root(&root);

    while (i<  NODE_NUMBER)
    {
        node=&nodes[i];
        rbtree_init_node(&node->node);

        node->key=rand();
        INF("inserting node-->%lu",node->key);
        rbtree64_insert(&root,node);
        ++i;


        DBG("root=%lu",((struct rbnode64*)root.rbnode)->key);
        for(j=0;j<i;++j) {
            node=&nodes[j];
            printf("CHECK left=%020lu right=%020lu self=%020lu parent=%020lu color=%s selfptr=%lu\n",node->node.left==NULL?0:((struct rbnode64*)(node->node.left))->key,
                node->node.right==NULL?0:((struct rbnode64*)(node->node.right))->key,
                   node->key,node->node.parent==NULL?0:((struct rbnode64*)(node->node.parent))->key,node->node.color==RB_RED?"red":"black",(uint64_t)node);
        }

        rbtree64_all(&root,check_rule4);

        is_balance(&root);

        check_rbtree(&root);


    }




    INF("delete test");

    uint64_t key;

    struct rbnode64 * delete_node;

    for(i=0;i<100;++i){
        key=nodes[rand()%NODE_NUMBER].key;
        INF("ready to delete %lu",key);
        delete_node=rbtree64_delete(&root,key);
        INF("key=%lu %s",key,delete_node==NULL?"no exist":"OK");

        rbtree64_all(&root,print_node);
        rbtree64_all(&root,check_rule4);
        INF("check rbtree");
        is_balance(&root);
        check_rbtree(&root);
    }


     goto again;

//    INF("exist test");
//
//    for(i=0;i<keys_size;++i){
//        node=rbtree64_search(&root,keys[i]);
//        if(node==NULL||node->key!=keys[i]){
//            DIE("search error");
//        }
//        else
//            INF("exist key=%lu",node->key);
//    }
//
//    INF("no exist test");
//    NO_EXIST_TEST(1UL);
//    NO_EXIST_TEST(2UL);
//    NO_EXIST_TEST(3445646UL);
//    NO_EXIST_TEST(1263575UL);
//    NO_EXIST_TEST(7542254UL);
//
//    INF("no exist test:passed");
    return &root;

}

void  is_balance(struct rbroot * root){
    if(root->rbnode==NULL)
        return;
    if(root->rbnode->color==RB_RED)
        DIE("root is red");
    int count=0;
    struct rbnode * cur=root->rbnode;
    while (cur!=NULL){
        if(cur->color==RB_BLACK)
            ++count;
        cur=cur->left;
    }
    int num=0;

    _is_balance(root->rbnode,count,num);
}


void _is_balance(struct rbnode * node,int count,int num){
    if(node==NULL)
        return;
    if(node->color==RB_RED)
    {
        if(node->parent==NULL)
        {
            DIE("node is red,but parent is null");
        }
        if(node->parent->color==RB_RED)
            DIE("continue red node");
    }

    if(node->color==RB_BLACK)
        ++num;

    if(node->left==NULL&&node->right==NULL)
    {
        if(num!=count)
        {
            DIE("black node different");
        }
    }

    _is_balance(node->left,count,num);
    _is_balance(node->right,count,num);
}

uint64_t get_rbtree_black_count(struct rbroot * root){
    struct rbnode * tmp;

    uint64_t black_count=0;

    tmp=root->rbnode;

    while(tmp){
        if(tmp->color==RB_BLACK)
            ++black_count;
        tmp=tmp->left;
    }
    return black_count;
}



void traverse_check_rbtree(struct rbnode * node,uint64_t tmp_black_count,uint64_t black_count){

    struct rbnode * tmp;
    if(node==NULL)
    {
     if(tmp_black_count!=black_count)
        DIE("rbtree isn't ok,");
     return;
    }
    if(node->color==RB_BLACK)
        ++tmp_black_count;

    tmp=node->left;
    traverse_check_rbtree(tmp,tmp_black_count,black_count);
    tmp=node->right;
    traverse_check_rbtree(tmp,tmp_black_count,black_count);
}

void check_rbtree(struct rbroot * root){
    if(root->rbnode==NULL)
    {
        INF("rbtree is ok");
        return;
    }

    if(root->rbnode->color==RB_RED)
    {
        DIE("rbtree isn't ok");
    }

    uint64_t black_count=get_rbtree_black_count(root);

    traverse_check_rbtree(root->rbnode,0,black_count);

    INF("rbtree is ok");
}




int main(int argc,char *argv[]){
    struct rbroot *root=test_rbtree_insert_and_find();
    INF("check rbtree");
    check_rbtree(root);
    return 0;
}