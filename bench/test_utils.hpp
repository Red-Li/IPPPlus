/**
 * @file test_utils.hpp
 * @Brief 
 * @author Red Li
 * @version 
 * @date 2014-12-26
 */

#ifndef IPPPLUS_BENCH_TEST_UTILS_HPP
#define IPPPLUS_BENCH_TEST_UTILS_HPP

#define STATIC_CHECK(exp) static_assert((exp), #exp)
#define SAME_TYPE_CHECK(T0, T1) static_assert(std::is_same<T0, T1>::value, #T0 " is not same as " #T1)


#endif
