
add_subdirectory(gtest)

include(IPPPlus)

file(GLOB SRCS *.cpp)
file(GLOB BENCH_SRCS bench*.cpp)

list(REMOVE_ITEM SRCS ${BENCH_SRCS})

#add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY=1)

link_directories(${IPP_LIBRARY_DIR})

add_executable(ipp_test ${SRCS})
add_executable(ipp_bench ${BENCH_SRCS})

target_include_directories(ipp_test PRIVATE
    gtest/include
    ${IPP_INCLUDE_DIR}
    )

target_include_directories(ipp_bench PRIVATE
    gtest/include
    ${IPP_INCLUDE_DIR}
    )


target_link_libraries(ipp_test
    gtest gtest_main ${IPP_LIB_S} ${IPP_LIB_CORE} ${IPP_LIB_VM}
    )

target_link_libraries(ipp_bench 
    gtest gtest_main ${IPP_LIB_S} ${IPP_LIB_CORE} ${IPP_LIB_VM}
    )


INSTALL(TARGETS ipp_bench
    RUNTIME DESTINATION ${CMAKE_INSTALL_PATH}/bin)

INSTALL(TARGETS ipp_test
    RUNTIME DESTINATION ${CMAKE_INSTALL_PATH}/bin)

