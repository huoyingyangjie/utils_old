//
// Created by yangjiegogogo@gmail.com on 5/10/19.
//

#ifndef UTILS_DEBUG_H
#define UTILS_DEBUG_H

#include <stdio.h>
#include "gversion.h"

#define VERSION_FMT_LEN (64U)

static int get_major_version(){
    return MAJOR_VERSION;
}

static int get_minor_version(){
    return MINOR_VERSION;
}

static char * get_version_hash(){
    return VERSION_HASH;
}

static char * get_version_branch(){
    return VERSION_BRANCH;
}

static char * get_build_timestamp(){
    return BUILD_TIMESTAMP;
}


char * strfversion(){
    static char version[VERSION_FMT_LEN]="";
    snprintf(version,VERSION_FMT_LEN,"%d.%d %s %s at %s",get_major_version(),get_minor_version(),get_version_branch(),get_version_hash(),get_build_timestamp());
    return version;
}


#endif //UTILS_DEBUG_H
