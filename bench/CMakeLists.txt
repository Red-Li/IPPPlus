
include(IPPPlus)

file(GLOB BENCH_SRCS *.cpp)

link_directories(${IPP_LIBRARY_DIR})

add_executable(ipp_bench ${BENCH_SRCS})

target_include_directories(ipp_bench PRIVATE
    ${IPP_INCLUDE_DIR}
    )


target_link_libraries(ipp_bench ${IPP_LIB_S} ${IPP_LIB_CORE}
    )


INSTALL(TARGETS ipp_bench
    RUNTIME DESTINATION ${CMAKE_INSTALL_PATH}/bin)

