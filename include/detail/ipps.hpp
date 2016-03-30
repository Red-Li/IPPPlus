/**
 * @file ipps.hpp
 * @Brief 
 * @author Red Li
 * @version 
 * @date 2014-12-26
 */


#ifndef IPPPLUS_DETAIL_IPPS_HPP
#define IPPPLUS_DETAIL_IPPS_HPP


namespace ipp{
namespace detail{

//
template<typename T, int Tid, size_t Size>
struct copy;


template<typename T>
struct copy<T, TYPE_CAT_INT, 1>
{
    static inline IppStatus do_copy(const T* src, T *dst, int len)
    {
        return ippsCopy_8u((const Ipp8u*)src, (Ipp8u*)dst, len);
    };
};

template<typename T>
struct copy<T, TYPE_CAT_INT, 2>
{
    static inline IppStatus do_copy(const T* src, T *dst, int len)
    {
        return ippsCopy_16s((const Ipp16s*)src, (Ipp16s*)dst, len);
    };
};

template<typename T>
struct copy<T, TYPE_CAT_INT, 4>
{
    static inline IppStatus do_copy(const T* src, T *dst, int len)
    {
        return ippsCopy_32s((const Ipp32s*)src, (Ipp32s*)dst, len);
    };
};

template<typename T>
struct copy<T, TYPE_CAT_INT, 8>
{
    static inline IppStatus do_copy(const T* src, T *dst, int len)
    {
        return ippsCopy_64s((const Ipp64s*)src, (Ipp64s*)dst, len);
    };
};

template<typename T>
struct copy<T, TYPE_CAT_FLOAT, 4>
{
    static inline IppStatus do_copy(const T* src, T *dst, int len)
    {
        return ippsCopy_32f((const Ipp32f*)src, (Ipp32f*)dst, len);
    };
};

template<typename T>
struct copy<T, TYPE_CAT_FLOAT, 8>
{
    static inline IppStatus do_copy(const T* src, T *dst, int len)
    {
        return ippsCopy_64f((const Ipp64f*)src, (Ipp64f*)dst, len);
    };
};


template<typename T>
struct copy<T, TYPE_CAT_COMPLEX, 8>
{
    static inline IppStatus do_copy(const T* src, T *dst, int len)
    {
        return ippsCopy_32fc((const Ipp32fc*)src, (Ipp32fc*)dst, len);
    };
};

template<typename T>
struct copy<T, TYPE_CAT_COMPLEX, 16>
{
    static inline IppStatus do_copy(const T* src, T *dst, int len)
    {
        return ippsCopy_64fc((const Ipp64fc*)src, (Ipp64fc*)dst, len);
    };
};


template<typename T, int Tid, size_t Size>
struct move;


template<typename T>
struct move<T, TYPE_CAT_INT, 1>
{
    static inline IppStatus do_move(const T* src, T *dst, int len)
    {
        return ippsMove_8u((const Ipp8u*)src, (Ipp8u*)dst, len);
    };
};

template<typename T>
struct move<T, TYPE_CAT_INT, 2>
{
    static inline IppStatus do_move(const T* src, T *dst, int len)
    {
        return ippsMove_16s((const Ipp16s*)src, (Ipp16s*)dst, len);
    };
};

template<typename T>
struct move<T, TYPE_CAT_INT, 4>
{
    static inline IppStatus do_move(const T* src, T *dst, int len)
    {
        return ippsMove_32s((const Ipp32s*)src, (Ipp32s*)dst, len);
    };
};

template<typename T>
struct move<T, TYPE_CAT_INT, 8>
{
    static inline IppStatus do_move(const T* src, T *dst, int len)
    {
        return ippsMove_64s((const Ipp64s*)src, (Ipp64s*)dst, len);
    };
};

template<typename T>
struct move<T, TYPE_CAT_FLOAT, 4>
{
    static inline IppStatus do_move(const T* src, T *dst, int len)
    {
        return ippsMove_32f((const Ipp32f*)src, (Ipp32f*)dst, len);
    };
};

template<typename T>
struct move<T, TYPE_CAT_FLOAT, 8>
{
    static inline IppStatus do_move(const T* src, T *dst, int len)
    {
        return ippsMove_64f((const Ipp64f*)src, (Ipp64f*)dst, len);
    };
};


template<typename T>
struct move<T, TYPE_CAT_COMPLEX, 8>
{
    static inline IppStatus do_move(const T* src, T *dst, int len)
    {
        return ippsMove_32fc((const Ipp32fc*)src, (Ipp32fc*)dst, len);
    };
};

template<typename T>
struct move<T, TYPE_CAT_COMPLEX, 16>
{
    static inline IppStatus do_move(const T* src, T *dst, int len)
    {
        return ippsMove_64fc((const Ipp64fc*)src, (Ipp64fc*)dst, len);
    };
};


//set
template<typename IT>
struct set;

#define SET_ASM(Suffix)\
template<>\
struct set<Ipp##Suffix>\
{\
    typedef Ipp##Suffix itype;\
    static inline IppStatus do_set(itype val, itype *dst, int len)\
    {\
        return ippsSet_##Suffix(val, dst, len);\
    }\
}

template<>
struct set<Ipp8s>
{
    typedef Ipp8s itype;
    static inline IppStatus do_set(itype val, itype *dst, int len)
    {
        return ippsSet_8u(*(Ipp8u*)&val, (Ipp8u*)dst, len);
    }
};

template<>
struct set<Ipp16u>
{
    typedef Ipp16u itype;
    static inline IppStatus do_set(itype val, itype *dst, int len)
    {
        return ippsSet_16s(*(Ipp16s*)&val, (Ipp16s*)dst, len);
    }
};

template<>
struct set<Ipp32u>
{
    typedef Ipp32u itype;
    static inline IppStatus do_set(itype val, itype *dst, int len)
    {
        return ippsSet_32s(*(Ipp32s*)&val, (Ipp32s*)dst, len);
    }
};

template<>
struct set<Ipp64u>
{
    typedef Ipp64u itype;
    static inline IppStatus do_set(itype val, itype *dst, int len)
    {
        return ippsSet_64s(*(Ipp64s*)&val, (Ipp64s*)dst, len);
    }
};

SET_ASM(8u);
SET_ASM(16s);
SET_ASM(32s);
SET_ASM(64s);
SET_ASM(32f);
SET_ASM(64f);
SET_ASM(16sc);
SET_ASM(32sc);
SET_ASM(64sc);
SET_ASM(32fc);
SET_ASM(64fc);

#undef SET_ASM

//zero
template<typename IT>
struct zero;

#define ZERO_ASM(Suffix)\
template<>\
struct zero<Ipp##Suffix>\
{\
    typedef Ipp##Suffix itype;\
    static inline IppStatus do_zero(itype *dst, int len)\
    {\
        return ippsZero_##Suffix(dst, len);\
    }\
}

template<>
struct zero<Ipp8s>
{
    typedef Ipp8s itype;
    static inline IppStatus do_zero(itype *dst, int len)
    {
        return ippsZero_8u((Ipp8u*)dst, len);
    }
};

template<>
struct zero<Ipp16u>
{
    typedef Ipp16u itype;
    static inline IppStatus do_zero(itype *dst, int len)
    {
        return ippsZero_16s((Ipp16s*)dst, len);
    }
};

template<>
struct zero<Ipp32u>
{
    typedef Ipp32u itype;
    static inline IppStatus do_zero(itype *dst, int len)
    {
        return ippsZero_32s((Ipp32s*)dst, len);
    }
};

template<>
struct zero<Ipp64u>
{
    typedef Ipp64u itype;
    static inline IppStatus do_zero(itype *dst, int len)
    {
        return ippsZero_64s((Ipp64s*)dst, len);
    }
};

ZERO_ASM(8u);
ZERO_ASM(16s);
ZERO_ASM(32s);
ZERO_ASM(64s);
ZERO_ASM(32f);
ZERO_ASM(64f);
ZERO_ASM(32fc);
ZERO_ASM(64fc);

#undef ZERO_ASM


template<typename T>
static inline IppStatus do_rand_uniform_get_size(int *pRandUniStateSize);

template<>
static inline IppStatus do_rand_uniform_get_size<Ipp8u>(int *pRandUniStateSize)
{
    return ippsRandUniformGetSize_8u(pRandUniStateSize);
}
template<>
static inline IppStatus do_rand_uniform_get_size<Ipp16s>(int *pRandUniStateSize)
{
    return ippsRandUniformGetSize_16s(pRandUniStateSize);
}
template<>
static inline IppStatus do_rand_uniform_get_size<Ipp32f>(int *pRandUniStateSize)
{
    return ippsRandUniformGetSize_32f(pRandUniStateSize);
}


template<typename T>
static inline IppStatus do_rand_uniform_init(
        void *state, T low, T high, unsigned int seed); 


template<>
static inline IppStatus do_rand_uniform_init<Ipp8u>(
        void *state, Ipp8u low, Ipp8u high, unsigned int seed)
{
    return ippsRandUniformInit_8u(
            (IppsRandUniState_8u*)state, low, high, seed);
}
template<>
static inline IppStatus do_rand_uniform_init<Ipp16s>(
        void *state, Ipp16s low, Ipp16s high, unsigned int seed)
{
    return ippsRandUniformInit_16s(
            (IppsRandUniState_16s*)state, low, high, seed);
}
template<>
static inline IppStatus do_rand_uniform_init<Ipp32f>(
        void *state, Ipp32f low, Ipp32f high, unsigned int seed)
{
    return ippsRandUniformInit_32f(
            (IppsRandUniState_32f*)state, low, high, seed);
}


template<typename T>
static inline IppStatus do_rand_uniform(
        T *dst, int len, void *state);

template<>
static inline IppStatus do_rand_uniform<Ipp8u>(
        Ipp8u *dst, int len, void *state)
{
    return ippsRandUniform_8u(
            dst, len, (IppsRandUniState_8u*)state);
}
template<>
static inline IppStatus do_rand_uniform<Ipp16s>(
        Ipp16s *dst, int len, void *state)
{
    return ippsRandUniform_16s(
            dst, len, (IppsRandUniState_16s*)state);
}
template<>
static inline IppStatus do_rand_uniform<Ipp32f>(
        Ipp32f *dst, int len, void *state)
{
    return ippsRandUniform_32f(
            dst, len, (IppsRandUniState_32f*)state);
}


////
template<typename T>
static inline IppStatus do_rand_gauss_get_size(int *pRandGaussStateSize);

template<>
static inline IppStatus do_rand_gauss_get_size<Ipp8u>(int *pRandGaussStateSize)
{
    return ippsRandGaussGetSize_8u(pRandGaussStateSize);
}
template<>
static inline IppStatus do_rand_gauss_get_size<Ipp16s>(int *pRandGaussStateSize)
{
    return ippsRandGaussGetSize_16s(pRandGaussStateSize);
}
template<>
static inline IppStatus do_rand_gauss_get_size<Ipp32f>(int *pRandGaussStateSize)
{
    return ippsRandGaussGetSize_32f(pRandGaussStateSize);
}


template<typename T>
static inline IppStatus do_rand_gauss_init(
        void *state, T mean, T std_dev, unsigned int seed); 


template<>
static inline IppStatus do_rand_gauss_init<Ipp8u>(
        void *state, Ipp8u mean, Ipp8u std_dev, unsigned int seed)
{
    return ippsRandGaussInit_8u(
            (IppsRandGaussState_8u*)state, mean, std_dev, seed);
}
template<>
static inline IppStatus do_rand_gauss_init<Ipp16s>(
        void *state, Ipp16s mean, Ipp16s std_dev, unsigned int seed)
{
    return ippsRandGaussInit_16s(
            (IppsRandGaussState_16s*)state, mean, std_dev, seed);
}
template<>
static inline IppStatus do_rand_gauss_init<Ipp32f>(
        void *state, Ipp32f mean, Ipp32f std_dev, unsigned int seed)
{
    return ippsRandGaussInit_32f(
            (IppsRandGaussState_32f*)state, mean, std_dev, seed);
}


template<typename T>
static inline IppStatus do_rand_gauss(
        T *dst, int len, void *state);

template<>
static inline IppStatus do_rand_gauss<Ipp8u>(
        Ipp8u *dst, int len, void *state)
{
    return ippsRandGauss_8u(
            dst, len, (IppsRandGaussState_8u*)state);
}
template<>
static inline IppStatus do_rand_gauss<Ipp16s>(
        Ipp16s *dst, int len, void *state)
{
    return ippsRandGauss_16s(
            dst, len, (IppsRandGaussState_16s*)state);
}
template<>
static inline IppStatus do_rand_gauss<Ipp32f>(
        Ipp32f *dst, int len, void *state)
{
    return ippsRandGauss_32f(
            dst, len, (IppsRandGaussState_32f*)state);
}



///////
template<typename IT>
struct vector_jaehne;

#define VECTOR_JAEHNE_ASM(Suffix)\
template<>\
struct vector_jaehne<Ipp##Suffix>\
{\
    typedef Ipp##Suffix itype;\
    static inline IppStatus do_vector_jaehne(\
            itype *dst, int len, itype magn)\
    {\
        return ippsVectorJaehne_##Suffix(dst, len, magn);\
    }\
}

VECTOR_JAEHNE_ASM(8u);
VECTOR_JAEHNE_ASM(16u);
VECTOR_JAEHNE_ASM(16s);
VECTOR_JAEHNE_ASM(32s);
VECTOR_JAEHNE_ASM(32f);
VECTOR_JAEHNE_ASM(64f);

#undef VECTOR_JAEHNE_ASM

template<typename IT>
struct vector_slope;

#define VECTOR_SLOPE_ASM(Suffix)\
template<>\
struct vector_slope<Ipp##Suffix>\
{\
    typedef Ipp##Suffix itype;\
    static inline IppStatus do_vector_slope(\
            itype *dst, int len, double offset, double slope)\
    {\
        return ippsVectorSlope_##Suffix(\
                dst, len, (Ipp32f)offset, (Ipp32f)slope);\
    }\
}

#define VECTOR_SLOPE_ASM_D(Suffix)\
template<>\
struct vector_slope<Ipp##Suffix>\
{\
    typedef Ipp##Suffix itype;\
    static inline IppStatus do_vector_slope(\
            itype *dst, int len, double offset, double slope)\
    {\
        return ippsVectorSlope_##Suffix(\
                dst, len, (Ipp64f)offset, (Ipp64f)slope);\
    }\
}

VECTOR_SLOPE_ASM(8u);
VECTOR_SLOPE_ASM(16u);
VECTOR_SLOPE_ASM(16s);
VECTOR_SLOPE_ASM_D(32u);
VECTOR_SLOPE_ASM_D(32s);
VECTOR_SLOPE_ASM(32f);
VECTOR_SLOPE_ASM_D(64f);

#undef VECTOR_SLOPE_ASM_D
#undef VECTOR_SLOPE_ASM

///// and const /////////
template<typename T>
static inline IppStatus and_const(const T*, T, T*, int);

#define AND_CONST_ASM(Suffix)\
template<>\
static inline IppStatus and_const<Ipp##Suffix>(const Ipp##Suffix *src, \
                                  Ipp##Suffix val,\
                                  Ipp##Suffix* dst,\
                                  int len)\
{\
    return src == dst ? ippsAndC_##Suffix##_I(val, dst, len)\
                      : ippsAndC_##Suffix(src, val, dst, len);\
}

AND_CONST_ASM(8u);
AND_CONST_ASM(16u);
AND_CONST_ASM(32u);


#undef AND_CONST_ASM


///// or const /////////
template<typename T>
static inline IppStatus or_const(const T*, T, T*, int);

#define OR_CONST_ASM(Suffix)\
template<>\
static inline IppStatus or_const<Ipp##Suffix>(const Ipp##Suffix *src, \
                                  Ipp##Suffix val,\
                                  Ipp##Suffix* dst,\
                                  int len)\
{\
    return src == dst ? ippsOrC_##Suffix##_I(val, dst, len)\
                      : ippsOrC_##Suffix(src, val, dst, len);\
}

OR_CONST_ASM(8u);
OR_CONST_ASM(16u);
OR_CONST_ASM(32u);


#undef OR_CONST_ASM



///// xor const /////////

template<typename T>
static inline IppStatus xor_const(const T*, T, T*, int);

#define XOR_CONST_ASM(Suffix)\
template<>\
static inline IppStatus xor_const<Ipp##Suffix>(const Ipp##Suffix *src, \
                                  Ipp##Suffix val,\
                                  Ipp##Suffix* dst,\
                                  int len)\
{\
    return src == dst ? ippsXorC_##Suffix##_I(val, dst, len)\
                      : ippsXorC_##Suffix(src, val, dst, len);\
}

XOR_CONST_ASM(8u);
XOR_CONST_ASM(16u);
XOR_CONST_ASM(32u);


#undef XOR_CONST_ASM


///// and /////////

template<typename T>
static inline IppStatus and(const T*, const T*, T*, int);

#define AND_ASM(Suffix)\
template<>\
static inline IppStatus and<Ipp##Suffix>(const Ipp##Suffix *src1, \
                            const Ipp##Suffix *src2,\
                                  Ipp##Suffix* dst,\
                                  int len)\
{\
    return src1 == dst ? ippsAnd_##Suffix##_I(src2, dst, len)\
                       : (src2 == dst ? ippsAnd_##Suffix##_I(src1, dst, len)\
                         : ippsAnd_##Suffix(src1, src2, dst, len));\
}

AND_ASM(8u);
AND_ASM(16u);
AND_ASM(32u);

#undef AND_ASM


///// or /////////

template<typename T>
static inline IppStatus or(const T*, const T*, T*, int);

#define OR_ASM(Suffix)\
template<>\
static inline IppStatus or<Ipp##Suffix>(const Ipp##Suffix *src1, \
                            const Ipp##Suffix *src2,\
                                  Ipp##Suffix* dst,\
                                  int len)\
{\
    return src1 == dst ? ippsOr_##Suffix##_I(src2, dst, len)\
                       : (src2 == dst ? ippsOr_##Suffix##_I(src1, dst, len)\
                         : ippsOr_##Suffix(src1, src2, dst, len));\
}

OR_ASM(8u);
OR_ASM(16u);
OR_ASM(32u);

#undef OR_ASM

///// xor /////////

template<typename T>
static inline IppStatus xor(const T*, const T*, T*, int);

#define XOR_ASM(Suffix)\
template<>\
static inline IppStatus xor<Ipp##Suffix>(const Ipp##Suffix *src1, \
                            const Ipp##Suffix *src2,\
                                  Ipp##Suffix* dst,\
                                  int len)\
{\
    return src1 == dst ? ippsXor_##Suffix##_I(src2, dst, len)\
                       : (src2 == dst ? ippsXor_##Suffix##_I(src1, dst, len)\
                         : ippsXor_##Suffix(src1, src2, dst, len));\
}

XOR_ASM(8u);
XOR_ASM(16u);
XOR_ASM(32u);

#undef XOR_ASM

///// not /////////

template<typename T>
static inline IppStatus not(const T*, T*, int);

#define NOT_ASM(Suffix)\
template<>\
static inline IppStatus not<Ipp##Suffix>(const Ipp##Suffix *src, \
                                  Ipp##Suffix* dst,\
                                  int len)\
{\
    return src == dst ? ippsNot_##Suffix##_I(dst, len)\
                      : ippsNot_##Suffix(src, dst, len);\
}

NOT_ASM(8u);
NOT_ASM(16u);
NOT_ASM(32u);

#undef NOT_ASM


///// lshift /////////

template<typename T>
static inline IppStatus lshift_const(const T*, int, T*, int);

#define LSHIFT_ASM(Suffix)\
template<>\
static inline IppStatus lshift_const<Ipp##Suffix>(const Ipp##Suffix *src, \
                                  int val,\
                                  Ipp##Suffix* dst,\
                                  int len)\
{\
    return src == dst ? ippsLShiftC_##Suffix##_I(val, dst, len)\
                      : ippsLShiftC_##Suffix(src, val, dst, len);\
}

LSHIFT_ASM(8u);
LSHIFT_ASM(16u);
LSHIFT_ASM(16s);
LSHIFT_ASM(32s);

#undef LSHIFT_ASM

///// rshift /////////

template<typename T>
static inline IppStatus rshift_const(const T*, int, T*, int);

#define RSHIFT_ASM(Suffix)\
template<>\
static inline IppStatus rshift_const<Ipp##Suffix>(const Ipp##Suffix *src, \
                                  int val,\
                                  Ipp##Suffix* dst,\
                                  int len)\
{\
    return src == dst ? ippsRShiftC_##Suffix##_I(val, dst, len)\
                      : ippsRShiftC_##Suffix(src, val, dst, len);\
}

RSHIFT_ASM(8u);
RSHIFT_ASM(16u);
RSHIFT_ASM(16s);
RSHIFT_ASM(32s);

#undef RSHIFT_ASM


/////// add_const /////////
template<typename T>
static inline IppStatus add_const(const T *, T, T *, int, int);


#define ADD_CONST_ASM(Suffix)\
template<>\
static inline IppStatus add_const<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return src == dst ? ippsAddC_##Suffix##_I(val, dst, len)\
                      : ippsAddC_##Suffix(src, val, dst, len);\
}


#define ADD_CONST_SFS_ASM(Suffix)\
template<>\
static inline IppStatus add_const<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return src == dst ? ippsAddC_##Suffix##_ISfs(val, dst, len, scale)\
                      : ippsAddC_##Suffix##_Sfs(src, val, dst, len, scale);\
}


ADD_CONST_ASM(32f);
ADD_CONST_ASM(64f);
ADD_CONST_ASM(32fc);
ADD_CONST_ASM(64fc);

ADD_CONST_SFS_ASM(8u);
ADD_CONST_SFS_ASM(16u);
ADD_CONST_SFS_ASM(16s);
ADD_CONST_SFS_ASM(32s);
ADD_CONST_SFS_ASM(16sc);
ADD_CONST_SFS_ASM(32sc);

#undef ADD_CONST_ASM
#undef ADD_CONST_SFS_ASM


template<typename T>
static inline IppStatus add_product_const(
        const T*, T, T *, int);


template<>
static inline IppStatus add_product_const<Ipp32f>(
        const Ipp32f *src, Ipp32f val, Ipp32f *dst, int len)
{
    return ippsAddProductC_32f(src, val, dst, len);
}


/////// mul_const /////////
template<typename T>
static inline IppStatus mul_const(const T *, T, T *, int, int);


#define MUL_CONST_ASM(Suffix)\
template<>\
static inline IppStatus mul_const<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return src == dst ? ippsMulC_##Suffix##_I(val, dst, len)\
                      : ippsMulC_##Suffix(src, val, dst, len);\
}


#define MUL_CONST_SFS_ASM(Suffix)\
template<>\
static inline IppStatus mul_const<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return src == dst ? ippsMulC_##Suffix##_ISfs(val, dst, len, scale)\
                      : ippsMulC_##Suffix##_Sfs(src, val, dst, len, scale);\
}


MUL_CONST_ASM(32f);
MUL_CONST_ASM(64f);
MUL_CONST_ASM(32fc);
MUL_CONST_ASM(64fc);

MUL_CONST_SFS_ASM(8u);
MUL_CONST_SFS_ASM(16u);
MUL_CONST_SFS_ASM(16s);
MUL_CONST_SFS_ASM(32s);
MUL_CONST_SFS_ASM(16sc);
MUL_CONST_SFS_ASM(32sc);

#undef MUL_CONST_ASM
#undef MUL_CONST_SFS_ASM

/////// sub_const /////////
template<typename T>
static inline IppStatus sub_const(const T *, T, T *, int, int);


#define SUB_CONST_ASM(Suffix)\
template<>\
static inline IppStatus sub_const<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return src == dst ? ippsSubC_##Suffix##_I(val, dst, len)\
                      : ippsSubC_##Suffix(src, val, dst, len);\
}


#define SUB_CONST_SFS_ASM(Suffix)\
template<>\
static inline IppStatus sub_const<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return src == dst ? ippsSubC_##Suffix##_ISfs(val, dst, len, scale)\
                      : ippsSubC_##Suffix##_Sfs(src, val, dst, len, scale);\
}


SUB_CONST_ASM(32f);
SUB_CONST_ASM(64f);
SUB_CONST_ASM(32fc);
SUB_CONST_ASM(64fc);

SUB_CONST_SFS_ASM(8u);
SUB_CONST_SFS_ASM(16u);
SUB_CONST_SFS_ASM(16s);
SUB_CONST_SFS_ASM(32s);
SUB_CONST_SFS_ASM(16sc);
SUB_CONST_SFS_ASM(32sc);

#undef SUB_CONST_ASM
#undef SUB_CONST_SFS_ASM

/////// sub_const_rev /////////
template<typename T>
static inline IppStatus sub_const_rev(const T *, T, T *, int, int);


#define SUB_CONST_REV_ASM(Suffix)\
template<>\
static inline IppStatus sub_const_rev<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return src == dst ? ippsSubCRev_##Suffix##_I(val, dst, len)\
                      : ippsSubCRev_##Suffix(src, val, dst, len);\
}


#define SUB_CONST_REV_SFS_ASM(Suffix)\
template<>\
static inline IppStatus sub_const_rev<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return src == dst ? ippsSubCRev_##Suffix##_ISfs(val, dst, len, scale)\
                      : ippsSubCRev_##Suffix##_Sfs(src, val, dst, len, scale);\
}


SUB_CONST_REV_ASM(32f);
SUB_CONST_REV_ASM(64f);
SUB_CONST_REV_ASM(32fc);
SUB_CONST_REV_ASM(64fc);

SUB_CONST_REV_SFS_ASM(8u);
SUB_CONST_REV_SFS_ASM(16u);
SUB_CONST_REV_SFS_ASM(16s);
SUB_CONST_REV_SFS_ASM(32s);
SUB_CONST_REV_SFS_ASM(16sc);
SUB_CONST_REV_SFS_ASM(32sc);

#undef SUB_CONST_REV_ASM
#undef SUB_CONST_REV_SFS_ASM


/////// div_const /////////
template<typename T>
static inline IppStatus div_const(const T *, T, T *, int, int);


#define DIV_CONST_ASM(Suffix)\
template<>\
static inline IppStatus div_const<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return src == dst ? ippsDivC_##Suffix##_I(val, dst, len)\
                      : ippsDivC_##Suffix(src, val, dst, len);\
}


#define DIV_CONST_SFS_ASM(Suffix)\
template<>\
static inline IppStatus div_const<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return src == dst ? ippsDivC_##Suffix##_ISfs(val, dst, len, scale)\
                      : ippsDivC_##Suffix##_Sfs(src, val, dst, len, scale);\
}


DIV_CONST_ASM(32f);
DIV_CONST_ASM(64f);
DIV_CONST_ASM(32fc);
DIV_CONST_ASM(64fc);

DIV_CONST_SFS_ASM(8u);
DIV_CONST_SFS_ASM(16u);
DIV_CONST_SFS_ASM(16s);
DIV_CONST_SFS_ASM(16sc);

#undef DIV_CONST_ASM
#undef DIV_CONST_SFS_ASM


/////// div_const_rev /////////
template<typename T>
static inline IppStatus div_const_rev(const T *, T, T *, int);


#define DIV_CONST_REV_ASM(Suffix)\
template<>\
static inline IppStatus div_const_rev<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len)\
{\
    return src == dst ? ippsDivCRev_##Suffix##_I(val, dst, len)\
                      : ippsDivCRev_##Suffix(src, val, dst, len);\
}


#define DIV_CONST_REV_SFS_ASM(Suffix)\
template<>\
static inline IppStatus div_const_rev<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix val,\
                                  Ipp##Suffix *dst,\
                                  int len)\
{\
    return src == dst ? ippsDivCRev_##Suffix##_I(val, dst, len)\
                      : ippsDivCRev_##Suffix##(src, val, dst, len);\
}


DIV_CONST_REV_ASM(32f);

DIV_CONST_REV_SFS_ASM(16u);

#undef DIV_CONST_REV_ASM
#undef DIV_CONST_REV_SFS_ASM


/////// add /////////
template<typename T>
static inline IppStatus add(const T *, const T*, T *, int, int);


#define ADD_ASM(Suffix)\
template<>\
static inline IppStatus add<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return src1 == dst ? ippsAdd_##Suffix##_I(src2, dst, len)\
                      : (src2 == dst ? ippsAdd_##Suffix##_I(src1, dst, len)\
                                     : ippsAdd_##Suffix(src1, src2, dst, len));\
}


#define ADD_SFS_ASM(Suffix)\
template<>\
static inline IppStatus add<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return src1 == dst ? ippsAdd_##Suffix##_ISfs(src2, dst, len, scale)\
                      : (src2 == dst ? ippsAdd_##Suffix##_ISfs(src1, dst, len, scale)\
                                     : ippsAdd_##Suffix##_Sfs(src1, src2, dst, len, scale));\
}


ADD_ASM(32f);
ADD_ASM(64f);
ADD_ASM(32fc);
ADD_ASM(64fc);

ADD_SFS_ASM(8u);
ADD_SFS_ASM(16u);
ADD_SFS_ASM(16s);
ADD_SFS_ASM(32s);
ADD_SFS_ASM(16sc);
ADD_SFS_ASM(32sc);

#undef ADD_ASM
#undef ADD_SFS_ASM


/////// add product /////////
template<typename T>
static inline IppStatus add_product(const T *, const T*, T *, int, int);


#define ADD_PRODUCT_ASM(Suffix)\
template<>\
static inline IppStatus add_product<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return ippsAddProduct_##Suffix##(src1, src2, dst, len);\
}


#define ADD_PRODUCT_SFS_ASM(Suffix)\
template<>\
static inline IppStatus add_product<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return ippsAddProduct_##Suffix##_Sfs(src1, src2, dst, len, scale);\
}


ADD_PRODUCT_ASM(32f);
ADD_PRODUCT_ASM(64f);
ADD_PRODUCT_ASM(32fc);
ADD_PRODUCT_ASM(64fc);

ADD_PRODUCT_SFS_ASM(16s);
ADD_PRODUCT_SFS_ASM(32s);

#undef ADD_PRODUCT_ASM
#undef ADD_PRODUCT_SFS_ASM



/////// mul /////////
template<typename T>
static inline IppStatus mul(const T *, const T*, T *, int, int);


#define MUL_ASM(Suffix)\
template<>\
static inline IppStatus mul<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return src1 == dst ? ippsMul_##Suffix##_I(src2, dst, len)\
                      : (src2 == dst ? ippsMul_##Suffix##_I(src1, dst, len)\
                                     : ippsMul_##Suffix(src1, src2, dst, len));\
}


#define MUL_SFS_ASM(Suffix)\
template<>\
static inline IppStatus mul<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return src1 == dst ? ippsMul_##Suffix##_ISfs(src2, dst, len, scale)\
                      : (src2 == dst ? ippsMul_##Suffix##_ISfs(src1, dst, len, scale)\
                                     : ippsMul_##Suffix##_Sfs(src1, src2, dst, len, scale));\
}


MUL_ASM(32f);
MUL_ASM(64f);
MUL_ASM(32fc);
MUL_ASM(64fc);

MUL_SFS_ASM(8u);
MUL_SFS_ASM(16u);
MUL_SFS_ASM(16s);
MUL_SFS_ASM(32s);
MUL_SFS_ASM(16sc);
MUL_SFS_ASM(32sc);

#undef MUL_ASM
#undef MUL_SFS_ASM

/////// sub /////////
template<typename T>
static inline IppStatus sub(const T *, const T*, T *, int, int);


#define SUB_ASM(Suffix)\
template<>\
static inline IppStatus sub<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return src1 == dst ? ippsSub_##Suffix##_I(src2, dst, len)\
                      : (src2 == dst ? ippsSub_##Suffix##_I(src1, dst, len)\
                                     : ippsSub_##Suffix(src1, src2, dst, len));\
}


#define SUB_SFS_ASM(Suffix)\
template<>\
static inline IppStatus sub<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return src1 == dst ? ippsSub_##Suffix##_ISfs(src2, dst, len, scale)\
                      : (src2 == dst ? ippsSub_##Suffix##_ISfs(src1, dst, len, scale)\
                                     : ippsSub_##Suffix##_Sfs(src1, src2, dst, len, scale));\
}


SUB_ASM(32f);
SUB_ASM(64f);
SUB_ASM(32fc);
SUB_ASM(64fc);

SUB_SFS_ASM(8u);
SUB_SFS_ASM(16u);
SUB_SFS_ASM(16s);
SUB_SFS_ASM(32s);
SUB_SFS_ASM(16sc);
SUB_SFS_ASM(32sc);

#undef SUB_ASM
#undef SUB_SFS_ASM


/////// div /////////
template<typename T>
static inline IppStatus div(const T *, const T*, T *, int, int);


#define DIV_ASM(Suffix)\
template<>\
static inline IppStatus div<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int )\
{\
    return src1 == dst ? ippsDiv_##Suffix##_I(src2, dst, len)\
                      : (src2 == dst ? ippsDiv_##Suffix##_I(src1, dst, len)\
                                     : ippsDiv_##Suffix(src1, src2, dst, len));\
}


#define DIV_SFS_ASM(Suffix)\
template<>\
static inline IppStatus div<Ipp##Suffix>(\
                                  const Ipp##Suffix *src1,\
                                  const Ipp##Suffix *src2,\
                                  Ipp##Suffix *dst,\
                                  int len,\
                                  int scale)\
{\
    return src1 == dst ? ippsDiv_##Suffix##_ISfs(src2, dst, len, scale)\
                      : (src2 == dst ? ippsDiv_##Suffix##_ISfs(src1, dst, len, scale)\
                                     : ippsDiv_##Suffix##_Sfs(src1, src2, dst, len, scale));\
}


DIV_ASM(32f);
DIV_ASM(64f);
DIV_ASM(32fc);
DIV_ASM(64fc);

DIV_SFS_ASM(8u);
DIV_SFS_ASM(16u);
DIV_SFS_ASM(16s);
DIV_SFS_ASM(32s);
DIV_SFS_ASM(16sc);

#undef DIV_ASM
#undef DIV_SFS_ASM

/////// abs /////////
template<typename T>
static inline IppStatus abs(const T *, T *, int);


#define ABS_ASM(Suffix)\
template<>\
static inline IppStatus abs<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix *dst,\
                                  int len)\
{\
    return src == dst ? ippsAbs_##Suffix##_I(dst, len)\
                      : ippsAbs_##Suffix(src, dst, len);\
}

ABS_ASM(16s);
ABS_ASM(32s);
ABS_ASM(32f);
ABS_ASM(64f);

#undef ABS_ASM


/////// sqr /////////
template<typename T>
static inline IppStatus sqr(const T *, T *, int, int);


#define SQR_ASM(Suffix)\
template<>\
static inline IppStatus sqr<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix *dst,\
                                  int len, int)\
{\
    return src == dst ? ippsSqr_##Suffix##_I(dst, len)\
                      : ippsSqr_##Suffix(src, dst, len);\
}


#define SQR_SFS_ASM(Suffix)\
template<>\
static inline IppStatus sqr<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix *dst,\
                                  int len, int scale)\
{\
    return src == dst ? ippsSqr_##Suffix##_ISfs(dst, len, scale)\
                      : ippsSqr_##Suffix##_Sfs(src, dst, len, scale);\
}

SQR_ASM(32f);
SQR_ASM(64f);
SQR_ASM(32fc);
SQR_ASM(64fc);

SQR_SFS_ASM(8u);
SQR_SFS_ASM(16u);
SQR_SFS_ASM(16s);
SQR_SFS_ASM(16sc);


#undef SQR_ASM
#undef SQR_SFS_ASM


/////// sqrt /////////
template<typename T>
static inline IppStatus sqrt(const T *, T *, int, int);


#define SQRT_ASM(Suffix)\
template<>\
static inline IppStatus sqrt<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix *dst,\
                                  int len, int)\
{\
    return src == dst ? ippsSqrt_##Suffix##_I(dst, len)\
                      : ippsSqrt_##Suffix(src, dst, len);\
}


#define SQRT_SFS_ASM(Suffix)\
template<>\
static inline IppStatus sqrt<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix *dst,\
                                  int len, int scale)\
{\
    return ippsSqrt_##Suffix##_Sfs(src, dst, len, scale);\
}

SQRT_ASM(32f);
SQRT_ASM(64f);
SQRT_ASM(32fc);
SQRT_ASM(64fc);

SQRT_SFS_ASM(8u);
SQRT_SFS_ASM(16u);
SQRT_SFS_ASM(16s);
SQRT_SFS_ASM(16sc);


#undef SQRT_ASM
#undef SQRT_SFS_ASM

///// cubrt ////
template<typename T>
static inline IppStatus cubrt(const T*, T*, int);

template<>
static inline IppStatus cubrt<Ipp32f>(
        const Ipp32f *src, Ipp32f *dst, int len)
{
    return ippsCubrt_32f(src, dst, len);
}


///// exp ////
template<typename T>
static inline IppStatus exp(const T*, T*, int);

template<>
static inline IppStatus exp<Ipp32f>(
        const Ipp32f *src, Ipp32f *dst, int len)
{
    return ippsExp_32f(src, dst, len);
}

template<>
static inline IppStatus exp<Ipp64f>(
        const Ipp64f *src, Ipp64f *dst, int len)
{
    return ippsExp_64f(src, dst, len);
}

///// ln ///////
template<typename T>
static inline IppStatus ln(const T *, T *, int, int);


#define LN_ASM(Suffix)\
template<>\
static inline IppStatus ln<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix *dst,\
                                  int len, int)\
{\
    return src == dst ? ippsLn_##Suffix##_I(dst, len)\
                      : ippsLn_##Suffix(src, dst, len);\
}


#define LN_SFS_ASM(Suffix)\
template<>\
static inline IppStatus ln<Ipp##Suffix>(\
                                  const Ipp##Suffix *src,\
                                  Ipp##Suffix *dst,\
                                  int len, int scale)\
{\
    return src == dst ? ippsLn_##Suffix##_ISfs(dst, len, scale)\
                      : ippsLn_##Suffix##_Sfs(src, dst, len, scale);\
}

LN_ASM(32f);
LN_ASM(64f);

LN_SFS_ASM(16s);
LN_SFS_ASM(32s);


#undef LN_ASM
#undef LN_SFS_ASM

///// arctan /////////////
template<typename T>
static inline IppStatus arctan(const T*, T*, int);

template<>
static inline IppStatus arctan<Ipp32f>(
        const Ipp32f *src, Ipp32f *dst, int len)
{
    return ippsArctan_32f(src, dst, len);
}

template<>
static inline IppStatus arctan<Ipp64f>(
        const Ipp64f *src, Ipp64f *dst, int len)
{
    return ippsArctan_64f(src, dst, len);
}



//////// normalize /////////
template<typename T1, typename T2>
static inline IppStatus normalize(
        const T1*, T1*, int, T1, T2, int);

#define NORMALIZE_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus normalize<Ipp##Suffix1, Ipp##Suffix2>(\
                                  const Ipp##Suffix1 *src,\
                                  Ipp##Suffix1 *dst,\
                                  int len, Ipp##Suffix1 sub,\
                                  Ipp##Suffix2 div, int)\
{\
    return ippsNormalize_##Suffix1(src, dst, len, sub, div);\
}



NORMALIZE_ASM(32f, 32f);
NORMALIZE_ASM(64f, 64f);
NORMALIZE_ASM(32fc, 32f);
NORMALIZE_ASM(64fc, 64f);

#undef NORMALIZE_ASM




//////////sort_ascend /////////
template<typename T>
static inline IppStatus sort_ascend(T *, int);

#define SORT_ASCEND(Suffix)\
template<>\
static inline IppStatus sort_ascend<Ipp##Suffix>(\
        Ipp##Suffix *buf, int len)\
{\
    return ippsSortAscend_##Suffix##_I(buf, len);\
}

SORT_ASCEND(8u);
SORT_ASCEND(16u);
SORT_ASCEND(16s);
SORT_ASCEND(32s);
SORT_ASCEND(32f);
SORT_ASCEND(64f);


#undef SORT_ASCEND



//////////sort_descend /////////
template<typename T>
static inline IppStatus sort_descend(T *, int);

#define SORT_DESCEND(Suffix)\
template<>\
static inline IppStatus sort_descend<Ipp##Suffix>(\
        Ipp##Suffix *buf, int len)\
{\
    return ippsSortDescend_##Suffix##_I(buf, len);\
}

SORT_DESCEND(8u);
SORT_DESCEND(16u);
SORT_DESCEND(16s);
SORT_DESCEND(32s);
SORT_DESCEND(32f);
SORT_DESCEND(64f);

#undef SORT_DESCEND



//////////sort_index_descend /////////
template<typename T>
static inline IppStatus sort_index_ascend(T *, int*, int);

#define SORT_INDEX_ASCEND(Suffix)\
template<>\
static inline IppStatus sort_index_ascend<Ipp##Suffix>(\
        Ipp##Suffix *buf, int *idxs, int len)\
{\
    return ippsSortIndexAscend_##Suffix##_I(buf, idxs, len);\
}

SORT_INDEX_ASCEND(8u);
SORT_INDEX_ASCEND(16u);
SORT_INDEX_ASCEND(16s);
SORT_INDEX_ASCEND(32s);
SORT_INDEX_ASCEND(32f);
SORT_INDEX_ASCEND(64f);


#undef SORT_INDEX_ASCEND


//////////sort_index_descend /////////
template<typename T>
static inline IppStatus sort_index_descend(T *, int*, int);

#define SORT_INDEX_DESCEND(Suffix)\
template<>\
static inline IppStatus sort_index_descend<Ipp##Suffix>(\
        Ipp##Suffix *buf, int *idxs, int len)\
{\
    return ippsSortIndexDescend_##Suffix##_I(buf, idxs, len);\
}

SORT_INDEX_DESCEND(8u);
SORT_INDEX_DESCEND(16u);
SORT_INDEX_DESCEND(16s);
SORT_INDEX_DESCEND(32s);
SORT_INDEX_DESCEND(32f);
SORT_INDEX_DESCEND(64f);

#undef SORT_INDEX_DESCEND


//////////sort_radix_ascend /////////
template<typename T>
static inline IppStatus sort_radix_ascend(T *, T*, Ipp32s);

#define SORT_RADIX_ASCEND(Suffix)\
template<>\
static inline IppStatus sort_radix_ascend<Ipp##Suffix>(\
        Ipp##Suffix *buf, Ipp##Suffix *tmp, Ipp32s len)\
{\
    return ippsSortRadixAscend_##Suffix##_I(buf, tmp, len);\
}

SORT_RADIX_ASCEND(8u);
SORT_RADIX_ASCEND(16u);
SORT_RADIX_ASCEND(16s);
SORT_RADIX_ASCEND(32s);
SORT_RADIX_ASCEND(32u);
SORT_RADIX_ASCEND(32f);
SORT_RADIX_ASCEND(64f);

#undef SORT_RADIX_ASCEND

//////////sort_radix_descend /////////
template<typename T>
static inline IppStatus sort_radix_descend(T *, T*, Ipp32s);

#define SORT_RADIX_DESCEND(Suffix)\
template<>\
static inline IppStatus sort_radix_descend<Ipp##Suffix>(\
        Ipp##Suffix *buf, Ipp##Suffix *tmp, Ipp32s len)\
{\
    return ippsSortRadixDescend_##Suffix##_I(buf, tmp, len);\
}

SORT_RADIX_DESCEND(8u);
SORT_RADIX_DESCEND(16u);
SORT_RADIX_DESCEND(16s);
SORT_RADIX_DESCEND(32s);
SORT_RADIX_DESCEND(32u);
SORT_RADIX_DESCEND(32f);
SORT_RADIX_DESCEND(64f);

#undef SORT_RADIX_DESCEND


//////////sort_radix_index_ascend /////////
template<typename T>
static inline IppStatus sort_radix_index_ascend(const T * const,
                                                 Ipp32s, Ipp32s*,
                                                 Ipp32s*, Ipp32s);

#define SORT_RADIX_INDEX_ASCEND(Suffix)\
template<>\
static inline IppStatus sort_radix_index_ascend<Ipp##Suffix>(\
        const Ipp##Suffix * const buf, Ipp32s stride, Ipp32s *idxs,\
        Ipp32s *tmp_idxs, Ipp32s len)\
{\
    return ippsSortRadixIndexAscend_##Suffix(\
            buf, stride, idxs, tmp_idxs, len);\
}

SORT_RADIX_INDEX_ASCEND(8u);
SORT_RADIX_INDEX_ASCEND(16u);
SORT_RADIX_INDEX_ASCEND(16s);
SORT_RADIX_INDEX_ASCEND(32s);
SORT_RADIX_INDEX_ASCEND(32u);
SORT_RADIX_INDEX_ASCEND(32f);

#undef SORT_RADIX_INDEX_ASCEND


//////////sort_radix_index_descend /////////
template<typename T>
static inline IppStatus sort_radix_index_descend(const T * const,
                                                 Ipp32s, Ipp32s*,
                                                 Ipp32s*, Ipp32s);
#define SORT_RADIX_INDEX_DESCEND(Suffix)\
template<>\
static inline IppStatus sort_radix_index_descend<Ipp##Suffix>(\
        const Ipp##Suffix * const buf, Ipp32s stride, Ipp32s *idxs,\
        Ipp32s *tmp_idxs, Ipp32s len)\
{\
    return ippsSortRadixIndexDescend_##Suffix(\
            buf, stride, idxs, tmp_idxs, len);\
}

SORT_RADIX_INDEX_DESCEND(8u);
SORT_RADIX_INDEX_DESCEND(16u);
SORT_RADIX_INDEX_DESCEND(16s);
SORT_RADIX_INDEX_DESCEND(32s);
SORT_RADIX_INDEX_DESCEND(32u);
SORT_RADIX_INDEX_DESCEND(32f);

#undef SORT_RADIX_INDEX_DESCEND


//////////swap_bytes/////////
template<typename T>
static inline IppStatus swap_bytes(const T *,
                                   T *, int);

#define SWAP_BYTES(Suffix)\
template<>\
static inline IppStatus swap_bytes<Ipp##Suffix>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len)\
{\
    return src == dst ? ippsSwapBytes_##Suffix##_I(dst, len)\
                      : ippsSwapBytes_##Suffix(src, dst, len);\
}

template<>
static inline IppStatus swap_bytes<Ipp8u>(
        const Ipp8u *src, Ipp8u *dst, int len)
{
    return src == dst ? ippsSwapBytes_24u_I(dst, len)
                      : ippsSwapBytes_24u(src, dst, len);
}


SWAP_BYTES(16u);
SWAP_BYTES(32u);
SWAP_BYTES(64u);

#undef SWAP_BYTES


//////////swap_bytes/////////
template<typename T1, typename T2>
static inline IppStatus convert(const T1 *,
                                   T2 *, int);

#define CONVERT(Suffix1, Suffix2)\
template<>\
static inline IppStatus convert<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix2 *dst, int len)\
{\
    return ippsConvert_##Suffix1##Suffix2(src, dst, len);\
}


template<typename T1, typename T2>
static inline IppStatus convert_sfs(const T1 *,
                                   T2 *, int, int);

#define CONVERT_SFS(Suffix1, Suffix2)\
template<>\
static inline IppStatus convert_sfs<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix2 *dst, int len, int scale)\
{\
    return ippsConvert_##Suffix1##Suffix2##_Sfs(src, dst, len, scale);\
}

template<typename T1, typename T2>
static inline IppStatus convert_sfs(const T1 *,
                                   T2 *, int,  IppRoundMode, int);

#define CONVERT_SFS_RND(Suffix1, Suffix2)\
template<>\
static inline IppStatus convert_sfs<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix2 *dst, int len, IppRoundMode rnd, int scale)\
{\
    return ippsConvert_##Suffix1##Suffix2##_Sfs(src, dst, len, rnd, scale);\
}


CONVERT(8s, 16s);
CONVERT(8s, 32f);
CONVERT(8u, 32f);
CONVERT(16s, 32s);
CONVERT(16s, 32f);
CONVERT(16u, 32f);
CONVERT(32s, 16s);
CONVERT(32s, 32f);
CONVERT(32s, 64f);
CONVERT(32f, 64f);
CONVERT(64s, 64f);
CONVERT(64f, 32f);


CONVERT_SFS_RND(16s, 8s);
CONVERT_SFS(16s, 32f);
CONVERT_SFS(16s, 64f);
CONVERT_SFS(32s, 16s);
CONVERT_SFS(32s, 32f);
CONVERT_SFS(32s, 64f);
CONVERT_SFS_RND(32f, 8s);
CONVERT_SFS_RND(32f, 8u);
CONVERT_SFS_RND(32f, 16s);
CONVERT_SFS_RND(32f, 16u);
CONVERT_SFS_RND(32f, 32s);
CONVERT_SFS_RND(64s, 32s);
CONVERT_SFS_RND(64f, 16s);
CONVERT_SFS_RND(64f, 32s);
CONVERT_SFS_RND(64f, 64s);

#undef CONVERT
#undef CONVERT_SFS
#undef CONVERT_SFS_RND


//////////conj/////////
template<typename T>
static inline IppStatus conj(const T *,
                                   T *, int);

#define CONJ(Suffix)\
template<>\
static inline IppStatus conj<Ipp##Suffix>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len)\
{\
    return src == dst ? ippsConj_##Suffix##_I(dst, len)\
                      : ippsConj_##Suffix(src, dst, len);\
}

CONJ(16sc);
CONJ(32fc);
CONJ(64fc);

#undef CONJ


//////////magnitude/////////
template<typename T>
static inline IppStatus magnitude(const T *, const T*,
                                   T *, int, int);

template<>
static inline IppStatus magnitude<Ipp32f>(const Ipp32f *re, 
                                          const Ipp32f *im,
										  Ipp32f *dst,
                                          int len,
                                          int)
{
    return ippsMagnitude_32f(re, im, dst, len);
}

template<>
static inline IppStatus magnitude<Ipp64f>(const Ipp64f *re, 
                                          const Ipp64f *im,
                                          Ipp64f *dst,
                                          int len,
                                          int)
{
    return ippsMagnitude_64f(re, im, dst, len);
}

template<>
static inline IppStatus magnitude<Ipp16s>(const Ipp16s *re, 
                                          const Ipp16s *im,
                                          Ipp16s *dst,
                                          int len,
                                          int scale)
{
    return ippsMagnitude_16s_Sfs(re, im, dst, len, scale);
}

//
template<typename T1, typename T2>
static inline IppStatus magnitude(const T1 *, const T1*,
                                   T2 *, int, int);

template<>
static inline IppStatus magnitude<Ipp16s, Ipp32f>(const Ipp16s *re, const Ipp16s* im,
                                   Ipp32f *dst, int len, int)
{
    return ippsMagnitude_16s32f(re, im, dst, len);
}

//
template<typename T1, typename T2>
static inline IppStatus magnitude(const T1 *,
                                   T2 *, int, int);

template<>
static inline IppStatus magnitude<Ipp32fc, Ipp32f>(const Ipp32fc *src,
                                   Ipp32f *dst, int len, int)
{
    return ippsMagnitude_32fc(src, dst, len);
}

template<>
static inline IppStatus magnitude<Ipp64fc, Ipp64f>(const Ipp64fc *src,
                                   Ipp64f *dst, int len, int)
{
    return ippsMagnitude_64fc(src, dst, len);
}

template<>
static inline IppStatus magnitude<Ipp16sc, Ipp32f>(const Ipp16sc *src,
                                   Ipp32f *dst, int len, int)
{
    return ippsMagnitude_16sc32f(src, dst, len);
}

template<>
static inline IppStatus magnitude<Ipp16sc, Ipp16s>(const Ipp16sc *src,
                                   Ipp16s *dst, int len, int scale)
{
    return ippsMagnitude_16sc_Sfs(src, dst, len, scale);
}

template<>
static inline IppStatus magnitude<Ipp32sc, Ipp32s>(const Ipp32sc *src,
                                   Ipp32s *dst, int len, int scale)
{
    return ippsMagnitude_32sc_Sfs(src, dst, len, scale);
}



//////////phase/////////
template<typename T1, typename T2>
static inline IppStatus phase(const T1 *, T2*, int);

template<>
static inline IppStatus phase<Ipp64fc, Ipp64f>(
        const Ipp64fc *src, Ipp64f *dst, int len)
{
    return ippsPhase_64fc(src, dst, len);
}

template<>
static inline IppStatus phase<Ipp32fc, Ipp32f>(
        const Ipp32fc *src, Ipp32f *dst, int len)
{
    return ippsPhase_32fc(src, dst, len);
}

template<>
static inline IppStatus phase<Ipp16sc, Ipp32f>(
        const Ipp16sc *src, Ipp32f *dst, int len)
{
    return ippsPhase_16sc32f(src, dst, len);
}


template<typename T1, typename T2>
static inline IppStatus phase(const T1 *, const T1*, T2*, int);


template<>
static inline IppStatus phase<Ipp64f, Ipp64f>(
        const Ipp64f *re, const Ipp64f *im, Ipp64f *dst, int len)
{
    return ippsPhase_64f(re, im, dst, len);
}

template<>
static inline IppStatus phase<Ipp32f, Ipp32f>(
        const Ipp32f *re, const Ipp32f *im, Ipp32f *dst, int len)
{
    return ippsPhase_32f(re, im, dst, len);
}

template<>
static inline IppStatus phase<Ipp16s, Ipp32f>(
        const Ipp16s *re, const Ipp16s *im, Ipp32f *dst, int len)
{
    return ippsPhase_16s32f(re, im, dst, len);
}


//////////power_spectr/////////
template<typename T1, typename T2>
static inline IppStatus power_spectr(const T1 *, T2*, int, int);

template<>
static inline IppStatus power_spectr<Ipp64fc, Ipp64f>(
        const  Ipp64fc* src, Ipp64f* dst, int len, int)
{
    return ippsPowerSpectr_64fc(src, dst, len);
}

template<>
static inline IppStatus power_spectr<Ipp32fc, Ipp32f>(
        const  Ipp32fc* src, Ipp32f* dst, int len, int)
{
    return ippsPowerSpectr_32fc(src, dst, len);
}

template<>
static inline IppStatus power_spectr<Ipp16sc, Ipp16s>(
        const  Ipp16sc* src, Ipp16s* dst, int len, int scale)
{
    return ippsPowerSpectr_16sc_Sfs(src, dst, len, scale);
}


template<typename T1, typename T2>
static inline IppStatus power_spectr(const T1 *, const T1*, T2*, int, int);


template<>
static inline IppStatus power_spectr<Ipp64f, Ipp64f>(
        const  Ipp64f* re, const Ipp64f *im, Ipp64f* dst, int len, int)
{
    return ippsPowerSpectr_64f(re, im, dst, len);
}

template<>
static inline IppStatus power_spectr<Ipp32f, Ipp32f>(
        const  Ipp32f* re, const Ipp32f *im, Ipp32f* dst, int len, int)
{
    return ippsPowerSpectr_32f(re, im, dst, len);
}

template<>
static inline IppStatus power_spectr<Ipp16s, Ipp16s>(
        const  Ipp16s* re, const Ipp16s *im, Ipp16s* dst, int len, int scale)
{
    return ippsPowerSpectr_16s_Sfs(re, im, dst, len, scale);
}


////// real, imag/////////
template<typename T1, typename T2>
static inline IppStatus real(const T1*, T2*, int);

template<typename T1, typename T2>
static inline IppStatus imag(const T1*, T2*, int);

#define REAL_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus real<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix2 *re, int len)\
{ return ippsReal_##Suffix1(src, re, len); }

#define IMAG_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus imag<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix2 *im, int len)\
{ return ippsImag_##Suffix1(src, im, len); }


REAL_ASM(16sc, 16s);
REAL_ASM(32fc, 32f);
REAL_ASM(64fc, 64f);

IMAG_ASM(16sc, 16s);
IMAG_ASM(32fc, 32f);
IMAG_ASM(64fc, 64f);

#undef REAL_ASM
#undef IMAG_ASM

///// cplx_to_real, real_to_cplx

template<typename T1, typename T2>
static inline IppStatus cplx_to_real(const T1*, T2*, T2*, int);

template<typename T1, typename T2>
static inline IppStatus real_to_cplx(const T1*, const T1*, T2*, int);

#define CPLX2REAL_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus cplx_to_real<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix2 *re,\
        Ipp##Suffix2 *im, int len)\
{ return ippsCplxToReal_##Suffix1(src, re, im, len); }

#define REAL2CPLX_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus real_to_cplx<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *re, const Ipp##Suffix1 *im,\
        Ipp##Suffix2 *dst, int len)\
{ return ippsRealToCplx_##Suffix1(re, im, dst, len); }


CPLX2REAL_ASM(16sc, 16s);
CPLX2REAL_ASM(32fc, 32f);
CPLX2REAL_ASM(64fc, 64f);

REAL2CPLX_ASM(16s, 16sc);
REAL2CPLX_ASM(32f, 32fc);
REAL2CPLX_ASM(64f, 64fc);

#undef CPLX2REAL_ASM
#undef REAL2CPLX_ASM


////// threshold_lt, threshold_gt ////////////
template<typename T1, typename T2>
static inline IppStatus threshold_lt(const T1*, T1*, int, T2);

template<typename T1, typename T2>
static inline IppStatus threshold_gt(const T1*, T1*, int, T2);


#define THRESHOLD_LT_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus threshold_lt<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix1 *dst,\
        int len, Ipp##Suffix2 level)\
{ return src == dst ? ippsThreshold_LT_##Suffix1##_I(dst, len, level)\
                    : ippsThreshold_LT_##Suffix1(src, dst, len, level); }

#define THRESHOLD_GT_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus threshold_gt<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix1 *dst,\
        int len, Ipp##Suffix2 level)\
{ return src == dst ? ippsThreshold_GT_##Suffix1##_I(dst, len, level)\
                    : ippsThreshold_GT_##Suffix1(src, dst, len, level); }


THRESHOLD_LT_ASM(16s, 16s);
THRESHOLD_LT_ASM(32s, 32s);
THRESHOLD_LT_ASM(32f, 32f);
THRESHOLD_LT_ASM(64f, 64f);
THRESHOLD_LT_ASM(32fc, 32f);
THRESHOLD_LT_ASM(64fc, 64f);


THRESHOLD_GT_ASM(16s, 16s);
THRESHOLD_GT_ASM(32s, 32s);
THRESHOLD_GT_ASM(32f, 32f);
THRESHOLD_GT_ASM(64f, 64f);
THRESHOLD_GT_ASM(32fc, 32f);
THRESHOLD_GT_ASM(64fc, 64f);

#undef THRESHOLD_LT_ASM
#undef THRESHOLD_GT_ASM



////// threshold_lt_abs, threshold_gt_abs ////////////
template<typename T1, typename T2>
static inline IppStatus threshold_lt_abs(const T1*, T1*, int, T2);

template<typename T1, typename T2>
static inline IppStatus threshold_gt_abs(const T1*, T1*, int, T2);


#define THRESHOLD_LT_ABS_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus threshold_lt_abs<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix1 *dst,\
        int len, Ipp##Suffix2 level)\
{ return src == dst ? ippsThreshold_LTAbs_##Suffix1##_I(dst, len, level)\
                    : ippsThreshold_LTAbs_##Suffix1(src, dst, len, level); }

#define THRESHOLD_GT_ABS_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus threshold_gt_abs<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix1 *dst,\
        int len, Ipp##Suffix2 level)\
{ return src == dst ? ippsThreshold_GTAbs_##Suffix1##_I(dst, len, level)\
                    : ippsThreshold_GTAbs_##Suffix1(src, dst, len, level); }


THRESHOLD_LT_ABS_ASM(16s, 16s);
THRESHOLD_LT_ABS_ASM(32s, 32s);
THRESHOLD_LT_ABS_ASM(32f, 32f);
THRESHOLD_LT_ABS_ASM(64f, 64f);


THRESHOLD_GT_ABS_ASM(16s, 16s);
THRESHOLD_GT_ABS_ASM(32s, 32s);
THRESHOLD_GT_ABS_ASM(32f, 32f);
THRESHOLD_GT_ABS_ASM(64f, 64f);

#undef THRESHOLD_LT_ABS_ASM
#undef THRESHOLD_GT_ABS_ASM


////// threshold_lt_val, threshold_gt_val, threshold_lt_val_gt_val ////////////
template<typename T1, typename T2>
static inline IppStatus threshold_lt_val(const T1*, T1*, int, T2, T1);

template<typename T1, typename T2>
static inline IppStatus threshold_gt_val(const T1*, T1*, int, T2, T1);

template<typename T1, typename T2>
static inline IppStatus threshold_lt_val_gt_val(
        const T1*, T1*, int, T2, T1, T2, T1);

#define THRESHOLD_LT_VAL_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus threshold_lt_val<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix1 *dst,\
        int len, Ipp##Suffix2 level, Ipp##Suffix1 value)\
{ return src == dst ? ippsThreshold_LTVal_##Suffix1##_I(dst, len, level, value)\
                    : ippsThreshold_LTVal_##Suffix1(src, dst, len, level, value); }

#define THRESHOLD_GT_VAL_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus threshold_gt_val<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix1 *dst,\
        int len, Ipp##Suffix2 level, Ipp##Suffix1 value)\
{ return src == dst ? ippsThreshold_GTVal_##Suffix1##_I(dst, len, level, value)\
                    : ippsThreshold_GTVal_##Suffix1(src, dst, len, level, value); }

#define THRESHOLD_LT_VAL_GT_VAL_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus threshold_lt_val_gt_val<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix1 *dst,\
        int len, Ipp##Suffix2 lt_level, Ipp##Suffix1 lt_value,\
        Ipp##Suffix2 gt_level, Ipp##Suffix1 gt_value)\
{ return src == dst ? ippsThreshold_LTValGTVal_##Suffix1##_I(\
                      dst, len, lt_level, lt_value, gt_level, gt_value)\
                    : ippsThreshold_LTValGTVal_##Suffix1(\
                      src, dst, len, lt_level, lt_value, gt_level, gt_value); }


THRESHOLD_LT_VAL_ASM(16s, 16s);
THRESHOLD_LT_VAL_ASM(32f, 32f);
THRESHOLD_LT_VAL_ASM(64f, 64f);
THRESHOLD_LT_VAL_ASM(32fc, 32f);
THRESHOLD_LT_VAL_ASM(64fc, 64f);


THRESHOLD_GT_VAL_ASM(16s, 16s);
THRESHOLD_GT_VAL_ASM(32f, 32f);
THRESHOLD_GT_VAL_ASM(64f, 64f);
THRESHOLD_GT_VAL_ASM(32fc, 32f);
THRESHOLD_GT_VAL_ASM(64fc, 64f);

THRESHOLD_LT_VAL_GT_VAL_ASM(16s, 16s);
THRESHOLD_LT_VAL_GT_VAL_ASM(32s, 32s);
THRESHOLD_LT_VAL_GT_VAL_ASM(32f, 32f);
THRESHOLD_LT_VAL_GT_VAL_ASM(64f, 64f);

#undef THRESHOLD_LT_VAL_ASM
#undef THRESHOLD_GT_VAL_ASM
#undef THRESHOLD_LT_VAL_GT_VAL_ASM


////// threshold_lt_inv ////////////
template<typename T1, typename T2>
static inline IppStatus threshold_lt_inv(const T1*, T1*, int, T2);


#define THRESHOLD_LT_INV_ASM(Suffix1, Suffix2)\
template<>\
static inline IppStatus threshold_lt_inv<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, Ipp##Suffix1 *dst,\
        int len, Ipp##Suffix2 level)\
{ return src == dst ? ippsThreshold_LTInv_##Suffix1##_I(dst, len, level)\
                    : ippsThreshold_LTInv_##Suffix1(src, dst, len, level); }

THRESHOLD_LT_INV_ASM(32f, 32f);
THRESHOLD_LT_INV_ASM(64f, 64f);
THRESHOLD_LT_INV_ASM(32fc, 32f);
THRESHOLD_LT_INV_ASM(64fc, 64f);

#undef THRESHOLD_LT_INV_ASM


////// cart_to_polar, polar_to_cart ////////
static inline IppStatus cart_to_polar(
        const Ipp32f *re, const Ipp32f *im, Ipp32f *magn, Ipp32f *phase, int len)
{
    return ippsCartToPolar_32f(re, im, magn, phase, len);
}
static inline IppStatus cart_to_polar(
        const Ipp64f *re, const Ipp64f *im, Ipp64f *magn, Ipp64f *phase, int len)
{
    return ippsCartToPolar_64f(re, im, magn, phase, len);
}

static inline IppStatus cart_to_polar(
        const Ipp32fc *src, Ipp32f *magn, Ipp32f *phase, int len)
{
    return ippsCartToPolar_32fc(src, magn, phase, len);
}

static inline IppStatus cart_to_polar(
        const Ipp64fc *src, Ipp64f *magn, Ipp64f *phase, int len)
{
    return ippsCartToPolar_64fc(src, magn, phase, len);
}

static inline IppStatus cart_to_polar(
        const Ipp16sc *src, Ipp16s *magn, Ipp16s *phase, int len, 
        int magn_scale, int phase_scale)
{
    return ippsCartToPolar_16sc_Sfs(src, magn, phase, len, magn_scale, phase_scale);
}



static inline IppStatus polar_to_cart(
        const Ipp32f *magn, const Ipp32f *phase, Ipp32f *re, Ipp32f *im, int len)
{
    return ippsPolarToCart_32f(magn, phase, re, im, len);
}
static inline IppStatus polar_to_cart(
        const Ipp64f *magn, const Ipp64f *phase, Ipp64f *re, Ipp64f *im, int len)
{
    return ippsPolarToCart_64f(magn, phase, re, im, len);
}

static inline IppStatus polar_to_cart(
        const Ipp32f *magn, const Ipp32f *phase, Ipp32fc *dst, int len)
{
    return ippsPolarToCart_32fc(magn, phase, dst, len);
}

static inline IppStatus polar_to_cart(
        const Ipp64f *magn, const Ipp64f *phase, Ipp64fc *dst, int len)
{
    return ippsPolarToCart_64fc(magn, phase, dst, len);
}

static inline IppStatus polar_to_cart(
        Ipp16s *magn, Ipp16s *phase, Ipp16sc *dst, int len, 
        int magn_scale, int phase_scale)
{
    return ippsPolarToCart_16sc_Sfs(magn, phase, dst, len, magn_scale, phase_scale);
}

////// max_order ///////
template<typename T>
static inline IppStatus max_order(const T*, int, int*);


#define MAX_ORDER_ASM(Suffix)\
template<>\
static inline IppStatus max_order<Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, int *order)\
{\
    return ippsMaxOrder_##Suffix(src, len, order);\
}

MAX_ORDER_ASM(16s);
MAX_ORDER_ASM(32s);
MAX_ORDER_ASM(32f);
MAX_ORDER_ASM(64f);

#undef MAX_ORDER_ASM

////// flip //////////
template<typename T>
static inline IppStatus flip(const T*, T*, int);

#define FLIP_ASM(Suffix)\
template<>\
static inline IppStatus flip<Ipp##Suffix>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len)\
{ return src == dst ? ippsFlip_##Suffix##_I(dst, len)\
                    : ippsFlip_##Suffix(src, dst, len); }

FLIP_ASM(8u);
FLIP_ASM(16u);
FLIP_ASM(32f);
FLIP_ASM(64f);
FLIP_ASM(32fc);
FLIP_ASM(64fc);

#undef FLIP_ASM


//////// find_nearest_one, find_nearest /////////
static inline IppStatus find_nearest_one(
        Ipp16u in_val, Ipp16u *out_val, int *out_idx, const Ipp16u *src, int len)
{
    return ippsFindNearestOne_16u(in_val, out_val, out_idx, src, len);
}

static inline IppStatus find_nearest(
        const Ipp16u *in_val, Ipp16u *out_val, int *out_idx,
        int len, const Ipp16u *src, int slen)
{
    return ippsFindNearest_16u(
            in_val, out_val, out_idx, len, src, slen);
}


/////// win_bartlett /////////
template<typename T>
static inline IppStatus win_bartlett(const T*, T*, int);

#define WIN_BARTLETT_ASM(Suffix)\
template<>\
static inline IppStatus win_bartlett<Ipp##Suffix>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len)\
{ return src == dst ? ippsWinBartlett_##Suffix##_I(dst, len)\
                    : ippsWinBartlett_##Suffix(src, dst, len); }

WIN_BARTLETT_ASM(16s);
WIN_BARTLETT_ASM(32f);
WIN_BARTLETT_ASM(64f);
WIN_BARTLETT_ASM(16sc);
WIN_BARTLETT_ASM(32fc);
WIN_BARTLETT_ASM(64fc);

#undef WIN_BARTLETT_ASM


////// win_blackman, win_blackman_std, win_blackman_opt ////
template<typename T1, typename T2>
static inline IppStatus win_blackman(const T1*, T1*, int, T2);

template<typename T>
static inline IppStatus win_blackman_std(const T*, T*, int);

template<typename T>
static inline IppStatus win_blackman_opt(const T*, T*, int);

#define WIN_BLACKMAN_ASM(Suffix, T2)\
template<>\
static inline IppStatus win_blackman<Ipp##Suffix, T2>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len, T2 alpha)\
{ return src == dst ? ippsWinBlackman_##Suffix##_I(dst, len, alpha)\
                    : ippsWinBlackman_##Suffix(src, dst, len, alpha); }

#define WIN_BLACKMAN_STD_ASM(Suffix)\
template<>\
static inline IppStatus win_blackman_std<Ipp##Suffix>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len)\
{ return src == dst ? ippsWinBlackmanStd_##Suffix##_I(dst, len)\
                    : ippsWinBlackmanStd_##Suffix(src, dst, len); }

#define WIN_BLACKMAN_OPT_ASM(Suffix)\
template<>\
static inline IppStatus win_blackman_opt<Ipp##Suffix>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len)\
{ return src == dst ? ippsWinBlackmanOpt_##Suffix##_I(dst, len)\
                    : ippsWinBlackmanOpt_##Suffix(src, dst, len); }


WIN_BLACKMAN_ASM(16s, float);
WIN_BLACKMAN_ASM(32f, float);
WIN_BLACKMAN_ASM(64f, double);
WIN_BLACKMAN_ASM(16sc, float);
WIN_BLACKMAN_ASM(32fc, float);
WIN_BLACKMAN_ASM(64fc, double);


WIN_BLACKMAN_STD_ASM(16s);
WIN_BLACKMAN_STD_ASM(32f);
WIN_BLACKMAN_STD_ASM(64f);
WIN_BLACKMAN_STD_ASM(16sc);
WIN_BLACKMAN_STD_ASM(32fc);
WIN_BLACKMAN_STD_ASM(64fc);

WIN_BLACKMAN_OPT_ASM(16s);
WIN_BLACKMAN_OPT_ASM(32f);
WIN_BLACKMAN_OPT_ASM(64f);
WIN_BLACKMAN_OPT_ASM(16sc);
WIN_BLACKMAN_OPT_ASM(32fc);
WIN_BLACKMAN_OPT_ASM(64fc);

#undef WIN_BLACKMAN_ASM
#undef WIN_BLACKMAN_STD_ASM
#undef WIN_BLACKMAN_OPT_ASM


/////// win_hamming /////////
template<typename T>
static inline IppStatus win_hamming(const T*, T*, int);

#define WIN_HAMMING_ASM(Suffix)\
template<>\
static inline IppStatus win_hamming<Ipp##Suffix>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len)\
{ return src == dst ? ippsWinHamming_##Suffix##_I(dst, len)\
                    : ippsWinHamming_##Suffix(src, dst, len); }

WIN_HAMMING_ASM(16s);
WIN_HAMMING_ASM(32f);
WIN_HAMMING_ASM(64f);
WIN_HAMMING_ASM(16sc);
WIN_HAMMING_ASM(32fc);
WIN_HAMMING_ASM(64fc);

#undef WIN_HAMMING_ASM


/////// win_hann /////////
template<typename T>
static inline IppStatus win_hann(const T*, T*, int);

#define WIN_HANN_ASM(Suffix)\
template<>\
static inline IppStatus win_hann<Ipp##Suffix>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len)\
{ return src == dst ? ippsWinHann_##Suffix##_I(dst, len)\
                    : ippsWinHann_##Suffix(src, dst, len); }

WIN_HANN_ASM(16s);
WIN_HANN_ASM(32f);
WIN_HANN_ASM(64f);
WIN_HANN_ASM(16sc);
WIN_HANN_ASM(32fc);
WIN_HANN_ASM(64fc);

#undef WIN_HANN_ASM



////// win_kaiser //////
template<typename T1, typename T2>
static inline IppStatus win_kaiser(const T1*, T1*, int, T2);


#define WIN_KAISER_ASM(Suffix, T2)\
template<>\
static inline IppStatus win_kaiser<Ipp##Suffix, T2>(\
        const Ipp##Suffix *src, Ipp##Suffix *dst, int len, T2 alpha)\
{ return src == dst ? ippsWinKaiser_##Suffix##_I(dst, len, alpha)\
                    : ippsWinKaiser_##Suffix(src, dst, len, alpha); }

WIN_KAISER_ASM(16s, float);
WIN_KAISER_ASM(32f, float);
WIN_KAISER_ASM(64f, double);
WIN_KAISER_ASM(16sc, float);
WIN_KAISER_ASM(32fc, float);
WIN_KAISER_ASM(64fc, double);

#undef WIN_KAISER_ASM


////// sum /////////
template<typename T>
static inline IppStatus sum(const T*, int, T*, IppHintAlgorithm);

template<typename T1, typename T2>
static inline IppStatus sum(const T1*, int, T2*, int);


template<>
static inline IppStatus sum<Ipp32f>(
        const Ipp32f *src, int len, Ipp32f *sum_, IppHintAlgorithm hint)
{ return ippsSum_32f(src, len, sum_, hint); }

template<>
static inline IppStatus sum<Ipp32fc>(
        const Ipp32fc *src, int len, Ipp32fc *sum_, IppHintAlgorithm hint)
{ return ippsSum_32fc(src, len, sum_, hint); }


#define SUM_ASM1(Suffix)\
template<>\
static inline IppStatus sum<Ipp##Suffix, Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *sum_, int scale)\
{ return ippsSum_##Suffix##_Sfs(src, len, sum_, scale); }

#define SUM_ASM2(Suffix)\
template<>\
static inline IppStatus sum<Ipp##Suffix, Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *sum_, int scale)\
{ return ippsSum_##Suffix(src, len, sum_); }

template<>
static inline IppStatus sum<Ipp16s, Ipp32s>(
        const Ipp16s *src, int len, Ipp32s *sum_, int scale)
{ return ippsSum_16s32s_Sfs(src, len, sum_, scale); }

SUM_ASM1(16s);
SUM_ASM1(32s);
SUM_ASM1(16sc);
SUM_ASM2(64f);
SUM_ASM2(64fc);

#undef SUM_ASM1
#undef SUM_ASM2

///// max, max_indx, max_abs, max_abs_indx /////
template<typename T>
static inline IppStatus max(const T*, int, T*);
template<typename T>
static inline IppStatus max_indx(const T*, int, T*, int*);
template<typename T>
static inline IppStatus max_abs(const T*, int, T*);
template<typename T>
static inline IppStatus max_abs_indx(const T*, int, T*, int*);


#define MAX_ASM(Suffix)\
template<>\
static inline IppStatus max(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *max_)\
{ return ippsMax_##Suffix(src, len, max_); }


#define MAX_INDX_ASM(Suffix)\
template<>\
static inline IppStatus max_indx(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *max_, int *indx)\
{ return ippsMaxIndx_##Suffix(src, len, max_, indx); }


#define MAX_ABS_ASM(Suffix)\
template<>\
static inline IppStatus max_abs(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *max_)\
{ return ippsMaxAbs_##Suffix(src, len, max_); }


#define MAX_ABS_INDX_ASM(Suffix)\
template<>\
static inline IppStatus max_abs_indx(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *max_, int *indx)\
{ return ippsMaxAbsIndx_##Suffix(src, len, max_, indx); }


MAX_ASM(16s);
MAX_ASM(32s);
MAX_ASM(32f);
MAX_ASM(64f);

MAX_INDX_ASM(16s);
MAX_INDX_ASM(32s);
MAX_INDX_ASM(32f);
MAX_INDX_ASM(64f);


MAX_ABS_ASM(16s);
MAX_ABS_ASM(32s);

MAX_ABS_INDX_ASM(16s);
MAX_ABS_INDX_ASM(32s);

#undef MAX_ASM
#undef MAX_INDX_ASM
#undef MAX_ABS_ASM
#undef MAX_ABS_INDX_ASM

///// min, min_indx, min_abs, min_abs_indx /////
template<typename T>
static inline IppStatus min(const T*, int, T*);
template<typename T>
static inline IppStatus min_indx(const T*, int, T*, int*);
template<typename T>
static inline IppStatus min_abs(const T*, int, T*);
template<typename T>
static inline IppStatus min_abs_indx(const T*, int, T*, int*);


#define MIN_ASM(Suffix)\
template<>\
static inline IppStatus min(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *min_)\
{ return ippsMin_##Suffix(src, len, min_); }


#define MIN_INDX_ASM(Suffix)\
template<>\
static inline IppStatus min_indx(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *min_, int *indx)\
{ return ippsMinIndx_##Suffix(src, len, min_, indx); }


#define MIN_ABS_ASM(Suffix)\
template<>\
static inline IppStatus min_abs(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *min_)\
{ return ippsMinAbs_##Suffix(src, len, min_); }


#define MIN_ABS_INDX_ASM(Suffix)\
template<>\
static inline IppStatus min_abs_indx(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *min_, int *indx)\
{ return ippsMinAbsIndx_##Suffix(src, len, min_, indx); }


MIN_ASM(16s);
MIN_ASM(32s);
MIN_ASM(32f);
MIN_ASM(64f);

MIN_INDX_ASM(16s);
MIN_INDX_ASM(32s);
MIN_INDX_ASM(32f);
MIN_INDX_ASM(64f);


MIN_ABS_ASM(16s);
MIN_ABS_ASM(32s);

MIN_ABS_INDX_ASM(16s);
MIN_ABS_INDX_ASM(32s);

#undef MIN_ASM
#undef MIN_INDX_ASM
#undef MIN_ABS_ASM
#undef MIN_ABS_INDX_ASM


////// min_max, min_max_indx ////////
template<typename T>
static inline IppStatus min_max(const T*, int, T*, T*);

template<typename T>
static inline IppStatus min_max_indx(const T*, int, T*, int*, T*, int*);

#define MIN_MAX_ASM(Suffix)\
template<>\
static inline IppStatus min_max<Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *min_, Ipp##Suffix *max_)\
{ return ippsMinMax_##Suffix(src, len, min_, max_); }


#define MIN_MAX_INDX_ASM(Suffix)\
template<>\
static inline IppStatus min_max_indx<Ipp##Suffix>(\
        const Ipp##Suffix *src, int len,\
        Ipp##Suffix *min_, int *min_indx,\
        Ipp##Suffix *max_, int *max_indx)\
{ return ippsMinMaxIndx_##Suffix(\
        src, len, min_, min_indx, max_, max_indx); }


MIN_MAX_ASM(8u);
MIN_MAX_ASM(16u);
MIN_MAX_ASM(16s);
MIN_MAX_ASM(32u);
MIN_MAX_ASM(32s);
MIN_MAX_ASM(32f);
MIN_MAX_ASM(64f);

MIN_MAX_INDX_ASM(8u);
MIN_MAX_INDX_ASM(16u);
MIN_MAX_INDX_ASM(16s);
MIN_MAX_INDX_ASM(32u);
MIN_MAX_INDX_ASM(32s);
MIN_MAX_INDX_ASM(32f);
MIN_MAX_INDX_ASM(64f);

#undef MIN_MAX_ASM
#undef MIN_MAX_INDX_ASM


////// mean /////////
template<typename T>
static inline IppStatus mean(const T*, int, T*, IppHintAlgorithm);

template<typename T>
static inline IppStatus mean(const T*, int, T*, int);


template<>
static inline IppStatus mean<Ipp32f>(
        const Ipp32f *src, int len, Ipp32f *mean_, IppHintAlgorithm hint)
{ return ippsMean_32f(src, len, mean_, hint); }

template<>
static inline IppStatus mean<Ipp32fc>(
        const Ipp32fc *src, int len, Ipp32fc *mean_, IppHintAlgorithm hint)
{ return ippsMean_32fc(src, len, mean_, hint); }


#define MEAN_ASM1(Suffix)\
template<>\
static inline IppStatus mean<Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *mean_, int scale)\
{ return ippsMean_##Suffix##_Sfs(src, len, mean_, scale); }

#define MEAN_ASM2(Suffix)\
template<>\
static inline IppStatus mean<Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *mean_, int scale)\
{ return ippsMean_##Suffix(src, len, mean_); }


MEAN_ASM1(16s);
MEAN_ASM1(32s);
MEAN_ASM1(16sc);
MEAN_ASM2(64f);
MEAN_ASM2(64fc);

#undef MEAN_ASM1
#undef MEAN_ASM2

////// std_dev /////////
template<typename T>
static inline IppStatus std_dev(const T*, int, T*, IppHintAlgorithm);

template<typename T>
static inline IppStatus std_dev(const T*, int, T*, int);


template<>
static inline IppStatus std_dev<Ipp32f>(
        const Ipp32f *src, int len, Ipp32f *std_dev_, IppHintAlgorithm hint)
{ return ippsStdDev_32f(src, len, std_dev_, hint); }


#define STD_DEV_ASM1(Suffix)\
template<>\
static inline IppStatus std_dev<Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *std_dev_, int scale)\
{ return ippsStdDev_##Suffix##_Sfs(src, len, std_dev_, scale); }

#define STD_DEV_ASM2(Suffix)\
template<>\
static inline IppStatus std_dev<Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *std_dev_, int scale)\
{ return ippsStdDev_##Suffix(src, len, std_dev_); }


STD_DEV_ASM1(16s);
STD_DEV_ASM2(64f);

#undef STD_DEV_ASM1
#undef STD_DEV_ASM2


////// mean_std_dev /////////
template<typename T>
static inline IppStatus mean_std_dev(const T*, int, T*, T*, IppHintAlgorithm);

template<typename T>
static inline IppStatus mean_std_dev(const T*, int, T*, T*, int);


template<>
static inline IppStatus mean_std_dev<Ipp32f>(
        const Ipp32f *src, int len, Ipp32f *mean_, Ipp32f *std_dev_, IppHintAlgorithm hint)
{ return ippsMeanStdDev_32f(src, len, mean_, std_dev_, hint); }


#define MEAN_STD_DEV_ASM1(Suffix)\
template<>\
static inline IppStatus mean_std_dev<Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *mean_, Ipp##Suffix *std_dev_, int scale)\
{ return ippsMeanStdDev_##Suffix##_Sfs(src, len, mean_, std_dev_, scale); }

#define MEAN_STD_DEV_ASM2(Suffix)\
template<>\
static inline IppStatus mean_std_dev<Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *mean_, Ipp##Suffix* std_dev_, int scale)\
{ return ippsMeanStdDev_##Suffix(src, len, mean_, std_dev_); }


MEAN_STD_DEV_ASM1(16s);
MEAN_STD_DEV_ASM2(64f);

#undef MEAN_STD_DEV_ASM1
#undef MEAN_STD_DEV_ASM2

///// norm_inf, norm_l1, norm_l2, norm_l2_sqr //////
template<typename T1, typename T2>
static inline IppStatus norm_inf(const T1*, int, T2 *);
template<typename T1, typename T2>
static inline IppStatus norm_l1(const T1*, int, T2 *);
template<typename T1, typename T2>
static inline IppStatus norm_l2(const T1*, int, T2 *);
template<typename T1, typename T2>
static inline IppStatus norm_l2_sqr(const T1*, int, T2 *, int);

#define NORM_ASM1(Suffix, Which1, Which2)\
template<>\
static inline IppStatus norm_##Which2<Ipp##Suffix, Ipp##Suffix>(\
        const Ipp##Suffix *src, int len, Ipp##Suffix *norm_)\
{ return ippsNorm_##Which1##_##Suffix(src, len, norm_); }

#define NORM_ASM2(Suffix1, Suffix2, Which1, Which2)\
template<>\
static inline IppStatus norm_##Which2<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src, int len, Ipp##Suffix2 *norm_)\
{ return ippsNorm_##Which1##_##Suffix1##Suffix2(src, len, norm_); }

template<>
static inline IppStatus norm_l2_sqr<Ipp16s, Ipp64s>(
        const Ipp16s* src, int len, Ipp64s *norm_, int scale)
{ return ippsNorm_L2Sqr_16s64s_Sfs(src, len, norm_, scale); }


NORM_ASM1(32f, Inf, inf);
NORM_ASM1(64f, Inf, inf);
NORM_ASM2(16s, 32f, Inf, inf);
NORM_ASM2(32fc, 32f, Inf, inf);
NORM_ASM2(64fc, 64f, Inf, inf);

NORM_ASM1(32f, L2, l2);
NORM_ASM1(64f, L2, l2);
NORM_ASM2(16s, 32f, L2, l2);
NORM_ASM2(32fc, 64f, L2, l2);
NORM_ASM2(64fc, 64f, L2, l2);

NORM_ASM1(32f, L1, l1);
NORM_ASM1(64f, L1, l1);
NORM_ASM2(16s, 32f, L1, l1);
NORM_ASM2(32fc, 64f, L1, l1);
NORM_ASM2(64fc, 64f, L1, l1);


#undef NORM_ASM1
#undef NORM_ASM2


///// norm_diff_inf, norm_diff_l1, norm_diff_l2, norm_diff_l2_sqr //////
template<typename T1, typename T2>
static inline IppStatus norm_diff_inf(const T1*, const T1*, int, T2 *);
template<typename T1, typename T2>
static inline IppStatus norm_diff_l1(const T1*, const T1*, int, T2 *);
template<typename T1, typename T2>
static inline IppStatus norm_diff_l2(const T1*, const T1*, int, T2 *);
template<typename T1, typename T2>
static inline IppStatus norm_diff_l2_sqr(const T1*, const T1*, int, T2 *, int);

#define NORM_DIFF_ASM1(Suffix, Which1, Which2)\
template<>\
static inline IppStatus norm_diff_##Which2<Ipp##Suffix, Ipp##Suffix>(\
        const Ipp##Suffix *src1, const Ipp##Suffix *src2, int len, Ipp##Suffix *norm_)\
{ return ippsNormDiff_##Which1##_##Suffix(src1, src2, len, norm_); }

#define NORM_DIFF_ASM2(Suffix1, Suffix2, Which1, Which2)\
template<>\
static inline IppStatus norm_diff_##Which2<Ipp##Suffix1, Ipp##Suffix2>(\
        const Ipp##Suffix1 *src1, const Ipp##Suffix1 *src2, int len, Ipp##Suffix2 *norm_)\
{ return ippsNormDiff_##Which1##_##Suffix1##Suffix2(src1, src2, len, norm_); }

template<>
static inline IppStatus norm_diff_l2_sqr<Ipp16s, Ipp64s>(
        const Ipp16s* src1, const Ipp16s *src2, int len, Ipp64s *norm_, int scale)
{ return ippsNormDiff_L2Sqr_16s64s_Sfs(src1, src2, len, norm_, scale); }


NORM_DIFF_ASM1(32f, Inf, inf);
NORM_DIFF_ASM1(64f, Inf, inf);
NORM_DIFF_ASM2(16s, 32f, Inf, inf);
NORM_DIFF_ASM2(32fc, 32f, Inf, inf);
NORM_DIFF_ASM2(64fc, 64f, Inf, inf);

NORM_DIFF_ASM1(32f, L2, l2);
NORM_DIFF_ASM1(64f, L2, l2);
NORM_DIFF_ASM2(16s, 32f, L2, l2);
NORM_DIFF_ASM2(32fc, 64f, L2, l2);
NORM_DIFF_ASM2(64fc, 64f, L2, l2);

NORM_DIFF_ASM1(32f, L1, l1);
NORM_DIFF_ASM1(64f, L1, l1);
NORM_DIFF_ASM2(16s, 32f, L1, l1);
NORM_DIFF_ASM2(32fc, 64f, L1, l1);
NORM_DIFF_ASM2(64fc, 64f, L1, l1);


#undef NORM_DIFF_ASM1
#undef NORM_DIFF_ASM2



//// dot_prod ////////
template<typename T1, typename T2, typename T3>
static inline IppStatus dot_prod(const T1*, const T2*, int, T3*);

#define DOT_PROD_ASM(Suffix1, Suffix2, Suffix3, FSuffix)\
template<>\
static inline IppStatus dot_prod<Ipp##Suffix1, Ipp##Suffix2, Ipp##Suffix3>(\
        const Ipp##Suffix1 *src1, const Ipp##Suffix2 *src2, int len, Ipp##Suffix3 *dp)\
{ return ippsDotProd_##FSuffix(src1, src2, len, dp); }

DOT_PROD_ASM(32f, 32f, 32f, 32f);
DOT_PROD_ASM(32fc, 32fc, 32fc, 32fc);
DOT_PROD_ASM(32f, 32fc, 32fc, 32f32fc);
DOT_PROD_ASM(32f, 32f, 64f, 32f64f);
DOT_PROD_ASM(32fc, 32fc, 64fc, 32fc64fc);
DOT_PROD_ASM(32f, 32fc, 64fc, 32f32fc64fc);
DOT_PROD_ASM(64f, 64f, 64f, 64f);
DOT_PROD_ASM(64fc, 64fc, 64fc, 64fc);
DOT_PROD_ASM(64f, 64fc, 64fc, 64f64fc);
DOT_PROD_ASM(16s, 16s, 64s, 16s64s);
DOT_PROD_ASM(16sc, 16sc, 64sc, 16sc64sc);
DOT_PROD_ASM(16s, 16sc, 64sc, 16s16sc64sc);
DOT_PROD_ASM(16s, 16s, 32f, 16s32f);

#undef DOT_PROD_ASM


///// max_every, min_every /////////
template<typename T>
static inline IppStatus max_every(const T*, const T*, T *, int);
template<typename T>
static inline IppStatus min_every(const T*, const T*, T *, int);
template<typename T>
static inline IppStatus max_every(const T*, T *, int);
template<typename T>
static inline IppStatus min_every(const T*, T *, int);

#define MAX_EVERY_ASM(Suffix)\
template<>\
static inline IppStatus max_every<Ipp##Suffix>(\
        const Ipp##Suffix *src1, const Ipp##Suffix *src2, Ipp##Suffix *dst, int len)\
{ return src1 == dst ? ippsMaxEvery_##Suffix##_I(src2, dst, len)\
                     : (src2 == dst ? ippsMaxEvery_##Suffix##_I(src1, dst, len)\
                                    : ippsMaxEvery_##Suffix(src1, src2, dst, len)); }


template<>
static inline IppStatus max_every<Ipp16s>(const Ipp16s *src, Ipp16s *srcdst, int len)
{ return ippsMaxEvery_16s_I(src, srcdst, len); }
template<>
static inline IppStatus max_every<Ipp32s>(const Ipp32s *src, Ipp32s *srcdst, int len)
{ return ippsMaxEvery_32s_I(src, srcdst, len); }

#define MIN_EVERY_ASM(Suffix)\
template<>\
static inline IppStatus min_every<Ipp##Suffix>(\
        const Ipp##Suffix *src1, const Ipp##Suffix *src2, Ipp##Suffix *dst, int len)\
{ return src1 == dst ? ippsMinEvery_##Suffix##_I(src2, dst, len)\
                     : (src2 == dst ? ippsMinEvery_##Suffix##_I(src1, dst, len)\
                                    : ippsMinEvery_##Suffix(src1, src2, dst, len)); }

template<>
static inline IppStatus min_every<Ipp16s>(const Ipp16s *src, Ipp16s *srcdst, int len)
{ return ippsMinEvery_16s_I(src, srcdst, len); }
template<>
static inline IppStatus min_every<Ipp32s>(const Ipp32s *src, Ipp32s *srcdst, int len)
{ return ippsMinEvery_32s_I(src, srcdst, len); }

MAX_EVERY_ASM(8u);
MAX_EVERY_ASM(16u);
MAX_EVERY_ASM(32f);
MAX_EVERY_ASM(64f);
MIN_EVERY_ASM(8u);
MIN_EVERY_ASM(16u);
MIN_EVERY_ASM(32f);
MIN_EVERY_ASM(64f);

#undef MAX_EVERY_ASM
#undef MIN_EVERY_ASM



////// count_in_range ////////
template<typename T>
static inline IppStatus count_in_range(const T*, int, int*, T, T);

template<>
static inline IppStatus count_in_range<Ipp32s>(
        const Ipp32s* src, int len, int* count, Ipp32s lower, Ipp32s upper)
{ return ippsCountInRange_32s(src, len, count, lower, upper); }




///// sample_up, sample_down //////////
template<typename T>
static inline IppStatus sample_up(const T*, int, T*, int*, int, int *);
template<typename T>
static inline IppStatus sample_down(const T*, int, T*, int*, int, int *);

#define SAMPLE_UP_ASM(Suffix)\
template<>\
static inline IppStatus sample_up<Ipp##Suffix>(\
        const Ipp##Suffix *src, int src_len, Ipp##Suffix* dst, int *dst_len, int factor, int *phase)\
{ return ippsSampleUp_##Suffix(src, src_len, dst, dst_len, factor, phase); }

#define SAMPLE_DOWN_ASM(Suffix)\
template<>\
static inline IppStatus sample_down<Ipp##Suffix>(\
        const Ipp##Suffix *src, int src_len, Ipp##Suffix* dst, int *dst_len, int factor, int *phase)\
{ return ippsSampleDown_##Suffix(src, src_len, dst, dst_len, factor, phase); }


SAMPLE_UP_ASM(16s);
SAMPLE_UP_ASM(32f);
SAMPLE_UP_ASM(64f);
SAMPLE_UP_ASM(16sc);
SAMPLE_UP_ASM(32fc);
SAMPLE_UP_ASM(64fc);

SAMPLE_DOWN_ASM(16s);
SAMPLE_DOWN_ASM(32f);
SAMPLE_DOWN_ASM(64f);
SAMPLE_DOWN_ASM(16sc);
SAMPLE_DOWN_ASM(32fc);
SAMPLE_DOWN_ASM(64fc);


#undef SAMPLE_UP_ASM
#undef SAMPLE_DOWN_ASM


///// auto_corr_norm //////////
static inline IppStatus auto_corr_norm_get_buffer_size(
        int slen, int dlen, IppDataType type, IppEnum alg, int *bsize)
{ return ippsAutoCorrNormGetBufferSize(slen, dlen, type, alg, bsize); }

template<typename T>
static inline IppStatus do_auto_corr_norm(
        const T*, int, T*, int, IppEnum, Ipp8u*);

#define AUTO_CORR_NORM_ASM(Suffix)\
template<>\
static inline IppStatus do_auto_corr_norm<Ipp##Suffix>(\
        const Ipp##Suffix *src, int slen, Ipp##Suffix *dst, int dlen, IppEnum alg, Ipp8u *buffer)\
{ return ippsAutoCorrNorm_##Suffix(src, slen, dst, dlen, alg, buffer); }

AUTO_CORR_NORM_ASM(32f);
AUTO_CORR_NORM_ASM(64f);
AUTO_CORR_NORM_ASM(32fc);
AUTO_CORR_NORM_ASM(64fc);

#undef AUTO_CORR_NORM_ASM




///// cross_corr_norm //////////
static inline IppStatus cross_corr_norm_get_buffer_size(
        int s1len, int s2len, int dlen, int low_lag, IppDataType type, IppEnum alg, int *bsize)
{
	return ippsCrossCorrNormGetBufferSize(s1len, s2len, dlen, low_lag, type, alg, bsize);
}

template<typename T>
static inline IppStatus do_cross_corr_norm(
        const T*, int, const T*, int, T*, int, int, IppEnum, Ipp8u*);

#define CROSS_CORR_NORM_ASM(Suffix)\
template<>\
static inline IppStatus do_cross_corr_norm<Ipp##Suffix>(\
        const Ipp##Suffix *src1, int s1len, const Ipp##Suffix *src2, int s2len,\
        Ipp##Suffix *dst, int dlen, int low_lag, IppEnum alg, Ipp8u *buffer)\
{ return ippsCrossCorrNorm_##Suffix(src1, s1len, src2, s2len, dst, dlen, low_lag, alg, buffer); }

CROSS_CORR_NORM_ASM(32f);
CROSS_CORR_NORM_ASM(64f);
CROSS_CORR_NORM_ASM(32fc);
CROSS_CORR_NORM_ASM(64fc);

#undef CROSS_CORR_NORM_ASM



///// convolve //////////
static inline IppStatus convolve_get_buffer_size(
        int s1len, int s2len, IppDataType type, IppEnum alg, int *bsize)
{
	return ippsConvolveGetBufferSize(s1len, s2len, type, alg, bsize);
}

template<typename T>
static inline IppStatus do_convolve(
        const T*, int, const T*, int, T*, IppEnum, Ipp8u*);

#define CONVOLVE_ASM(Suffix)\
template<>\
static inline IppStatus do_convolve<Ipp##Suffix>(\
        const Ipp##Suffix *src1, int s1len, const Ipp##Suffix *src2, int s2len,\
        Ipp##Suffix *dst, IppEnum alg, Ipp8u *buffer)\
{ return ippsConvolve_##Suffix(src1, s1len, src2, s2len, dst, alg, buffer); }

CONVOLVE_ASM(32f);
CONVOLVE_ASM(64f);

#undef CONVOLVE_ASM



///// conv_biased /////
template<typename T>
static inline IppStatus conv_biased(
        const T*, int, const T*, int, T*, int, int);


template<>
static inline IppStatus conv_biased<Ipp32f>(
        const Ipp32f *src1, int s1len, const Ipp32f *src2, int s2len,
        Ipp32f *dst, int dlen, int bias)
{ return ippsConvBiased_32f(src1, s1len, src2, s2len, dst, dlen, bias); }







///// fft ///////

template<typename T, bool IsCplx>
struct fft_spec;

#define FFT_SPEC_ASM(Suffix, RC, IsCplx)\
template<>\
struct fft_spec<Ipp##Suffix, IsCplx>\
{ typedef IppsFFTSpec_##RC##_##Suffix type; }

FFT_SPEC_ASM(32f, R, false);
FFT_SPEC_ASM(64f, R, false);
FFT_SPEC_ASM(32f, C, true);
FFT_SPEC_ASM(64f, C, true);
FFT_SPEC_ASM(32fc, C, true);
FFT_SPEC_ASM(64fc, C, true);

#undef FFT_SPEC_ASM


template<typename T, bool IsCplx>
static inline IppStatus fft_get_size(
        int, int, IppHintAlgorithm, int*, int*, int*);


#define FFT_GET_SIZE_ASM(Suffix, RC, IsCplx)\
template<>\
static inline IppStatus fft_get_size<Ipp##Suffix, IsCplx>(\
        int order, int flag, IppHintAlgorithm hint, int *ssize, int *sbsize, int *bsize)\
{ return ippsFFTGetSize_##RC##_##Suffix(order, flag, hint, ssize, sbsize, bsize); }

FFT_GET_SIZE_ASM(32f, R, false);
FFT_GET_SIZE_ASM(64f, R, false);
FFT_GET_SIZE_ASM(32f, C, true);
FFT_GET_SIZE_ASM(64f, C, true);
FFT_GET_SIZE_ASM(32fc, C, true);
FFT_GET_SIZE_ASM(64fc, C, true);

#undef FFT_GET_SIZE_ASM


template<typename IT, typename Spec>
static inline IppStatus fft_init(
        Spec **, int, int, IppHintAlgorithm, Ipp8u*, Ipp8u*);

#define FFT_INIT_ASM(Suffix, RC)\
template<>\
static inline IppStatus fft_init<Ipp##Suffix, IppsFFTSpec_##RC##_##Suffix>(\
        IppsFFTSpec_##RC##_##Suffix **spec, int order, int flag, IppHintAlgorithm hint,\
        Ipp8u *p_spec, Ipp8u* spec_buf)\
{ return ippsFFTInit_##RC##_##Suffix(spec, order, flag, hint, p_spec, spec_buf); }

FFT_INIT_ASM(32f, R);
FFT_INIT_ASM(64f, R);
FFT_INIT_ASM(32f, C);
FFT_INIT_ASM(64f, C);
FFT_INIT_ASM(32fc, C);
FFT_INIT_ASM(64fc, C);

#undef FFT_INIT_ASM


template<typename T, typename Spec, bool IsCplx>
static inline IppStatus fft_inverse(
        const T *, const T*, T*, T*, Spec *, Ipp8u*);

template<typename T, typename Spec, bool IsCplx>
static inline IppStatus fft_inverse(
        const T *, T*, Spec *, Ipp8u*);


#define FFT_INVERSE_ASM(Suffix, F, T, IsCplx)\
template<>\
static inline IppStatus fft_inverse<Ipp##Suffix, IppsFFTSpec_##F##_##Suffix, IsCplx>(\
    const Ipp##Suffix *sre, const Ipp##Suffix *sim, Ipp##Suffix *dre, Ipp##Suffix *dim, \
    IppsFFTSpec_##F##_##Suffix *spec, Ipp8u *buf)\
{ return (sre == dre && sim == dim) ? ippsFFTInv_##F##To##T##_##Suffix##_I(dre, dim, spec, buf)\
                                    : ippsFFTInv_##F##To##T##_##Suffix(sre, sim, dre, dim, spec, buf); }

#define FFT_INVERSE_2_ASM(Suffix, F, T, IsCplx)\
template<>\
static inline IppStatus fft_inverse<Ipp##Suffix, IppsFFTSpec_##T##_##Suffix, IsCplx>(\
    const Ipp##Suffix *src, Ipp##Suffix *dst, \
    IppsFFTSpec_##T##_##Suffix *spec, Ipp8u *buf)\
{ return (src == dst) ? ippsFFTInv_##F##To##T##_##Suffix##_I(dst, spec, buf)\
                      : ippsFFTInv_##F##To##T##_##Suffix(src, dst, spec, buf); }


FFT_INVERSE_ASM(32f, C, C, true);
FFT_INVERSE_ASM(64f, C, C, true);

FFT_INVERSE_2_ASM(32fc, C, C, true);
FFT_INVERSE_2_ASM(64fc, C, C, true);

FFT_INVERSE_2_ASM(32f, Perm, R, false);
FFT_INVERSE_2_ASM(64f, Perm, R, false);

#undef FFT_INVERSE_ASM
#undef FFT_INVERSE_2_ASM

template<typename T, typename Spec, bool IsCplx>
static inline IppStatus fft_forward(
        const T *, const T*, T*, T*, Spec *, Ipp8u*);

template<typename T, typename Spec, bool IsCplx>
static inline IppStatus fft_forward(
        const T *, T*, Spec *, Ipp8u*);


#define FFT_FORWARD_ASM(Suffix, F, T, IsCplx)\
template<>\
static inline IppStatus fft_forward<Ipp##Suffix, IppsFFTSpec_##F##_##Suffix, IsCplx>(\
    const Ipp##Suffix *sre, const Ipp##Suffix *sim, Ipp##Suffix *dre, Ipp##Suffix *dim, \
    IppsFFTSpec_##F##_##Suffix *spec, Ipp8u *buf)\
{ return (sre == dre && sim == dim) ? ippsFFTFwd_##F##To##T##_##Suffix##_I(dre, dim, spec, buf)\
                                    : ippsFFTFwd_##F##To##T##_##Suffix(sre, sim, dre, dim, spec, buf); }

#define FFT_FORWARD_2_ASM(Suffix, F, T, IsCplx)\
template<>\
static inline IppStatus fft_forward<Ipp##Suffix, IppsFFTSpec_##F##_##Suffix, IsCplx>(\
    const Ipp##Suffix *src, Ipp##Suffix *dst, \
    IppsFFTSpec_##F##_##Suffix *spec, Ipp8u *buf)\
{ return (src == dst) ? ippsFFTFwd_##F##To##T##_##Suffix##_I(dst, spec, buf)\
                      : ippsFFTFwd_##F##To##T##_##Suffix(src, dst, spec, buf); }


FFT_FORWARD_ASM(32f, C, C, true);
FFT_FORWARD_ASM(64f, C, C, true);

FFT_FORWARD_2_ASM(32fc, C, C, true);
FFT_FORWARD_2_ASM(64fc, C, C, true);

FFT_FORWARD_2_ASM(32f, R, Perm, false);
FFT_FORWARD_2_ASM(64f, R, Perm, false);

#undef FFT_FORWARD_ASM
#undef FFT_FORWARD_2_ASM


// fir sr ///
template<typename T>
static void fir_sr_get_size(int tap_len, int *spec_size, int *buf_size);

template<>
static void fir_sr_get_size<Ipp32f>(int tap_len, int *spec_size, int *buf_size)
{
    ippsFIRSRGetSize(tap_len, ipp32f, spec_size, buf_size);
}

template<>
static void fir_sr_get_size<Ipp64f>(int tap_len, int *spec_size, int *buf_size)
{
    ippsFIRSRGetSize(tap_len, ipp64f, spec_size, buf_size);
}


template<typename T>
static int fir_sr_init(const T*, int, IppAlgType, void*);

template<>
static int fir_sr_init<Ipp32f>(const Ipp32f *taps, int tap_len, IppAlgType alg, void *spec)
{
    return ippsFIRSRInit_32f(taps, tap_len, alg, (IppsFIRSpec_32f*)spec);
}

template<>
static int fir_sr_init<Ipp64f>(const Ipp64f *taps, int tap_len, IppAlgType alg, void *spec)
{
    return ippsFIRSRInit_64f(taps, tap_len, alg, (IppsFIRSpec_64f*)spec);
}


template<typename T>
static IppStatus fir_sr_filter(const T*, T*, int, void *, const T*, T*, Ipp8u*);

template<>
static IppStatus fir_sr_filter<Ipp32f>(
        const Ipp32f *src, Ipp32f *dst, int n, void *spec, 
        const Ipp32f *sdly, Ipp32f *ddly, Ipp8u *buf)
{
    return ippsFIRSR_32f(src, dst, n, (IppsFIRSpec_32f*)spec, sdly, ddly, buf);
}

template<>
static IppStatus fir_sr_filter<Ipp64f>(
        const Ipp64f *src, Ipp64f *dst, int n, void *spec, 
        const Ipp64f *sdly, Ipp64f *ddly, Ipp8u *buf)
{
    return ippsFIRSR_64f(src, dst, n, (IppsFIRSpec_64f*)spec, sdly, ddly, buf);
}


//fir, fir_mr
template<typename T>
static void fir_get_state_size(int tap_len, int *buf_size);

template<typename T>
static IppStatus fir_init(void **, const T*, int, const T*, Ipp8u*);


template<typename T>
static void fir_mr_get_state_size(int, int, int, int *);

template<typename T>
static IppStatus fir_mr_init(void **, const T* , int, 
        int, int, int, int, 
        const T* , Ipp8u *);


template<typename T>
static IppStatus fir_filter(const T*, T*, int n, void *);

#define FIR_GET_STATE_SIZE_ASM(Suffix)\
template<>\
static void fir_get_state_size<Ipp##Suffix>(int tap_len, int *buf_size)\
{\
    ippsFIRGetStateSize_##Suffix(tap_len, buf_size);\
}


#define FIR_INIT_ASM(Suffix)\
template<>\
static IppStatus fir_init<Ipp##Suffix>(void **state, const Ipp##Suffix *taps, int tap_len, \
        const Ipp##Suffix *dly, Ipp8u *work_buf)\
{\
    return ippsFIRInit_##Suffix((IppsFIRState_##Suffix**)state, taps, tap_len, \
            dly, work_buf);\
}


#define FIR_MR_GET_STATE_SIZE_ASM(Suffix)\
template<>\
static void fir_mr_get_state_size<Ipp##Suffix>(\
        int tap_len, int up_factor, int down_factor, int *buf_size)\
{\
    ippsFIRMRGetStateSize_##Suffix(tap_len, up_factor, down_factor, buf_size);\
}

#define FIR_MR_INIT_ASM(Suffix)\
template<>\
static IppStatus fir_mr_init<Ipp##Suffix>(void ** state, const Ipp##Suffix* taps, int tap_len, \
        int up_factor, int up_phase, int down_factor, int down_phase, \
        const Ipp##Suffix* dly, Ipp8u *work_buf)\
{\
    return ippsFIRMRInit_##Suffix((IppsFIRState_##Suffix**)state,\
            taps, tap_len, up_factor, up_phase, down_factor, down_phase, dly, work_buf);\
}


#define FIR_FILTER_ASM(Suffix)\
template<>\
static IppStatus fir_filter<Ipp##Suffix>(const Ipp##Suffix *src, Ipp##Suffix *dst, int n, \
        void *state)\
{\
    return src != dst ? ippsFIR_##Suffix(src, dst, n, (IppsFIRState_##Suffix*)state)\
                      : ippsFIR_##Suffix##_I(dst, n, (IppsFIRState_##Suffix*)state);\
}


FIR_GET_STATE_SIZE_ASM(32f)
FIR_GET_STATE_SIZE_ASM(32fc)
FIR_GET_STATE_SIZE_ASM(64f)
FIR_GET_STATE_SIZE_ASM(64fc)

FIR_INIT_ASM(32f)
FIR_INIT_ASM(32fc)
FIR_INIT_ASM(64f)
FIR_INIT_ASM(64fc)

FIR_MR_GET_STATE_SIZE_ASM(32f)
FIR_MR_GET_STATE_SIZE_ASM(32fc)
FIR_MR_GET_STATE_SIZE_ASM(64f)
FIR_MR_GET_STATE_SIZE_ASM(64fc)

FIR_MR_INIT_ASM(32f)
FIR_MR_INIT_ASM(32fc)
FIR_MR_INIT_ASM(64f)
FIR_MR_INIT_ASM(64fc)

FIR_FILTER_ASM(32f)
FIR_FILTER_ASM(32fc)
FIR_FILTER_ASM(64f)
FIR_FILTER_ASM(64fc)


//polyphase resampling
template<typename T>
static void resample_polyphase_get_size(
        Ipp32f, int, int *, IppHintAlgorithm);

template<>
static void resample_polyphase_get_size<Ipp16s>(
        Ipp32f win, int nstep, int *psize, IppHintAlgorithm hint)
{
    ippsResamplePolyphaseGetSize_16s(win, nstep, psize, hint);
}

template<>
static void resample_polyphase_get_size<Ipp32f>(
        Ipp32f win, int nstep, int *psize, IppHintAlgorithm hint)
{
    ippsResamplePolyphaseGetSize_32f(win, nstep, psize, hint);
}

template<typename T>
static IppStatus resample_polyphase_init(
        Ipp32f, int, Ipp32f, Ipp32f, void*, IppHintAlgorithm);

template<>
static IppStatus resample_polyphase_init<Ipp16s>(
        Ipp32f win, int nstep, Ipp32f rollf, 
        Ipp32f alpha, void* spec, IppHintAlgorithm hint)
{
    return ippsResamplePolyphaseInit_16s(win, nstep, rollf, alpha, 
            (IppsResamplingPolyphase_16s*)spec, hint);
}

template<>
static IppStatus resample_polyphase_init<Ipp32f>(
        Ipp32f win, int nstep, Ipp32f rollf, 
        Ipp32f alpha, void* spec, IppHintAlgorithm hint)
{
    return ippsResamplePolyphaseInit_32f(win, nstep, rollf, alpha, 
            (IppsResamplingPolyphase_32f*)spec, hint);
}


template<typename T>
static IppStatus resample_polyphase(const T*, int, T*, Ipp64f, Ipp32f, 
        Ipp64f*, int *, const void*);

template<>
static IppStatus resample_polyphase<Ipp16s>(const Ipp16s* src, int ilen,
        Ipp16s *dst, Ipp64f factor, Ipp32f norm, 
        Ipp64f* time, int *olen, const void* spec)
{
    return ippsResamplePolyphase_16s(src, ilen, dst, factor, norm, 
            time, olen, (const IppsResamplingPolyphase_16s*)spec);
}

template<>
static IppStatus resample_polyphase<Ipp32f>(const Ipp32f* src, int ilen,
        Ipp32f *dst, Ipp64f factor, Ipp32f norm, 
        Ipp64f* time, int *olen, const void* spec)
{
    return ippsResamplePolyphase_32f(src, ilen, dst, factor, norm, 
            time, olen, (const IppsResamplingPolyphase_32f*)spec);
}



//polyphase resampling fixed
template<typename T>
static void resample_polyphase_fixed_get_size(
        int, int, int, int*, int*, int*, IppHintAlgorithm);

template<>
static void resample_polyphase_fixed_get_size<Ipp16s>(
        int in_rate, int out_rate, int len, 
        int* psize, int* plen, int *pheight, IppHintAlgorithm hint)
{
    ippsResamplePolyphaseFixedGetSize_16s(
            in_rate, out_rate, len, psize, plen, pheight, hint);
}

template<>
static void resample_polyphase_fixed_get_size<Ipp32f>(
        int in_rate, int out_rate, int len, 
        int* psize, int* plen, int *pheight, IppHintAlgorithm hint)
{
    ippsResamplePolyphaseFixedGetSize_32f(
            in_rate, out_rate, len, psize, plen, pheight, hint);
}

template<typename T>
static IppStatus resample_polyphase_fixed_init(
        int, int, int, Ipp32f, Ipp32f, void*, IppHintAlgorithm);

template<>
static IppStatus resample_polyphase_fixed_init<Ipp16s>(
        int in_rate, int out_rate, int len, 
        Ipp32f rollf, Ipp32f alpha, void* spec, IppHintAlgorithm hint)
{
    return ippsResamplePolyphaseFixedInit_16s(in_rate, out_rate, len,
            rollf, alpha, (IppsResamplingPolyphaseFixed_16s*)spec, hint);
}

template<>
static IppStatus resample_polyphase_fixed_init<Ipp32f>(
        int in_rate, int out_rate, int len, 
        Ipp32f rollf, Ipp32f alpha, void* spec, IppHintAlgorithm hint)
{
    return ippsResamplePolyphaseFixedInit_32f(in_rate, out_rate, len,
            rollf, alpha, (IppsResamplingPolyphaseFixed_32f*)spec, hint);
}


template<typename T>
static IppStatus resample_polyphase_fixed(const T*, int, T*, Ipp32f, 
        Ipp64f*, int *, const void*);

template<>
static IppStatus resample_polyphase_fixed<Ipp16s>(const Ipp16s* src, int ilen,
        Ipp16s *dst, Ipp32f norm, 
        Ipp64f* time, int *olen, const void* spec)
{
    return ippsResamplePolyphaseFixed_16s(src, ilen, dst, norm, 
            time, olen, (const IppsResamplingPolyphaseFixed_16s*)spec);
}

template<>
static IppStatus resample_polyphase_fixed<Ipp32f>(const Ipp32f* src, int ilen,
        Ipp32f *dst, Ipp32f norm, 
        Ipp64f* time, int *olen, const void* spec)
{
    return ippsResamplePolyphaseFixed_32f(src, ilen, dst, norm, 
            time, olen, (const IppsResamplingPolyphaseFixed_32f*)spec);
}


template<typename T>
static IppStatus resample_polyphase_fixed_filter(
        T*, int, int, void *);

template<>
static IppStatus resample_polyphase_fixed_filter<Ipp32f>(
        Ipp32f* src, int step, int height, void *spec)
{
    return ippsResamplePolyphaseGetFixedFilter_32f(
            src, step, height, (IppsResamplingPolyphaseFixed_32f*)spec); 
}

template<>
static IppStatus resample_polyphase_fixed_filter<Ipp16s>(
        Ipp16s* src, int step, int height, void *spec)
{
    return ippsResamplePolyphaseGetFixedFilter_16s(
            src, step, height, (IppsResamplingPolyphaseFixed_16s*)spec); 
}


}}

#endif

