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
typedef testing::Types<int8_t, uint8_t, char, unsigned char,
                       short, unsigned short,
                       int, unsigned int,
                       long long, unsigned long long,
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
typedef testing::Types<int8_t, uint8_t, char, unsigned char,
                       short, unsigned short,
                       int, unsigned int,
                       long long, unsigned long long,
                       float, double,
                       std::complex<float>, std::complex<double> > MoveTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPMove, MoveTest, MoveTypes);




//////////// SET ////////

template<typename T>
class SetTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(SetTest);

TYPED_TEST_P(SetTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);

    memset(buf0, 0, sizeof(TypeParam) * 4096);

    ipp::set(from_int<TypeParam>(0x55), buf0, 4096);

    for(int i = 0; i < 4096; ++i)
        EXPECT_EQ(buf0[i], from_int<TypeParam>(0x55));

    ipp::free(buf0);
}


REGISTER_TYPED_TEST_CASE_P(SetTest, 
        SanitCheck);
typedef testing::Types<int8_t, uint8_t, char, unsigned char,
                       short, unsigned short,
                       int, unsigned int,
                       long long, unsigned long long,
                       float, double,
                       std::complex<float>, std::complex<double> > SetTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPSet, SetTest, SetTypes);


//////////// ZERO ////////

template<typename T>
class ZeroTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(ZeroTest);

TYPED_TEST_P(ZeroTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);

    ipp::zero(buf0, 4096);

    for(int i = 0; i < 4096; ++i)
        EXPECT_EQ(buf0[i], from_int<TypeParam>(0));

    ipp::free(buf0);
}


REGISTER_TYPED_TEST_CASE_P(ZeroTest, 
        SanitCheck);
typedef testing::Types<int8_t, uint8_t, char, unsigned char,
                       short, unsigned short,
                       int, unsigned int,
                       long long, unsigned long long,
                       float, double,
                       std::complex<float>, std::complex<double> > ZeroTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPZero, ZeroTest, ZeroTypes);


//////////// Rand Uniform ////////

template<typename T>
class RandUniformTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(RandUniformTest);

TYPED_TEST_P(RandUniformTest, SanitCheck)
{
    ipp::rand_uniform<TypeParam> uni(0, 128, 0);

    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    uni.generate(buf0, 4096);

    ipp::free(buf0);
}


REGISTER_TYPED_TEST_CASE_P(RandUniformTest, 
        SanitCheck);
typedef testing::Types<uint8_t,unsigned char,
                       short,
                       float> RandUniformTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPRandUniform, RandUniformTest, RandUniformTypes);

//////////// Rand Gauss ////////

template<typename T>
class RandGaussTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(RandGaussTest);

TYPED_TEST_P(RandGaussTest, SanitCheck)
{
    ipp::rand_gauss<TypeParam> gas(0, 128, 0);

    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    gas.generate(buf0, 4096);

    ipp::free(buf0);
}


REGISTER_TYPED_TEST_CASE_P(RandGaussTest, 
        SanitCheck);
typedef testing::Types<uint8_t,unsigned char,
                       short,
                       float> RandGaussTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPRandGauss, RandGaussTest, RandGaussTypes);

//////////// VECTOR Jaehne ////////

template<typename T>
class VectorJaehneTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(VectorJaehneTest);

TYPED_TEST_P(VectorJaehneTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    ipp::vector_jaehne(buf0, 4096, (TypeParam)128);

    ipp::free(buf0);
}


REGISTER_TYPED_TEST_CASE_P(VectorJaehneTest, 
        SanitCheck);
typedef testing::Types<uint8_t,unsigned char,
                       short,
                       int,
                       float, double> VectorJaehneTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPVectorJaehne, VectorJaehneTest, VectorJaehneTypes);

//////////// VECTOR SLOPE ////////

template<typename T>
class VectorSlopeTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(VectorSlopeTest);

TYPED_TEST_P(VectorSlopeTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    ipp::vector_slope(buf0, 4096, 0, (TypeParam)128);

    ipp::free(buf0);
}


REGISTER_TYPED_TEST_CASE_P(VectorSlopeTest, 
        SanitCheck);
typedef testing::Types<uint8_t,unsigned char,
                       short, unsigned short,
                       int, unsigned int,
                       float, double> VectorSlopeTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPVectorSlope, VectorSlopeTest, VectorSlopeTypes);



//////////// AND CONST ////////

template<typename T>
class AndConstTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(AndConstTest);

TYPED_TEST_P(AndConstTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i)
        buf0[i] = from_int<TypeParam>(0xff);

    ipp::and_const(buf0, from_int<TypeParam>(0xf5), buf1, 4096);
    ipp::and_const(buf0, from_int<TypeParam>(0xf5), buf0, 4096);

    size_t ec0 = 0, ec1 = 0;
    for(size_t i = 0; i < 4096; ++i){
        ec0 += buf0[i] != from_int<TypeParam>(0xf5);
        ec1 += buf1[i] != from_int<TypeParam>(0xf5);
    }

    EXPECT_EQ(ec0, 0);
    EXPECT_EQ(ec1, 0);

    ipp::free(buf0);
    ipp::free(buf1);
}


REGISTER_TYPED_TEST_CASE_P(AndConstTest, 
        SanitCheck);
typedef testing::Types<int8_t, char, uint8_t,unsigned char,
                       short, unsigned short,
                       int, unsigned int> AndConstTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPAndConst, AndConstTest, AndConstTypes);



//////////// OR CONST ////////

template<typename T>
class OrConstTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(OrConstTest);

TYPED_TEST_P(OrConstTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i)
        buf0[i] = from_int<TypeParam>(0xff);

    ipp::or_const(buf0, from_int<TypeParam>(0xf5), buf1, 4096);
    ipp::or_const(buf0, from_int<TypeParam>(0xf5), buf0, 4096);

    TypeParam r = from_int<TypeParam>(0xf5) | from_int<TypeParam>(0xff);

    size_t ec0 = 0, ec1 = 0;
    for(size_t i = 0; i < 4096; ++i){
        ec0 += buf0[i] != r;
        ec1 += buf1[i] != r;
    }

    EXPECT_EQ(ec0, 0);
    EXPECT_EQ(ec1, 0);

    ipp::free(buf0);
    ipp::free(buf1);
}


REGISTER_TYPED_TEST_CASE_P(OrConstTest, 
        SanitCheck);
typedef testing::Types<int8_t, char, uint8_t,unsigned char,
                       short, unsigned short,
                       int, unsigned int> OrConstTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPOrConst, OrConstTest, OrConstTypes);


//////////// XOR CONST ////////

template<typename T>
class XorConstTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(XorConstTest);

TYPED_TEST_P(XorConstTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i)
        buf0[i] = from_int<TypeParam>(0xff);

    ipp::xor_const(buf0, from_int<TypeParam>(0xf5), buf1, 4096);
    ipp::xor_const(buf0, from_int<TypeParam>(0xf5), buf0, 4096);

    TypeParam r = from_int<TypeParam>(0xf5) ^ from_int<TypeParam>(0xff);

    size_t ec0 = 0, ec1 = 0;
    for(size_t i = 0; i < 4096; ++i){
        ec0 += buf0[i] != r;
        ec1 += buf1[i] != r;
    }

    EXPECT_EQ(ec0, 0);
    EXPECT_EQ(ec1, 0);

    ipp::free(buf0);
    ipp::free(buf1);
}


REGISTER_TYPED_TEST_CASE_P(XorConstTest, 
        SanitCheck);
typedef testing::Types<int8_t, char, uint8_t,unsigned char,
                       short, unsigned short,
                       int, unsigned int> XorConstTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPXorConst, XorConstTest, XorConstTypes);



//////////// AND ////////

template<typename T>
class AndTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(AndTest);

TYPED_TEST_P(AndTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0xff);
        buf1[i] = from_int<TypeParam>(0xf5);
    }

    ipp::and(buf0, buf1, buf2, 4096);
    ipp::and(buf0, buf1, buf0, 4096);

    TypeParam r = from_int<TypeParam>(0xf5) & from_int<TypeParam>(0xff);

    size_t ec0 = 0, ec1 = 0;
    for(size_t i = 0; i < 4096; ++i){
        ec0 += buf0[i] != r;
        ec1 += buf2[i] != r;
    }

    EXPECT_EQ(ec0, 0);
    EXPECT_EQ(ec1, 0);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
}


REGISTER_TYPED_TEST_CASE_P(AndTest, 
        SanitCheck);
typedef testing::Types<int8_t, char, uint8_t,unsigned char,
                       short, unsigned short,
                       int, unsigned int> AndTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPAnd, AndTest, AndTypes);




//////////// OR ////////

template<typename T>
class OrTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(OrTest);

TYPED_TEST_P(OrTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0xff);
        buf1[i] = from_int<TypeParam>(0xf5);
    }

    ipp::or(buf0, buf1, buf2, 4096);
    ipp::or(buf0, buf1, buf1, 4096);

    TypeParam r = from_int<TypeParam>(0xf5) | from_int<TypeParam>(0xff);

    size_t ec0 = 0, ec1 = 0;
    for(size_t i = 0; i < 4096; ++i){
        ec0 += buf1[i] != r;
        ec1 += buf2[i] != r;
    }

    EXPECT_EQ(ec0, 0);
    EXPECT_EQ(ec1, 0);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
}


REGISTER_TYPED_TEST_CASE_P(OrTest, 
        SanitCheck);
typedef testing::Types<int8_t, char, uint8_t,unsigned char,
                       short, unsigned short,
                       int, unsigned int> OrTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPOr, OrTest, OrTypes);



//////////// XOR ////////

template<typename T>
class XorTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(XorTest);

TYPED_TEST_P(XorTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0xff);
        buf1[i] = from_int<TypeParam>(0xf5);
    }

    ipp::xor(buf0, buf1, buf2, 4096);
    ipp::xor(buf0, buf1, buf1, 4096);

    TypeParam r = from_int<TypeParam>(0xf5) ^ from_int<TypeParam>(0xff);

    size_t ec0 = 0, ec1 = 0;
    for(size_t i = 0; i < 4096; ++i){
        ec0 += buf1[i] != r;
        ec1 += buf2[i] != r;
    }

    EXPECT_EQ(ec0, 0);
    EXPECT_EQ(ec1, 0);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
}


REGISTER_TYPED_TEST_CASE_P(XorTest, 
        SanitCheck);
typedef testing::Types<int8_t, char, uint8_t,unsigned char,
                       short, unsigned short,
                       int, unsigned int> XorTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPXor, XorTest, XorTypes);


//////////// NOT ////////

template<typename T>
class NotTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(NotTest);

TYPED_TEST_P(NotTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0xf5);
    }

    ipp::not(buf0, buf1, 4096);
    ipp::not(buf0, buf0, 4096);

    TypeParam r = ~from_int<TypeParam>(0xf5);

    size_t ec0 = 0, ec1 = 0;
    for(size_t i = 0; i < 4096; ++i){
        ec0 += buf0[i] != r;
        ec1 += buf1[i] != r;
    }

    EXPECT_EQ(ec0, 0);
    EXPECT_EQ(ec1, 0);

    ipp::free(buf0);
    ipp::free(buf1);
}


REGISTER_TYPED_TEST_CASE_P(NotTest, 
        SanitCheck);
typedef testing::Types<int8_t, char, uint8_t,unsigned char,
                       short, unsigned short,
                       int, unsigned int> NotTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPNot, NotTest, NotTypes);


//////////// LSHIFT ////////

template<typename T>
class LShiftTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(LShiftTest);

TYPED_TEST_P(LShiftTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x2);
    }

    ipp::lshift_const(buf0, 1, buf1, 4096);
    ipp::lshift_const(buf0, 1, buf0, 4096);

    TypeParam r = from_int<TypeParam>(4);

    size_t ec0 = 0, ec1 = 0;
    for(size_t i = 0; i < 4096; ++i){
        ec0 += buf0[i] != r;
        ec1 += buf1[i] != r;
    }

    EXPECT_EQ(ec0, 0);
    EXPECT_EQ(ec1, 0);

    ipp::free(buf0);
    ipp::free(buf1);
}


REGISTER_TYPED_TEST_CASE_P(LShiftTest, 
        SanitCheck);
typedef testing::Types<uint8_t,unsigned char,
                       short, unsigned short,
                       int> LShiftTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPLShift, LShiftTest, LShiftTypes);



//////////// RSHIFT ////////

template<typename T>
class RShiftTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(RShiftTest);

TYPED_TEST_P(RShiftTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x2);
    }

    ipp::rshift_const(buf0, 1, buf1, 4096);
    ipp::rshift_const(buf0, 1, buf0, 4096);

    TypeParam r = from_int<TypeParam>(1);

    size_t ec0 = 0, ec1 = 0;
    for(size_t i = 0; i < 4096; ++i){
        ec0 += buf0[i] != r;
        ec1 += buf1[i] != r;
    }

    EXPECT_EQ(ec0, 0);
    EXPECT_EQ(ec1, 0);

    ipp::free(buf0);
    ipp::free(buf1);
}


REGISTER_TYPED_TEST_CASE_P(RShiftTest, 
        SanitCheck);
typedef testing::Types<uint8_t,unsigned char,
                       short, unsigned short,
                       int> RShiftTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPRShift, RShiftTest, RShiftTypes);





}



