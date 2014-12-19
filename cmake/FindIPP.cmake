#modified from intel IPP sample build system
#need set evnrionment IPPROOT
if(NOT INTERNAL_IPP)
    set(INTERNAL_IPP static)
endif()

if( ${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(INTERNAL_ARCH intel64)
else()
    set(INTERNAL_ARCH ia32)
endif()

set(INTERNAL_IPP_INC $ENV{IPPROOT}/include)
set(INTERNAL_IPP_LIB $ENV{IPPROOT}/lib/${INTERNAL_ARCH})
set(INTERNAL_ICL_LIB $ENV{IPPROOT}/../compiler/lib/${INTERNAL_ARCH})

if( WIN32 )
    if( INTERNAL_IPP MATCHES static )
        set(INTERNAL_IPP_LIB_SUF mt)
    endif()
endif()

if( APPLE )
    string(REPLACE "$ENV{IPPROOT}/lib/${INTERNAL_ARCH}" "$ENV{IPPROOT}/lib" INTERNAL_IPP_LIB ${INTERNAL_IPP_LIB})
    string(REPLACE "$ENV{IPPROOT}/../compiler/lib/${INTERNAL_ARCH}" "$ENV{IPPROOT}/../compiler/lib" INTERNAL_ICL_LIB ${INTERNAL_ICL_LIB})
endif()

if( INTERNAL_IPP MATCHES -threaded )
    string(REPLACE "$ENV{IPPROOT}/lib/${INTERNAL_ARCH}" "$ENV{IPPROOT}/lib/${INTERNAL_ARCH}/threaded/" INTERNAL_IPP_LIB ${INTERNAL_IPP_LIB})
endif()

find_path   (INTERNAL_IPP_INC_CORE ippcore.h  PATHS ${INTERNAL_IPP_INC})
find_library(INTERNAL_IPP_LIB_CORE ippcore${INTERNAL_IPP_LIB_SUF} PATHS ${INTERNAL_IPP_LIB})


if(NOT INTERNAL_IPP_INC_CORE MATCHES NOTFOUND)
    if(NOT INTERNAL_IPP_LIB_CORE MATCHES NOTFOUND)
        set(IPP_FOUND TRUE)
    endif()
endif()

if(NOT DEFINED IPP_FOUND)
    message(FATAL_ERROR "Intel(R) IPP was not found (required)!")
else()
    file(TO_NATIVE_PATH ${INTERNAL_IPP_INC} INTERNAL_IPP_INC)
    file(TO_NATIVE_PATH ${INTERNAL_IPP_LIB} INTERNAL_IPP_LIB)
    file(TO_NATIVE_PATH ${INTERNAL_ICL_LIB} INTERNAL_ICL_LIB)
    
    #reset the include/library related to ippcore
    set(IPP_INCLUDE_DIR ${INTERNAL_IPP_INC_CORE})
    get_filename_component(IPP_LIBRARY_DIR ${INTERNAL_IPP_LIB_CORE} PATH)

    if(NOT ${CMAKE_CXX_COMPILER_ID} MATCHES Intel)
        set(IPP_ICL_LIBRARY_DIR ${IPP_LIBRARY_DIR}/../../../compiler/lib/${INTERNAL_ARCH})
        file(TO_NATIVE_PATH ${IPP_ICL_LIBRARY_DIR} IPP_ICL_LIBRARY_DIR)
        set(IPP_LIBRARY_DIR ${IPP_LIBRARY_DIR} ${IPP_ICL_LIBRARY_DIR})
    endif()

    SET(IPP_LIB_CORE ippcore${INTERNAL_IPP_LIB_SUF})
    SET(IPP_LIB_AC ippac${INTERNAL_IPP_LIB_SUF})
    SET(IPP_LIB_CC ippcc${INTERNAL_IPP_LIB_SUF})
    SET(IPP_LIB_S  ipps${INTERNAL_IPP_LIB_SUF})
    SET(IPP_LIB_VM  ippvm${INTERNAL_IPP_LIB_SUF})
    
    message(STATUS "Intel(R) IPP(${INTERNAL_IPP}) was found here: $ENV{IPPROOT}")
    message(STATUS "      folder with libraries: ${IPP_LIBRARY_DIR}")
    message(STATUS "      folder with includes : ${IPP_INCLUDE_DIR}")
endif()

