/**
 * @file main.cpp
 * @Brief 
 * @author Red Li
 * @version 
 * @date 2014-12-19
 */

#include <memory>
#include <vector>

#include "ipptype.hpp"
#include "ipps.hpp"

#include "ipptype_test.hpp"


class test_executor
{
    std::vector<std::shared_ptr<test_case>> tests_;
public:


    template<typename T, typename ...Args>
    int add_test(Args ...args)
    {
        auto t = std::make_shared<T>(args...);

        tests_.push_back(std::dynamic_pointer_cast<test_case>(t));
    };

};



int main(int argc, char *argv[])
{
    test_executor exec;

    return 0;
}
