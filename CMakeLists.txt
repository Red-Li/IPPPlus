cmake_minimum_required(VERSION 2.8.9)

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
cmake_policy(SET CMP0020 NEW)
#Configration

#
project (IPPPlus)

if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(ARCH_STR "x64")
else()
    set(ARCH_STR "x86")
endif()

#Platform 


#include modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#
add_subdirectory(bench)

#install
#INSTALL(DIRECTORY include 
#    DESTINATION ${CMAKE_INSTALL_PATH})
#INSTALL(FILES cmake/FindIPP.cmake cmake/FindIPPPlus.cmake cmake/IPPPlus.cmake
#    DESTINATION ${CMAKE_INSTALL_PATH})
