/**
 * @file ipps_test.cpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2014-12-29
 */

#include <gtest/gtest.h>

#include "ipps.hpp"

namespace ipps{

template<typename T>
T from_int(int v)
{
    return T(v);
}

template<>
std::complex<float> from_int<std::complex<float> >(int v)
{
    return std::complex<float>((float)v, (float)v);
}

template<>
std::complex<double> from_int<std::complex<double> >(int v)
{
    return std::complex<double>(v, v);
}



//////////// COPY /////////////////
template<typename T>
class CopyTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(CopyTest);

TYPED_TEST_P(CopyTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);

    memset(buf0, 0, sizeof(TypeParam) * 4096);
    memset(buf1, 0, sizeof(TypeParam) * 4096);

    for(int i = 0; i < 4096; ++i)
        buf0[i] = from_int<TypeParam>(i);
    ipp::copy(buf0, buf1, 4096);

    for(int i = 0; i < 4096; ++i)
        EXPECT_EQ(buf1[i], from_int<TypeParam>(i));

    ipp::free(buf0);
    ipp::free(buf1);
}



template<typename T>
void copyBench(int bsize, long long total)
{
    std::vector<T*> bufs;
    for(;;){
        try{
            T *buf = (T*)ipp::malloc<T>(bsize);
            if(!buf)
                break;
            bufs.push_back(buf);
        }
        catch(std::bad_alloc&){
            break;
        }

    }

    if(bufs.size() > 3){
        long long count = 0;
        for(size_t i = 0; count < total;
                i = (i + 1) % bufs.size(), count += bsize * sizeof(T)){
            size_t ni = (i + 1) % bufs.size();
            ipp::copy(bufs[i], bufs[ni], bsize);
        }
    }

    for(size_t i = 0; i < bufs.size(); ++i)
        ipp::free(bufs[i]);
}


TYPED_TEST_P(CopyTest, Benchmark)
{
    long long total = 64 * (1LL << 20);
    copyBench<TypeParam>(1 << 10, total);
    copyBench<TypeParam>(1 << 12, total);
    copyBench<TypeParam>(1 << 14, total);
    copyBench<TypeParam>(1 << 16, total);
    copyBench<TypeParam>(1 << 18, total);
    copyBench<TypeParam>(1 << 20, total);
    copyBench<TypeParam>(1 << 22, total);
}


//
REGISTER_TYPED_TEST_CASE_P(CopyTest, 
        SanitCheck, Benchmark);
typedef testing::Types<char, unsigned char,
                       short, unsigned short,
                       int, unsigned int,
                       float, double,
                       std::complex<float>, std::complex<double> > CopyTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPCopy, CopyTest, CopyTypes);


//////////// MOVE ////////

template<typename T>
class MoveTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(MoveTest);

TYPED_TEST_P(MoveTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);

    memset(buf0, 0, sizeof(TypeParam) * 4096);
    memset(buf1, 0, sizeof(TypeParam) * 4096);

    for(int i = 0; i < 4096; ++i)
        buf0[i] = from_int<TypeParam>(i);
    ipp::move(buf0, buf1, 4096);

    for(int i = 0; i < 4096; ++i)
        EXPECT_EQ(buf1[i], from_int<TypeParam>(i));

    ipp::move(buf0, buf0 + 128, 4096 - 128);

    for(int i = 0; i < 4096 - 128; ++i)
        EXPECT_EQ(buf0[i + 128], from_int<TypeParam>(i));

    ipp::free(buf0);
    ipp::free(buf1);
}



template<typename T>
void moveBench(int bsize, long long total)
{
    std::vector<T*> bufs;
    for(;;){
        try{
            T *buf = (T*)ipp::malloc<T>(bsize);
            if(!buf)
                break;
            bufs.push_back(buf);
        }
        catch(std::bad_alloc&){
            break;
        }

    }

    if(bufs.size() > 3){
        long long count = 0;
        for(size_t i = 0; count < total;
                i = (i + 1) % bufs.size(), count += bsize * sizeof(T)){
            size_t ni = (i + 1) % bufs.size();
            ipp::move(bufs[i], bufs[ni], bsize);
        }
    }

    for(size_t i = 0; i < bufs.size(); ++i)
        ipp::free(bufs[i]);
}


TYPED_TEST_P(MoveTest, Benchmark)
{
    long long total = 64 * (1LL << 20);
    moveBench<TypeParam>(1 << 10, total);
    moveBench<TypeParam>(1 << 12, total);
    moveBench<TypeParam>(1 << 14, total);
    moveBench<TypeParam>(1 << 16, total);
    moveBench<TypeParam>(1 << 18, total);
    moveBench<TypeParam>(1 << 20, total);
    moveBench<TypeParam>(1 << 22, total);
}


//
REGISTER_TYPED_TEST_CASE_P(MoveTest, 
        SanitCheck, Benchmark);
typedef testing::Types<char, unsigned char,
                       short, unsigned short,
                       int, unsigned int,
                       float, double,
                       std::complex<float>, std::complex<double> > MoveTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPMove, MoveTest, MoveTypes);



}



