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

SET_ASM(8u);
SET_ASM(16s);
SET_ASM(32s);
SET_ASM(64s);
SET_ASM(32f);
SET_ASM(64f);
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



}}

#endif

