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


class test_case
{
public:
    virtual void setup() = 0;
    virtual void run() = 0;
    virtual void teardown() = 0;
};




class test_executor
{
    std::vector<std::shared_ptr<test_case>> tests_;
public:

    template<typename T>
    int add_test()
    {
        auto t = std::make_shared<T>();

        tests_.push_back(std::dynamic_pointer_cast<test_case>(t));
    };

};


#define DEF_MTP_TEST(TCls)\
    template<typename ...Ts>\
    void __add_##TCls(test_executor &te, Ts...);\
    template<typename T, typename ...Ts>\
    void __add_##TCls(test_executor &te, Ts...)\
    {\
        typedef TCls<T> ttype;\
        te.add_test<ttype>();\
    }\
    template<>\
    void __add_##TCls(test_executor &te)\
    {\
    }


#define ADD_MTP_TEST(TCls, TE, ...)\
    __add_##TCls<__VA_ARGS__>(TE)

#define ADD_TEST(TCls, TE)\
    (TE)->add_test<TCls>()




#endif
