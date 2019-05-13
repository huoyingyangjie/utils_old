cmake_minimum_required(VERSION 3.3)
project(utils C)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS_ORG ${CMAKE_C_FLAGS})
set(CMAKE_C_FLAGS_DEBUG    "${CMAKE_C_FLAGS_ORG} -fPIC -O0 -g -rdynamic -Wall -fno-strict-aliasing -std=c99")
set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_ORG} -fPIC -O3 -g -rdynamic -Wall -fno-strict-aliasing -std=c99 -DNDEBUG")

list(APPEND build_options "Debug")
list(APPEND build_options "Release")
if(CMAKE_BUILD_TYPE IN_LIST build_options)
else()
    set(CMAKE_BUILD_TYPE "Debug")
endif()

aux_source_directory(./src/utils/ utils_src)
include_directories(./include/utils/)
add_library(utils SHARED ${utils_src} include/utils/gversion.h include/utils/debug.h)
add_library(utils_static STATIC ${utils_src})
set_target_properties(utils_static PROPERTIES OUTPUT_NAME utils)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/utils)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/utils)




set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/test)

