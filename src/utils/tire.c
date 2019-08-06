//
// Created by yangjiegogogo@gmail.com on 8/6/19.
//

#include "utils/tire.h"


struct tire_t * tire_create(){
    struct tire_t * tire=NULL;
    tire=(struct tire_t*)malloc(sizeof(struct tire_t));
    if(!tire)
        return NULL;
    memset(tire,0,sizeof(struct tire_t));
    return tire;
}

int tire_add(struct tire_t * root, char * str, void *val){
    struct tire_t * node=root;
    unsigned char character;
    again:
    character = *((unsigned char *)str);
    if(!character)
        return -1;
    if(!(node->nodes[character]))
    {
        node->nodes[character]=(struct tire_t *)malloc(sizeof(struct tire_t));
        if(!(node->nodes[character]))
            return -1;
        memset(node->nodes[character],0, sizeof(node->nodes));
    }
    node=node->nodes[character];
    if(!(*(++str)))
    {
        node->val=val;
        SFENCE;
        node->light=1;
        LFENCE;
        return 0;
    }
    goto again;
}