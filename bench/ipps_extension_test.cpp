/**
 * @file ipps_extension_test.cpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2015-03-18
 */


#include <gtest/gtest.h>

#include "ipps_extension.hpp"


/////
template<typename T>
class IntegerSampleDownTest : public testing::Test
{
};

TYPED_TEST_CASE_P(IntegerSampleDownTest);

TYPED_TEST_P(IntegerSampleDownTest, SanitCheck)
{
    int ntaps = 5;

    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(32);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(32);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(32);
    TypeParam *buf3 = (TypeParam*)ipp::malloc<TypeParam>(32);

    for(int i = 0; i < 32; ++i){
        buf0[i] = TypeParam(i);
        buf1[i] = TypeParam(i);
        buf2[i] = 0;
        buf3[i] = 0;
    }

    ipp::integer_sample_down<TypeParam> isd(
            3, 2, ntaps, 0, 0.95f);

    int no = 0;
    isd.resample(buf0, 32, buf2, &no); 
    isd.resample(buf1, 32, buf3, &no); 

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
    ipp::free(buf3);
}

REGISTER_TYPED_TEST_CASE_P(
        IntegerSampleDownTest, SanitCheck);

typedef testing::Types<
                       float
                       >IntegerSampleDownTestTypes;
INSTANTIATE_TYPED_TEST_CASE_P(
        MTPIntegerSampleDownTest,
        IntegerSampleDownTest,
        IntegerSampleDownTestTypes);

