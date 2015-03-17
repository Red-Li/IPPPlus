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

template<>
std::complex<short> from_int<std::complex<short> >(int v)
{
    return std::complex<short>((short)v, (short)v);
}

template<>
std::complex<int> from_int<std::complex<int> >(int v)
{
    return std::complex<int>(v, v);
}


template<typename T>
T _sqrt(T v)
{
	return sqrt(v);
}

template<>
unsigned char _sqrt(unsigned char v)
{
	return (unsigned char)sqrt(float(v));
}

template<>
short _sqrt(short v)
{
	return (short)sqrt(float(v));
}

template<>
unsigned short _sqrt(unsigned short v)
{
	return (unsigned short)sqrt(float(v));
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


///// Add Const //////////
template<typename T>
class AddConstTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(AddConstTest);

TYPED_TEST_P(AddConstTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x4);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::add_const(buf0, from_int<TypeParam>(0x4), buf1, 4096, 1);  
        ipp::add_const(buf0, from_int<TypeParam>(0x4), buf0, 4096, 1);  
        r = from_int<TypeParam>(0x2) + from_int<TypeParam>(0x2);
    }
    else{
        ipp::add_const(buf0, from_int<TypeParam>(0x4), buf1, 4096);  
        ipp::add_const(buf0, from_int<TypeParam>(0x4), buf0, 4096);  
        r = from_int<TypeParam>(0x4) + from_int<TypeParam>(0x4);
    }

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


REGISTER_TYPED_TEST_CASE_P(AddConstTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       int, std::complex<short>, std::complex<int>,
                       float, double, std::complex<float>, std::complex<double>
                       > AddConstTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPAddConst, AddConstTest, AddConstTypes);


///// Mul Const //////////
template<typename T>
class MulConstTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(MulConstTest);

TYPED_TEST_P(MulConstTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x4);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::mul_const(buf0, from_int<TypeParam>(0x4), buf1, 4096, 1);  
        ipp::mul_const(buf0, from_int<TypeParam>(0x4), buf0, 4096, 1);  
        r = from_int<TypeParam>(0x4) * from_int<TypeParam>(0x2);
    }
    else{
        ipp::mul_const(buf0, from_int<TypeParam>(0x4), buf1, 4096);  
        ipp::mul_const(buf0, from_int<TypeParam>(0x4), buf0, 4096);  
        r = from_int<TypeParam>(0x4) * from_int<TypeParam>(0x4);
    }

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


REGISTER_TYPED_TEST_CASE_P(MulConstTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       int, std::complex<short>, std::complex<int>,
                       float, double, std::complex<float>, std::complex<double>
                       > MulConstTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPMulConst, MulConstTest, MulConstTypes);


///// Sub Const //////////
template<typename T>
class SubConstTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(SubConstTest);

TYPED_TEST_P(SubConstTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x8);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::sub_const(buf0, from_int<TypeParam>(0x4), buf1, 4096, 1);  
        ipp::sub_const(buf0, from_int<TypeParam>(0x4), buf0, 4096, 1);  
        r = from_int<TypeParam>(0x4) - from_int<TypeParam>(0x2);
    }
    else{
        ipp::sub_const(buf0, from_int<TypeParam>(0x4), buf1, 4096);  
        ipp::sub_const(buf0, from_int<TypeParam>(0x4), buf0, 4096);  
        r = from_int<TypeParam>(0x8) - from_int<TypeParam>(0x4);
    }

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


REGISTER_TYPED_TEST_CASE_P(SubConstTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       int, std::complex<short>, std::complex<int>,
                       float, double, std::complex<float>, std::complex<double>
                       > SubConstTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPSubConst, SubConstTest, SubConstTypes);


///// DIV Const //////////
template<typename T>
class DivConstTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(DivConstTest);

TYPED_TEST_P(DivConstTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x8);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::div_const(buf0, from_int<TypeParam>(0x4), buf1, 4096, 1);  
        ipp::div_const(buf0, from_int<TypeParam>(0x4), buf0, 4096, 1);  
        r = from_int<TypeParam>(0x4) / from_int<TypeParam>(0x4);
    }
    else{
        ipp::div_const(buf0, from_int<TypeParam>(0x4), buf1, 4096);  
        ipp::div_const(buf0, from_int<TypeParam>(0x4), buf0, 4096);  
        r = from_int<TypeParam>(0x8) / from_int<TypeParam>(0x4);
    }

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


REGISTER_TYPED_TEST_CASE_P(DivConstTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       std::complex<short>, 
                       float, double, std::complex<float>, std::complex<double>
                       > DivConstTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPDivConst, DivConstTest, DivConstTypes);

///// Add //////////
template<typename T>
class AddTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(AddTest);

TYPED_TEST_P(AddTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x4);
        buf1[i] = from_int<TypeParam>(0x4);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::add(buf0, buf1, buf2, 4096, 1);  
        ipp::add(buf0, buf1, buf0, 4096, 1);  
        r = from_int<TypeParam>(0x2) + from_int<TypeParam>(0x2);
    }
    else{
        ipp::add(buf0, buf1, buf2, 4096);  
        ipp::add(buf0, buf1, buf0, 4096);  
        r = from_int<TypeParam>(0x4) + from_int<TypeParam>(0x4);
    }

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


REGISTER_TYPED_TEST_CASE_P(AddTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       int, std::complex<short>, std::complex<int>,
                       float, double, std::complex<float>, std::complex<double>
                       > AddTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPAdd, AddTest, AddTypes);

///// Mul //////////
template<typename T>
class MulTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(MulTest);

TYPED_TEST_P(MulTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x4);
        buf1[i] = from_int<TypeParam>(0x4);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::mul(buf0, buf1, buf2, 4096, 1);  
        ipp::mul(buf0, buf1, buf0, 4096, 1);  
        r = from_int<TypeParam>(0x4) * from_int<TypeParam>(0x2);
    }
    else{
        ipp::mul(buf0, buf1, buf2, 4096);  
        ipp::mul(buf0, buf1, buf0, 4096);  
        r = from_int<TypeParam>(0x4) * from_int<TypeParam>(0x4);
    }

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


REGISTER_TYPED_TEST_CASE_P(MulTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       int, std::complex<short>, std::complex<int>,
                       float, double, std::complex<float>, std::complex<double>
                       > MulTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPMul, MulTest, MulTypes);


///// Sub //////////
template<typename T>
class SubTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(SubTest);

TYPED_TEST_P(SubTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x8);
        buf1[i] = from_int<TypeParam>(0x4);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::sub(buf1, buf0, buf2, 4096, 1);  
        ipp::sub(buf1, buf0, buf0, 4096, 1);  
        r = from_int<TypeParam>(0x4) - from_int<TypeParam>(0x2);
    }
    else{
        ipp::sub(buf1, buf0, buf2, 4096);  
        ipp::sub(buf1, buf0, buf0, 4096);  
        r = from_int<TypeParam>(0x8) - from_int<TypeParam>(0x4);
    }

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


REGISTER_TYPED_TEST_CASE_P(SubTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       int, std::complex<short>, std::complex<int>,
                       float, double, std::complex<float>, std::complex<double>
                       > SubTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPSub, SubTest, SubTypes);


///// Div //////////
template<typename T>
class DivTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(DivTest);

TYPED_TEST_P(DivTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x8);
        buf1[i] = from_int<TypeParam>(0x4);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::div(buf1, buf0, buf2, 4096, 1);  
        ipp::div(buf1, buf0, buf0, 4096, 1);  
        r = from_int<TypeParam>(0x4) / from_int<TypeParam>(0x4);
    }
    else{
        ipp::div(buf1, buf0, buf2, 4096);  
        ipp::div(buf1, buf0, buf0, 4096);  
        r = from_int<TypeParam>(0x8) / from_int<TypeParam>(0x4);
    }

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


REGISTER_TYPED_TEST_CASE_P(DivTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       int, std::complex<short>,  
                       float, double, std::complex<float>, std::complex<double>
                       > DivTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPDiv, DivTest, DivTypes);




///// Abs //////////
template<typename T>
class AbsTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(AbsTest);

TYPED_TEST_P(AbsTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(-1);
    }

    ipp::abs(buf0, buf1, 4096);
    ipp::abs(buf0, buf0, 4096);
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


REGISTER_TYPED_TEST_CASE_P(AbsTest, 
        SanitCheck);
typedef testing::Types<
                       short,
                       int,  
                       float, double
                       > AbsTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPAbs, AbsTest, AbsTypes);



///// Sqr //////////
template<typename T>
class SqrTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(SqrTest);

TYPED_TEST_P(SqrTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x8);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::sqr(buf0, buf1, 4096, 1);  
        ipp::sqr(buf0, buf0,  4096, 1);
        r = from_int<TypeParam>(8) * from_int<TypeParam>(4);
    }
    else{
        ipp::sqr(buf0, buf1, 4096);  
        ipp::sqr(buf0, buf0, 4096);  
        r = from_int<TypeParam>(0x8) * from_int<TypeParam>(0x8);
    }

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


REGISTER_TYPED_TEST_CASE_P(SqrTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       std::complex<short>,  
                       float, double, std::complex<float>, std::complex<double>
                       > SqrTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPSqr, SqrTest, SqrTypes);




///// Sqrt //////////
template<typename T>
class SqrtTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(SqrtTest);

TYPED_TEST_P(SqrtTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(0x4);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::sqrt(buf0, buf1, 4096, 0);  
        ipp::sqrt(buf0, buf0,  4096, 0);
        r = (TypeParam)_sqrt(from_int<TypeParam>(4));
    }
    else{
        ipp::sqrt(buf0, buf1, 4096);  
        ipp::sqrt(buf0, buf0, 4096);  
        r = (TypeParam)_sqrt(from_int<TypeParam>(4));
    }

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


REGISTER_TYPED_TEST_CASE_P(SqrtTest, 
        SanitCheck);
typedef testing::Types<unsigned char,
                       short, unsigned short,
                       //std::complex<short>,  
                       float, double, 
					   //std::complex<float>, 
					   std::complex<double>
                       > SqrtTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPSqrt, SqrtTest, SqrtTypes);



///// Ln //////////
template<typename T>
class LnTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(LnTest);

TYPED_TEST_P(LnTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    for(size_t i = 0; i < 4096; ++i){
        buf0[i] = from_int<TypeParam>(10);
    }

    TypeParam r;
    if(ipp::is_integer<
            typename ipp::value_type<TypeParam>::type>::value){
        ipp::ln(buf0, buf1, 4096, 1);  
        ipp::ln(buf0, buf0,  4096, 1);
        r = (TypeParam)log(10.) / 2;
    }
    else{
        ipp::ln(buf0, buf1, 4096);  
        ipp::ln(buf0, buf0, 4096);  
        r = (TypeParam)log(10.);
    }

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


REGISTER_TYPED_TEST_CASE_P(LnTest, 
        SanitCheck);
typedef testing::Types<
                       short, int,
                       float, double
                       > LnTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPLn, LnTest, LnTypes);



///////win////
template<typename T>
class WinTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(WinTest);

TYPED_TEST_P(WinTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    typedef ipp::win<TypeParam> win_type;

    for(int tp = 0; tp < win_type::END_MAKRER; ++tp){
        win_type w((win_type::win_type)tp, 4096);

        for(size_t i = 0; i < 4096; ++i){
            buf0[i] = from_int<TypeParam>(10);
        }

        EXPECT_EQ(w.mul(buf0, buf0, 4096), ippStsNoErr);
    }

    ipp::free(buf0);
}


REGISTER_TYPED_TEST_CASE_P(WinTest, 
        SanitCheck);
typedef testing::Types<
                       short,
                       float, double,
                       std::complex<short>,
                       std::complex<float>,
                       std::complex<double>
                       >WinTestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPWinTest, WinTest, WinTestTypes);



///////auto_corr_norm////
template<typename T>
class AutoCorrNormTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(AutoCorrNormTest);

TYPED_TEST_P(AutoCorrNormTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(2048);
    typedef ipp::auto_corr_norm<TypeParam> corr_type;
    IppEnum funCfg = (IppEnum)(ippAlgAuto|ippsNormB);

    corr_type corr(4096, 2048, funCfg);

    corr.do_corr(buf0, 4096, buf1, 2048);

    ipp::free(buf0);
    ipp::free(buf1);
}


REGISTER_TYPED_TEST_CASE_P(AutoCorrNormTest, 
        SanitCheck);
typedef testing::Types<
                       float,
                       double,
                       std::complex<float>,
                       std::complex<double>
                       >AutoCorrNormTestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPAutoCorrNormTest, AutoCorrNormTest, AutoCorrNormTestTypes);


///////cross_corr_norm////
template<typename T>
class CrossCorrNormTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(CrossCorrNormTest);

TYPED_TEST_P(CrossCorrNormTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    typedef ipp::cross_corr_norm<TypeParam> corr_type;
    IppEnum funCfg = (IppEnum)(ippAlgAuto|ippsNormB);

    corr_type corr(4096, 4096, 4096, 0, funCfg);

    corr.do_corr(buf0, 4096, buf1, 4096, buf2, 4096);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
}


REGISTER_TYPED_TEST_CASE_P(CrossCorrNormTest, 
        SanitCheck);
typedef testing::Types<
                       float,
                       double,
                       std::complex<float>,
                       std::complex<double>
                       >CrossCorrNormTestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPCrossCorrNormTest, CrossCorrNormTest, CrossCorrNormTestTypes);


///////cross_corr_norm////
template<typename T>
class ConvolveTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(ConvolveTest);

TYPED_TEST_P(ConvolveTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(16);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096 + 16 - 1);
    IppEnum funCfg = (IppEnum)(ippAlgAuto|ippsNormB);

    ipp::convolve<TypeParam> conv(4096, 16, funCfg);

    conv.do_convolve(buf0, 4096, buf1, 16, buf2);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
}


REGISTER_TYPED_TEST_CASE_P(ConvolveTest, 
        SanitCheck);
typedef testing::Types<
                       float,
                       double
                       >ConvolveTestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPConvolveTest, ConvolveTest, ConvolveTestTypes);



///////FFT////
template<typename T>
class FFTTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(FFTTest);

TYPED_TEST_P(FFTTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf3 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    ipp::fft<TypeParam, true> fft(12);

    fft.forward(buf0, buf1, buf2, buf3);
    fft.inverse(buf0, buf1, buf2, buf3);
    fft.forward(buf0, buf1, buf0, buf1); //in-place
    fft.inverse(buf0, buf1, buf0, buf1);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
    ipp::free(buf3);
}


REGISTER_TYPED_TEST_CASE_P(FFTTest, 
        SanitCheck);
typedef testing::Types<
                       float,
                       double
                       >FFTTestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPFFTTest, FFTTest, FFTTestTypes);


template<typename T>
class FFT2Test : public testing::Test
{
};

//
TYPED_TEST_CASE_P(FFT2Test);

TYPED_TEST_P(FFT2Test, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4096);
    
    ipp::fft<TypeParam, ipp::is_complex<TypeParam>::value > fft(12);

    fft.forward(buf0, buf1);
    fft.inverse(buf0, buf1);
    fft.forward(buf0, buf0); //in-place
    fft.inverse(buf0, buf0);

    ipp::free(buf0);
    ipp::free(buf1);
}


REGISTER_TYPED_TEST_CASE_P(FFT2Test, 
        SanitCheck);
typedef testing::Types<
                       float,
                       double,
                       std::complex<float>,
                       std::complex<double>
                       >FFT2TestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPFFT2Test, FFT2Test, FFT2TestTypes);



///////FIR SR////
template<typename T>
class FIRSRTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(FIRSRTest);

TYPED_TEST_P(FIRSRTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4);
    TypeParam *buf3 = (TypeParam*)ipp::malloc<TypeParam>(4);
    
    TypeParam taps[3] = {1., 2., 3.};
    for(int i = 0; i < 4; ++i){
        buf0[i] = 1;
        buf1[i] = 1;
        buf2[i] = 1;
        buf3[i] = 1;
    }

    ipp::fir_sr<TypeParam> sr(taps, 3, ippAlgFFT);

    sr.filter(buf0, buf2, 4);
    sr.filter(buf1, buf3, 4);

    EXPECT_EQ(buf2[0], 1);
    EXPECT_EQ(buf2[1], 3);
    EXPECT_EQ(buf2[2], 6);
    EXPECT_EQ(buf3[0], 6);
    EXPECT_EQ(buf3[1], 6);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
    ipp::free(buf3);
}


REGISTER_TYPED_TEST_CASE_P(FIRSRTest, 
        SanitCheck);
typedef testing::Types<
                       float,
                       double
                       >FIRSRTestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPFIRSRTest, FIRSRTest, FIRSRTestTypes);

///////FIR////
template<typename T>
class FIRTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(FIRTest);

TYPED_TEST_P(FIRTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(4);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(4);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(4);
    TypeParam *buf3 = (TypeParam*)ipp::malloc<TypeParam>(4);
    
    TypeParam taps[3] = {1., 2., 3.};
    for(int i = 0; i < 4; ++i){
        buf0[i] = 1;
        buf1[i] = 1;
        buf2[i] = 1;
        buf3[i] = 1;
    }

    ipp::fir<TypeParam> sr(taps, 3);

    sr.filter(buf0, buf2, 4);
    sr.filter(buf1, buf3, 4);

    EXPECT_EQ(buf2[0], 1);
    EXPECT_EQ(buf2[1], 3);
    EXPECT_EQ(buf2[2], 6);
    EXPECT_EQ(buf3[0], 6);
    EXPECT_EQ(buf3[1], 6);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
    ipp::free(buf3);
}


REGISTER_TYPED_TEST_CASE_P(FIRTest, 
        SanitCheck);
typedef testing::Types<
                       float,
                       double
                       >FIRTestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPFIRTest, FIRTest, FIRTestTypes);



///////FIRMR////
template<typename T>
class FIRMRTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(FIRMRTest);

TYPED_TEST_P(FIRMRTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(9);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(9);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(9);
    TypeParam *buf3 = (TypeParam*)ipp::malloc<TypeParam>(9);
    
    TypeParam taps[5] = {1., 2., 3., 4., 5.};
    for(int i = 0; i < 9; ++i){
        buf0[i] = 1;
        buf1[i] = 1;
        buf2[i] = 1;
        buf3[i] = 1;
    }

    ipp::fir_mr<TypeParam> sr(taps, 5, 2, 0, 3, 0);

    sr.filter(buf0, buf2, 3); //fetch 3, output 2 each iteration
    sr.filter(buf1, buf3, 3);

    EXPECT_EQ(buf2[0], 1);
    EXPECT_EQ(buf2[1], 6);
    EXPECT_EQ(buf2[2], 9);
    EXPECT_EQ(buf3[0], 9);
    EXPECT_EQ(buf3[1], 6);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
    ipp::free(buf3);
}


REGISTER_TYPED_TEST_CASE_P(FIRMRTest, 
        SanitCheck);
typedef testing::Types<
                       float,
                       double
                       >FIRMRTestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPFIRMRTest, FIRMRTest, FIRMRTestTypes);



///////PolyphaseResample////
template<typename T>
class PolyphaseResampleTest : public testing::Test
{
};

//
TYPED_TEST_CASE_P(PolyphaseResampleTest);

TYPED_TEST_P(PolyphaseResampleTest, SanitCheck)
{
    TypeParam *buf0 = (TypeParam*)ipp::malloc<TypeParam>(65536);
    TypeParam *buf1 = (TypeParam*)ipp::malloc<TypeParam>(65536);
    TypeParam *buf2 = (TypeParam*)ipp::malloc<TypeParam>(65536);
    TypeParam *buf3 = (TypeParam*)ipp::malloc<TypeParam>(65536);
    TypeParam *buf4 = (TypeParam*)ipp::malloc<TypeParam>(65536);

	for (int i = 0; i < 65536; ++i){
		//buf0[i] = i > 3 ? TypeParam(i) : 0;
		buf0[i] = TypeParam((i / 2) % 32);
		buf1[i] = TypeParam((i / 2) % 32);
		buf2[i] = 0;
		buf3[i] = 0;
		buf4[i] = 0;
	}

	//buf0[14] = 1000;

    float inRate = 17.f;
    float outRate = 3.f;
    float a = inRate / outRate;
	int nstep = a > 1 / a ? int(a) : int(1 / a) ;
    //float alpha = 9.f;
    float alpha = 3.3953f;
    float rollf = 0.8f;
    float As = 40.f;
    int N = int((As - 8) / (2.285 * (1 - rollf) / nstep * 3.1415926) + 0.5);
	float win = N / float(nstep);

	int history1 = (int)(64.0f*0.5*IPP_MAX(1.0, 1.0 / (double)outRate / (double)inRate)) + 1;
	int history = N;

    ipp::polyphase_resampling<TypeParam> pr(win, nstep, rollf, alpha);
    ipp::polyphase_resampling_fixed<TypeParam> prf((int)inRate, (int)outRate, N, rollf, alpha);

	int olen = 0, olenf = 0;
	double ti = history, tif = history;
	pr.resample (buf0, 30, buf2, &olen, &ti, 1. / a, 1.f);
	prf.resample(buf1, 30, buf3, &olenf, &tif, 1.f);

	ipp::sub(buf2, buf3, buf4, 200);

    ipp::free(buf0);
    ipp::free(buf1);
    ipp::free(buf2);
    ipp::free(buf3);
}


REGISTER_TYPED_TEST_CASE_P(PolyphaseResampleTest, 
        SanitCheck);
typedef testing::Types<
                       float
                       >PolyphaseResampleTestTypes;

INSTANTIATE_TYPED_TEST_CASE_P(MTPPolyphaseResampleTest, PolyphaseResampleTest, PolyphaseResampleTestTypes);


class FIRTapEstimateTest : public testing::Test
{
};

//
TEST_F(FIRTapEstimateTest, SanitCheck)
{
    EXPECT_EQ(
            ipp::fir_tap_estimate(1.0471975512, 1.15191730632, 0.0114469, 0.01778279, ipp::FIR_HERMANN), 106); 

    EXPECT_EQ(
            ipp::fir_tap_estimate(1.0471975512, 1.15191730632, 0.01778279, 0.0114469, ipp::FIR_HERMANN), 105); 

    EXPECT_EQ(
            ipp::fir_tap_estimate(1.0471975512, 1.15191730632, 0.01778279, 0.0114469, ipp::FIR_KAISER), 99); 

    EXPECT_EQ(
            ipp::fir_tap_estimate(1.0471975512, 1.15191730632, 0.01778279, 0.0114469, ipp::FIR_BELLANGER), 107); 


}


}
