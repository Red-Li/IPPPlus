/**
 * @file ipps.hpp
 * @Brief 
 * @author Red Li
 * @version 
 * @date 2014-12-19
 */

#ifndef IPPPLUS_IPPS_HPP
#define IPPPLUS_IPPS_HPP

#include <ipps.h>
#include <ippvm.h>

#include "ippcore.h"
#include "ipptype.hpp"
#include "ippcore.hpp"
#include "ipps_extension.hpp"
#include "detail/ipps.hpp"

#ifndef M_PI_2
#define M_PI_2 6.2831853071795864769252
#endif

namespace ipp{

/**
 * defgroup VectorInitFuncTop This chapter describes the Intel® IPP functions that initialize vectors with either constants, the contents of other vectors, or the generated signals. 
 */

/**
 * @defgroup VectorInitFunc Vector Initialization Functions
 * @ingroup VectorInitFuncTop
 * @{
 */


/* --------------------------------------------------------------------------*/
/**
 * @brief copies the contents of one vector into another 
 *
 * @tparam T 
 * @param src
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus copy(const T* src, T* dst, int len)
{
    return detail::copy<
        T, type_cat_index<T>::value, sizeof(T)>::do_copy(src, dst, len);
}


/* --------------------------------------------------------------------------*/
/**
 * @brief moves the contents of one vector to another vector
 *
 * @tparam T
 * @param src
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus move(const T* src, T* dst, int len)
{
    return detail::move<
        T, type_cat_index<T>::value, sizeof(T)>::do_move(src, dst, len);
}



/* --------------------------------------------------------------------------*/
/**
 * @brief Initializes vector elements to a specified common value.
 *
 * @tparam T
 * @param val
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus set(T val, T *dst, int len)
{
    typedef get<T>::type itype;
    return detail::set<itype>::do_set(
            *((itype*)&val), (itype*)dst, len);
}


/* --------------------------------------------------------------------------*/
/**
 * @brief Initializes a vector to zero.
 *
 * @tparam T
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus zero(T *dst, int len)
{
    typedef get<T>::type itype;
    return detail::zero<itype>::do_zero(
            (itype*)dst, len);
};


/**@}*/

/**
 * @defgroup SampleGenFunc
 * @ingroup VectorInitFuncTop
 * @{
 */


/* --------------------------------------------------------------------------*/
/**
 * @brief Generates the pseudo-random samples with a uniform distribution.
 *
 * @tparam T
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
class rand_uniform
{
    void *state_;

    rand_uniform(const rand_uniform &);   
    rand_uniform &operator=(const rand_uniform &);
public:
    typedef typename get<T>::type itype;

    rand_uniform(T low, T high, unsigned int seed)
    {
        int pRandUniStateSize = 0;
        detail::do_rand_uniform_get_size<itype>(&pRandUniStateSize);
        state_ = malloc<char>(pRandUniStateSize); 
        
        detail::do_rand_uniform_init<itype>(
                state_, (itype)low, (itype)high, seed); 
    }
    ~rand_uniform()
    {
        free(state_);
    }

    IppStatus generate(T *dst, int len)
    {
        return detail::do_rand_uniform((itype*)dst, len, state_);
    }
};


/* --------------------------------------------------------------------------*/
/**
 * @brief This section describes the function that generates pseudo-random samples with Gaussian distribution.
 *
 * @tparam T
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
class rand_gauss
{
    void *state_;

    rand_gauss(const rand_gauss &);   
    rand_gauss &operator=(const rand_gauss &);
public:
    typedef typename get<T>::type itype;

    rand_gauss(T mean, T std_dev, unsigned int seed)
    {
        int pRandGaussStateSize = 0;
        detail::do_rand_gauss_get_size<itype>(&pRandGaussStateSize);
        state_ = malloc<char>(pRandGaussStateSize); 
        
        detail::do_rand_gauss_init<itype>(
                state_, (itype)mean, (itype)std_dev, seed); 
    }
    ~rand_gauss()
    {
        free(state_);
    }

    inline IppStatus generate(T *dst, int len)
    {
        return detail::do_rand_gauss((itype*)dst, len, state_);
    }
};


/* --------------------------------------------------------------------------*/
/**
 * @brief Creates a Jaehne vector.
 * pDst[n] = magn * sin ((0.5πn2)/len), 0 <= n < len 
 *
 * @tparam T 
 * @param dst
 * @param len
 * @param magn
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus vector_jaehne(T *dst, int len, T magn)
{
    typedef get<T>::type itype;
    return detail::vector_jaehne<itype>::do_vector_jaehne(
            (itype*)dst, len, magn);
}


/* --------------------------------------------------------------------------*/
/**
 * @brief Creates a slope vector.
 * pDst[n] = offset + slope*n, 0 <= n < len.
 *
 * @tparam T
 * @param dst
 * @param len
 * @param offset
 * @param slope
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus vector_slope(
        T *dst, int len, double offset, double slope)
{
    typedef get<T>::type itype;
    return detail::vector_slope<itype>::do_vector_slope(
            (itype*)dst, len, offset, slope);
}

/**@}*/



/**
 * @defgroup EssentialFunctions  This section describes the Intel IPP signal processing functions that perform logical and shift operations on vectors. Logical and shift functions are only defined for integer arguments. 
 * */

/**
 * @defgroup LogicalShiftFunctions Logical and Shift Functions
 * @ingroup EssentialFunctions
 * @{
 **/




/* --------------------------------------------------------------------------*/
/**
 * @brief Computes the bitwise AND of a scalar value and each element of a vector.
 *
 * @tparam T
 * @param src
 * @param val
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus and_const(const T *src, T val, T *dst, int len)
{
    static_assert(is_integer<T>::value, "should be integer");
    typedef get_int<sizeof(T), false>::type itype;
    return detail::and_const(
            (const itype*)src, *(itype*)&val, (itype*)dst, len);
};


/* --------------------------------------------------------------------------*/
/**
 * @brief Computes the bitwise OR of a scalar value and each element of a vector.
 *
 * @tparam T
 * @param src
 * @param val
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus or_const(const T *src, T val, T *dst, int len)
{
    static_assert(is_integer<T>::value, "should be integer");
    typedef get_int<sizeof(T), false>::type itype;
    return detail::or_const((const itype*)src, *(itype*)&val,
                             (itype*)dst, len); 
};


/* --------------------------------------------------------------------------*/
/**
 * @brief Computes the bitwise XOR of a scalar value and each element of a vector.
 *
 * @tparam T
 * @param src
 * @param val
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus xor_const(const T *src, T val, T *dst, int len)
{
    static_assert(is_integer<T>::value, "should be integer");
    typedef get_int<sizeof(T), false>::type itype;
    return detail::xor_const((const itype*)src, *(itype*)&val,
                             (itype*)dst, len); 
};



template<typename T>
static inline IppStatus and(const T *src1, const T *src2, T *dst, int len)
{
    static_assert(is_integer<T>::value, "should be integer");
    typedef get_int<sizeof(T), false>::type itype;
    return detail::and((const itype*)src1, (const itype*)src2,
                              (itype*)dst, len); 

}


template<typename T>
static inline IppStatus or(const T *src1, const T *src2, T *dst, int len)
{
    static_assert(is_integer<T>::value, "should be integer");
    typedef get_int<sizeof(T), false>::type itype;
    return detail::or((const itype*)src1, (const itype*)src2,
                              (itype*)dst, len); 

}

template<typename T>
static inline IppStatus xor(const T *src1, const T *src2, T *dst, int len)
{
    static_assert(is_integer<T>::value, "should be integer");
    typedef get_int<sizeof(T), false>::type itype;
    return detail::xor((const itype*)src1, (const itype*)src2,
                              (itype*)dst, len); 

}


template<typename T>
static inline IppStatus not(const T *src, T *dst, int len)
{
    static_assert(is_integer<T>::value, "should be integer");
    typedef get_int<sizeof(T), false>::type itype;
    return detail::not((const itype*)src, (itype*)dst, len); 
}


template<typename T>
static inline IppStatus lshift_const(const T *src, int val, T *dst, int len)
{
    static_assert(is_integer<T>::value, "should be integer");
    typedef get<T>::type itype;
    return detail::lshift_const(
            (const itype*)src, val, (itype*)dst, len); 
}

template<typename T>
static inline IppStatus rshift_const(const T *src, int val, T *dst, int len)
{
    static_assert(is_integer<T>::value, "should be integer");
    typedef get<T>::type itype;
    return detail::rshift_const(
            (const itype*)src, val, (itype*)dst, len); 
}



/**@}*/


/**
 * @defgroup ArithmeticFunctions Arithmetic Functions
 * This section describes the Intel IPP signal processing functions that perform vector arithmetic operations on vectors. The arithmetic functions include basic element-wise arithmetic operations between vectors, as well as more complex calculations such as computing absolute values, square and square root, natural logarithm and exponential of vector elements.
 * @ingroup EssentialFunctions
 * @{
 **/


template<typename T>
static inline IppStatus add_const(const T *src, T val, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::add_const(
            (const itype*)src, *(itype*)&val, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus add_product_const(const T *src, T val, T *dst, int len)
{
    typedef get<T>::type itype;
    return detail::add_product_const(
            (const itype*)src, *(itype*)&val, (itype*)dst, len);
}


template<typename T>
static inline IppStatus mul_const(const T *src, T val, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::mul_const(
            (const itype*)src, *(itype*)&val, (itype*)dst, len, scale);
}


template<typename T>
static inline IppStatus sub_const(const T *src, T val, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::sub_const(
            (const itype*)src, *(itype*)&val, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus sub_const_rev(const T *src, T val, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::sub_const_rev(
            (const itype*)src, *(itype*)&val, (itype*)dst, len, scale);
}


template<typename T>
static inline IppStatus div_const(const T *src, T val, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::div_const(
            (const itype*)src, *(itype*)&val, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus div_const_rev(const T *src, T val, T *dst, int len)
{
    typedef get<T>::type itype;
    return detail::div_const_rev(
            (const itype*)src, *(itype*)&val, (itype*)dst, len);
}


template<typename T>
static inline IppStatus add(const T *src1, const T *src2, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::add(
            (const itype*)src1, (const itype*)src2, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus add_product(const T *src1, const T *src2, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::add_product(
            (const itype*)src1, (const itype*)src2, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus mul(const T *src1, const T *src2, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::mul(
            (const itype*)src1, (const itype*)src2, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus sub(const T *src1, const T *src2, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::sub(
            (const itype*)src1, (const itype*)src2, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus div(const T *src1, const T *src2, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::div(
            (const itype*)src1, (const itype*)src2, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus abs(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;
    return detail::abs(
            (const itype*)src, (itype*)dst, len);
}

template<typename T>
static inline IppStatus sqr(const T *src, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::sqr(
            (const itype*)src, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus sqrt(const T *src, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::sqrt(
            (const itype*)src, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus cubrt(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;
    return detail::cubrt(
            (const itype*)src, (itype*)dst, len);
}


template<typename T>
static inline IppStatus exp(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;
    return detail::exp(
            (const itype*)src, (itype*)dst, len);
}

template<typename T>
static inline IppStatus ln(const T *src, T *dst, int len, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::ln(
            (const itype*)src, (itype*)dst, len, scale);
}

template<typename T>
static inline IppStatus arctan(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;
    return detail::arctan(
            (const itype*)src, (itype*)dst, len);
}


template<typename T>
static inline IppStatus normalize(const T *src, T *dst, 
                                  int len, T sub, T div, int scale = 0)
{
    typedef get<T>::type itype;
    typedef get<value_type<T>::type>::type vtype;
    return detail::normalize(
            (const itype*)src, (itype*)dst, len, 
            *(itype*)&sub, *(vtype*)&div, scale);
}


/**@}*/



/**
 * @defgroup ConversionFunctions Conversion Functions
The functions described in this section perform the following conversion operations for vectors:
•Sorting all elements of a vector
•Data type conversion (including floating-point to integer and integer to floating-point)
•Joining several vectors
•Extracting components from a complex vector and constructing a complex vector
•Computing the complex conjugates of vectors
•Cartesian to polar and polar to Cartesian coordinate conversion.
 * Note: remove join*, split*,
 *
 * @ingroup EssentialFunctions
 * @{
 **/

template<typename T>
static inline IppStatus sort_ascend(T *buf, int len)
{
    typedef get<T>::type itype;
    return detail::sort_ascend((itype*)buf, len);
}

template<typename T>
static inline IppStatus sort_descend(T *buf, int len)
{
    typedef get<T>::type itype;
    return detail::sort_descend((itype*)buf, len);
}


template<typename T>
static inline IppStatus sort_index_ascend(T *buf, int *idxs, int len)
{
    typedef get<T>::type itype;
    return detail::sort_index_ascend((itype*)buf, idxs, len);
}


template<typename T>
static inline IppStatus sort_index_descend(T *buf, int *idxs, int len)
{
    typedef get<T>::type itype;
    return detail::sort_index_descend((itype*)buf, idxs, len);
}



template<typename T>
static inline IppStatus sort_radix_ascend(T *buf, T *tmp, int len)
{
    typedef get<T>::type itype;
    static_assert(std::is_same<get<int>::type, Ipp32s>::value,
            "type int is not same as Ipp32s");
    return detail::sort_radix_ascend(
            (itype*)buf, (itype*)tmp, (Ipp32s)len);
}


template<typename T>
static inline IppStatus sort_radix_index_ascend(const T* const src, 
                                                int stride,
                                                int *idxs,
                                                int *tmp_idxs,
                                                int len)
{
    typedef get<T>::type itype;
    static_assert(std::is_same<get<int>::type, Ipp32s>::value,
            "type int is not same as Ipp32s");
    return detail::sort_radix_index_ascend(
            (itype*)src, (Ipp32s)stride, (Ipp32s*)idxs,
            (Ipp32s*)tmp_idxs, (Ipp32s)len);
}

template<typename T>
static inline IppStatus sort_radix_index_descend(const T* const src, 
                                                int stride,
                                                int *idxs,
                                                int *tmp_idxs,
                                                int len)
{
    typedef get<T>::type itype;
    static_assert(std::is_same<get<int>::type, Ipp32s>::value,
            "type int is not same as Ipp32s");
    return detail::sort_radix_index_descend(
            (itype*)src, (Ipp32s)stride, (Ipp32s*)idxs,
            (Ipp32s*)tmp_idxs, (Ipp32s)len);
}


/* --------------------------------------------------------------------------*/
/**
 * @brief  Reverses the byte order of a vector.
 *  Note: extend to support signed integer
 * @tparam T
 * @param src
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus swap_bytes(const T *src, T *dst, int len)
{
    static_assert(is_integer<T>::value, "only support integer type");
    typedef get_int<sizeof(T), false>::type itype;
    return detail::swap_bytes(
            (const itype*)src, (itype*)dst, len);
}



/* --------------------------------------------------------------------------*/
/**
 * @brief Converts the data type of a vector and stores the results in a second vector.
 * Note: deprecate 24u, 24s, 16f related functions
 * @tparam T1
 * @tparam T2
 * @param src
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T1, typename T2>
static inline IppStatus convert(const T1 *src, T2 *dst, int len)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::convert(
            (const itype1*)src, (itype2*)dst, len);
}


/* --------------------------------------------------------------------------*/
/**
 * @brief Converts the data type of a vector and stores the results in a second vector.
 * Note: deprecate 24u, 24s, 16f related functions
 * @tparam T1
 * @tparam T2
 * @param src
 * @param dst
 * @param len
 * @param scale
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T1, typename T2>
static inline IppStatus convert(const T1 *src, T2 *dst, int len, int scale)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::convert_sfs(
            (const itype1*)src, (itype2*)dst, len, scale);
}

/* --------------------------------------------------------------------------*/
/**
 * @brief Converts the data type of a vector and stores the results in a second vector.
 * Note: deprecate 24u, 24s, 16f related functions
 * @tparam T1
 * @tparam T2
 * @param src
 * @param dst
 * @param len
 * @param rnd
 * @param scale
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T1, typename T2>
static inline IppStatus convert(const T1 *src, T2 *dst, int len, IppRoundMode rnd, int scale)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::convert_sfs(
            (const itype1*)src, (itype2*)dst, len, rnd, scale);
}



template<typename T>
static inline IppStatus conj(const T *src, T *dst, int len)
{
    static_assert(is_complex<T>::value, "need complex type");
    typedef get<T>::type itype;

    return detail::conj(
            (const itype*)src, (itype*)dst, len);
}


template<typename T>
static inline IppStatus magnitude(const T *re, const T*im, T*dst, int len, int scale = 0)
{
    typedef get<T>::type itype;

    return detail::magnitude(
            (const itype*)re, (const itype*)im, (itype*)dst, len, scale);
}

template<typename T1, typename T2>
static inline IppStatus magnitude(const T1 *re, const T1* im, T2* dst, int len, int scale = 0)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;

    return detail::magnitude(
            (const itype*)re, (const itype*)im, (vtype*)dst, len, scale);
}

/* --------------------------------------------------------------------------*/
/**
 * @brief 
 *
 * @tparam T1
 * @tparam T2
 * @param src
 * @param dst
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T1, typename T2>
static inline IppStatus magnitude(const T1 *src, T2 *dst, int len, int scale = 0)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;

    return detail::magnitude(
            (const itype*)src, (vtype*)dst, len, scale);
}




template<typename T1, typename T2>
static inline IppStatus phase(const T1 *src, T2 *dst, int len)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;

    return detail::phase(
            (const itype*)src, (vtype*)dst, len);

}

template<typename T1, typename T2>
static inline IppStatus phase(const T1 *re, const T1 *im, T2 *dst, int len)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;

    return detail::phase(
            (const itype*)re, (const itype*)im, (vtype*)dst, len);
}


template<typename T1, typename T2>
static inline IppStatus power_spectr(const T1 *src, T2 *dst, int len, int scale = 0)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;

    return detail::power_spectr(
            (const itype*)src, (vtype*)dst, len, scale);
}

template<typename T1, typename T2>
static inline IppStatus power_spectr(const T1 *re, const T1 *im, T2 *dst, int len, int scale = 0)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;

    return detail::power_spectr(
            (const itype*)re, (const itype*)im, (vtype*)dst, len, scale);
}


template<typename T1, typename T2>
static inline IppStatus real(const T1 *src, T2* re, int len)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;
    return detail::real(
            (const itype*)src, (vtype*)re, len);
}


template<typename T1, typename T2>
static inline IppStatus imag(const T1 *src, T2* im, int len)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;
    return detail::imag(
            (const itype*)src, (vtype*)im, len);
}


template<typename T1, typename T2>
static inline IppStatus cplx_to_real(const T1 *src, T2* re, T2 *im, int len)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;
    return detail::cplx_to_real(
            (const itype*)src, (vtype*)re, (vtype*)im, len);
}

template<typename T1, typename T2>
static inline IppStatus real_to_cplx(const T1 *re, const T1 *im, T2* dst, int len)
{
    typedef get<T1>::type itype;
    typedef get<T2>::type vtype;
    return detail::real_to_cplx(
            (const itype*)re, (const itype*)im, (vtype*)dst, len);
}


template<typename T1, typename T2>
static inline IppStatus threshold_lt(const T1 *src, T1 *dst, int len, T2 level)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::threshold_lt(
            (const itype1*)src, (itype1*)dst, len, (itype2)level);
    
}

template<typename T1, typename T2>
static inline IppStatus threshold_gt(const T1 *src, T1 *dst, int len, T2 level)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::threshold_gt(
            (const itype1*)src, (itype1*)dst, len, (itype2)level);
}

template<typename T1, typename T2>
static inline IppStatus threshold_lt_abs(const T1 *src, T1 *dst, int len, T2 level)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::threshold_lt_abs(
            (const itype1*)src, (itype1*)dst, len, (itype2)level);
}


template<typename T1, typename T2>
static inline IppStatus threshold_gt_abs(const T1 *src, T1 *dst, int len, T2 level)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::threshold_gt_abs(
            (const itype1*)src, (itype1*)dst, len, (itype2)level);
}

template<typename T1, typename T2>
static inline IppStatus threshold_lt_val(const T1 *src, T1 *dst, int len, T2 level, T1 value)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::threshold_lt_val(
            (const itype1*)src, (itype1*)dst, len, (itype2)level, *(itype1*)&value);
}


template<typename T1, typename T2>
static inline IppStatus threshold_gt_val(const T1 *src, T1 *dst, int len, T2 level, T1 value)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::threshold_gt_val(
            (const itype1*)src, (itype1*)dst, len, (itype2)level, *(itype1*)&value);
}

template<typename T1, typename T2>
static inline IppStatus threshold_lt_val_gt_val(const T1 *src, T1 *dst, int len,
        T2 lt_level, T1 lt_value, T2 gt_level, T1 gt_value)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::threshold_lt_val(
            (const itype1*)src, (itype1*)dst, len, 
            (itype2)lt_level, *(itype1*)&lt_value,
            (itype2)gt_level, *(itype1*)&gt_value);
}

///
template<typename T1, typename T2>
static inline IppStatus cart_to_polar(const T1 *src, T2 *magn, T2 *phase, int len)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::cart_to_polar(
            (const itype1*)src, (itype2*)magn, (itype2*)phase, len);
}

template<typename T1, typename T2>
static inline IppStatus cart_to_polar(
        const T1 *re, const T1 *im, T2 *magn, T2 *phase, int len)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::cart_to_polar(
            (const itype1*)re, (const itype1*)im,
            (itype2*)magn, (itype2*)phase, len);
}

template<typename T1, typename T2>
static inline IppStatus cart_to_polar(
        const T1 *re, const T1 *im, T2 *magn, T2 *phase,
        int len, int magn_scale, int phase_scale)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::cart_to_polar(
            (const itype1*)re, (const itype1*)im, (itype2*)magn,
            (itype2*)phase, len, magn_scale, phase_scale);
}

//
template<typename T1, typename T2>
static inline IppStatus polar_to_cart(
        const T1 *magn, const T1 *phase, T2 *dst, int len)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::cart_to_polar(
            (const itype1*)magn, (const itype1*)phase, (itype2*)dst, len);
}

template<typename T1, typename T2>
static inline IppStatus polar_to_cart(
        const T1 *magn, const T1 *phase, T2 *re, T2 *im, int len)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::cart_to_polar(
            (const itype1*)magn, (const itype1*)phase,
            (itype2*)re, (itype2*)im, len);
}


template<typename T1, typename T2>
static inline IppStatus polar_to_cart(
        const T1 *magn, const T1 *phase, T2 *re, T2 *im, int len,
        int magn_scale, int phase_scale)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;

    return detail::cart_to_polar(
            (const itype1*)magn, (const itype1*)phase,
            (itype2*)re, (itype2*)im, len, 
            magn_scale, phase_scale);
}


template<typename T>
static inline IppStatus max_order(const T *src, int len, int *order)
{
    typedef get<T>::type itype;
    return detail::max_order(
            (const itype*)src, len, order);
}


template<typename T>
static inline IppStatus flip(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;
    return detail::flip(
            (const itype*)src, dst, len);
}


template<typename T>
static inline IppStatus find_nearest_one(
        T in_val, T *out_val, int *out_idx, const T* src, int len)
{
    typedef get<T>::type itype;

    return detail::find_nearest_one(
            *(itype*)&in_val, (itype*)out_val, out_idx, (const itype*)src, len);
}

template<typename T>
static inline IppStatus find_nearest(
        const T *in_val, T *out_val, int *out_idx, int len, const T* src, int slen)
{
    typedef get<T>::type itype;

    return detail::find_nearest(
            (const itype*)in_val, (itype*)out_val, out_idx, 
            len, (const itype*)src, slen);
}

/**@}*/



/**
 * @defgroup WindowingFunction Windowing Functions
 * This chapter describes several of the windowing functions commonly used in signal processing. A window is a mathematical function by which a signal is multiplied to improve the characteristics of some subsequent analysis. Windows are commonly used in FFT-based spectral analysis. 
 * @ingroup EssentialFunctions
 * @{
 **/


template<typename T>
static inline IppStatus win_bartlett(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;

    return detail::win_bartlett(
            (const itype*)src, (itype*)dst, len);
}

template<typename T1, typename T2>
static inline IppStatus win_blackman(const T1 *src, T1 *dst, int len, T2 alpha)
{
    typedef get<T1>::type itype;

    return detail::win_blackman(
            (const itype*)src, (itype*)dst, len, alpha);
}


template<typename T>
static inline IppStatus win_blackman_std(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;

    return detail::win_blackman_std(
            (const itype*)src, (itype*)dst, len);
}


template<typename T>
static inline IppStatus win_blackman_opt(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;

    return detail::win_blackman_opt(
            (const itype*)src, (itype*)dst, len);
}

template<typename T>
static inline IppStatus win_hamming(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;

    return detail::win_hamming(
            (const itype*)src, (itype*)dst, len);
}

template<typename T>
static inline IppStatus win_hann(const T *src, T *dst, int len)
{
    typedef get<T>::type itype;

    return detail::win_hann(
            (const itype*)src, (itype*)dst, len);
}

template<typename T1, typename T2>
static inline IppStatus win_kaiser(const T1 *src, T1 *dst, int len, T2 alpha)
{
    typedef get<T1>::type itype;

    return detail::win_kaiser(
            (const itype*)src, (itype*)dst, len, alpha);
}


template<typename T>
class win
{
    win();
    win(const win &);

    int w_;
    int len_;
    T *wdata_;

    template<typename VT>
    struct get_alpha_type
    {
        typedef float type;
    };

    template<>
    struct get_alpha_type<double>
    {
        typedef double type;
    };
public:
    typedef enum{
        BARTLETT,
        BLACKMAN,
        BLACKMAN_STD,
        BLACKMAN_OPT,
        HAMMING,
        HANN,
        KAISER,

        //unused
        END_MAKRER,
    }win_type;

    typedef typename get_alpha_type<
        typename value_type<T>::type>::type alpha_type;


    win(win_type w, int len, alpha_type alpha = 0)
       : w_(w), len_(len)
    { 
        wdata_ = (T*)ipp::malloc<T>(len);
        if(!wdata_)
            return;

        set<T>(1, wdata_, len); 
        
        switch(w){
            case BARTLETT:
                win_bartlett(wdata_, wdata_, len);
                break;

            case BLACKMAN:
                win_blackman(wdata_, wdata_, len, alpha);
                break;

            case BLACKMAN_STD:
                win_blackman_std(wdata_, wdata_, len);
                break;

            case BLACKMAN_OPT:
                win_blackman_opt(wdata_, wdata_, len);
                break;

            case HAMMING:
                win_hamming(wdata_, wdata_, len);
                break;

            case HANN:
                win_hann(wdata_, wdata_, len);
                break;

            case KAISER:
                win_kaiser(wdata_, wdata_, len, alpha);
                break;

            default:
                //no window
                break;
        }
    }
    ~win()
    {
        if(wdata_) ipp::free(wdata_);
    }

    IppStatus mul(const T *src, T* dst, int len)
    {
        if(!wdata_)
            return ippStsMemAllocErr;
        else if(len > len_)
            return ippStsLengthErr;
        else
            return ipp::mul(src, wdata_, dst, len);
    }


};



/**@}*/

/**
 * @defgroup StatisticalFunction Statistical Functions
 * This section describes the Intel IPP functions that compute the vector measure values: maximum, minimum, mean, and standard deviation.
 *
 * Note: ZeroCrossing not implemented
 *
 * @ingroup EssentialFunctions
 * @{
 **/

template<typename T>
static inline IppStatus sum(const T *src, int len, T *sum_, IppHintAlgorithm hint =  ippAlgHintFast)
{
    typedef get<T>::type itype;
    return detail::sum<itype>(
            (const itype*)src, len, (itype*)sum_, hint);
}

template<typename T1, typename T2>
static inline IppStatus sum(const T1 *src, int len, T2 *sum_, int scale = 0)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::sum<itype1, itype2>(
            (const itype1*)src, len, (itype2*)sum_, scale);
}



template<typename T>
static inline IppStatus max(const T *src, int len, T *max_)
{
    typedef get<T>::type itype;
    return detail::max(
            (const itype*)src, len, (itype*)max_);
}


template<typename T>
static inline IppStatus max_indx(const T *src, int len, T *max_, int *indx)
{
    typedef get<T>::type itype;
    return detail::max_indx(
            (const itype*)src, len, (itype*)max_, indx);
}

template<typename T>
static inline IppStatus max_abs(const T *src, int len, T *max_)
{
    typedef get<T>::type itype;
    return detail::max_abs(
            (const itype*)src, len, (itype*)max_);
}

template<typename T>
static inline IppStatus max_abs_indx(const T *src, int len, T *max_, int *indx)
{
    typedef get<T>::type itype;
    return detail::max_abs_indx(
            (const itype*)src, len, (itype*)max_, indx);
}

template<typename T>
static inline IppStatus min(const T *src, int len, T *min_)
{
    typedef get<T>::type itype;
    return detail::min(
            (const itype*)src, len, (itype*)min_);
}


template<typename T>
static inline IppStatus min_indx(const T *src, int len, T *min_, int *indx)
{
    typedef get<T>::type itype;
    return detail::min_indx(
            (const itype*)src, len, (itype*)min_, indx);
}

template<typename T>
static inline IppStatus min_abs(const T *src, int len, T *min_)
{
    typedef get<T>::type itype;
    return detail::min_abs(
            (const itype*)src, len, (itype*)min_);
}

template<typename T>
static inline IppStatus min_abs_indx(const T *src, int len, T *min_, int *indx)
{
    typedef get<T>::type itype;
    return detail::min_abs_indx(
            (const itype*)src, len, (itype*)min_, indx);
}


template<typename T>
static inline IppStatus min_max(const T* src, int len, T *min_, T *max_)
{
    typedef get<T>::type itype;
    return detail::min_max(
            (const itype*)src, len, (itype*)min_, (itype*)max_);
}


template<typename T>
static inline IppStatus min_max_indx(
        const T* src, int len, T *min_, int *min_indx,  T *max_, int *max_indx)
{
    typedef get<T>::type itype;
    return detail::min_max(
            (const itype*)src, len, (itype*)min_, min_indx, (itype*)max_, max_indx);
}


template<typename T>
static inline IppStatus mean(const T *src, int len, T *mean_, IppHintAlgorithm hint)
{
    typedef get<T>::type itype;
    return detail::mean(
            (const itype*)src, len, (itype*)mean_, hint);
}

template<typename T>
static inline IppStatus mean(const T *src, int len, T *mean_, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::mean(
            (const itype*)src, len, (itype*)mean_, scale);
}


template<typename T>
static inline IppStatus std_dev(const T *src, int len, T *std_dev_, IppHintAlgorithm hint)
{
    typedef get<T>::type itype;
    return detail::std_dev(
            (const itype*)src, len, (itype*)std_dev_, hint);
}

template<typename T>
static inline IppStatus std_dev(const T *src, int len, T *std_dev_, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::std_dev(
            (const itype*)src, len, (itype*)std_dev_, scale);
}


template<typename T>
static inline IppStatus mean_std_dev(
        const T *src, int len, T* mean_, T *std_dev_, IppHintAlgorithm hint)
{
    typedef get<T>::type itype;
    return detail::mean_std_dev(
            (const itype*)src, len, (itype*)mean_, (itype*)std_dev_, hint);
}

template<typename T>
static inline IppStatus mean_std_dev(
        const T *src, int len, T* mean_, T *std_dev_, int scale = 0)
{
    typedef get<T>::type itype;
    return detail::mean_std_dev(
            (const itype*)src, len, (itype*)mean_, (itype*)std_dev_, scale);
}


template<typename T1, typename T2>
static inline IppStatus norm_inf(
        const T1* src, int len, T2 *norm_)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::norm_inf(
            (const itype1*)src, len, (itype2*)norm_);
}

template<typename T1, typename T2>
static inline IppStatus norm_l1(
        const T1* src, int len, T2 *norm_)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::norm_l1(
            (const itype1*)src, len, (itype2*)norm_);
}

template<typename T1, typename T2>
static inline IppStatus norm_l2(
        const T1* src, int len, T2 *norm_)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::norm_l2(
            (const itype1*)src, len, (itype2*)norm_);
}

template<typename T1, typename T2>
static inline IppStatus norm_l2_sqr(
        const T1* src, int len, T2 *norm_, int scale)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::norm_l2_sqr(
            (const itype1*)src, len, (itype2*)norm_, scale);
}


template<typename T1, typename T2>
static inline IppStatus norm_diff_inf(
        const T1* src1, const T1* src2, int len, T2 *norm_)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::norm_diff_inf(
            (const itype1*)src1, (const itype1*)src2, len, (itype2*)norm_);
}

template<typename T1, typename T2>
static inline IppStatus norm_diff_l1(
        const T1* src1, const T1* src2, int len, T2 *norm_)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::norm_diff_l1(
            (const itype1*)src1, (const itype1*)src2, len, (itype2*)norm_);
}

template<typename T1, typename T2>
static inline IppStatus norm_diff_l2(
        const T1* src1, const T1* src2, int len, T2 *norm_)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::norm_diff_l2(
            (const itype1*)src1, (const itype1*)src2, len, (itype2*)norm_);
}

template<typename T1, typename T2>
static inline IppStatus norm_diff_l2_sqr(
        const T1* src1, const T1 *src2, int len, T2 *norm_, int scale)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::norm_diff_l2_sqr(
            (const itype1*)src1, (const itype1*)src2, len, (itype2*)norm_);
}


template<typename T1, typename T2, typename T3>
static inline IppStatus dot_prod(
        const T1* src1, const T2* src2, int len, T3 *dp)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    typedef get<T3>::type itype3;

    return detail::dot_prod(
            (const itype1*)src1, (const itype2*)src2,
            len, (itype3*)dp);
}



/* --------------------------------------------------------------------------*/
/**
 * @brief in-place and out-place operation 
 *
 * @tparam T
 * @Param src
 * @Param dst
 * @Param len
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus max_every(const T* src1, const T* src2, T *dst, int len)
{
    typedef get<T>::type itype;

    return detail::max_every(
            (const itype*)src1, (const itype*)src2, (itype*)dst, len);
}

/* --------------------------------------------------------------------------*/
/**
 * @brief in-place operation 
 *
 * @tparam T
 * @Param src
 * @Param dst
 * @Param len
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus max_every(const T* src, T *srcdst, int len)
{
    typedef get<T>::type itype;

    return detail::max_every(
            (const itype*)src, (const itype*)srcdst, (itype*)srcdst, len);
}


/* --------------------------------------------------------------------------*/
/**
 * @brief in-place and out-place operation 
 *
 * @tparam T
 * @Param src
 * @Param dst
 * @Param len
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus min_every(const T* src1, const T* src2, T *dst, int len)
{
    typedef get<T>::type itype;

    return detail::min_every(
            (const itype*)src1, (const itype*)src2, (itype*)dst, len);
}

/* --------------------------------------------------------------------------*/
/**
 * @brief in-place operation 
 *
 * @tparam T
 * @Param src
 * @Param dst
 * @Param len
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline IppStatus min_every(const T* src, T *srcdst, int len)
{
    typedef get<T>::type itype;

    return detail::min_every(
            (const itype*)src, (const itype*)srcdst, (itype*)srcdst, len);
}



template<typename T>
static inline IppStatus count_in_range(const T* src, int len, int *count, T lower, T upper)
{
    typedef get<T>::type itype;
    return detail::count_in_range(
            (const itype*)src, len, count, (itype)lower, (itype)upper);
}

/**@}*/


/**
 * @defgroup SamplingFunctions Sampling Functions
 * The functions described in this section manipulate signal samples. Sampling functions are used to change the sampling rate of the input signal and thus to obtain the signal vector of a required length. The functions perform the following operations:
Insert zero-valued samples between neighboring samples of a signal (up-sample).
Remove samples from between neighboring samples of a signal (down-sample).
 *
 * @ingroup EssentialFunctions
 * @{
 **/

template<typename T>
static inline IppStatus sample_up(
        const T* src, int src_len, T *dst, int *dst_len, int factor, int *phase)
{
    typedef get<T>::type itype;

    return detail::sample_up(
            (const itype*)src, src_len, (itype*)dst, dst_len, factor, phase);
}


template<typename T>
static inline IppStatus sample_down(
        const T* src, int src_len, T *dst, int *dst_len, int factor, int *phase)
{
    typedef get<T>::type itype;

    return detail::sample_down(
            (const itype*)src, src_len, (itype*)dst, dst_len, factor, phase);
}



/**@}*/


/**
 * @defgroup FilteringFunctions This chapter describes the Intel® IPP functions that perform convolution and correlation operations, as well as linear and non-linear filtering. 
 * */



/**
 * @defgroup ConvolutionAndCorrelationFunctions Convolution and Correlation Functions
 * Note: CrossCorr is not implemented
 * @ingroup FilteringFunctions Convolution is an operation used to define an output signal from any linear time-invariant (LTI) processor in response to any input signal. 
 * @{
 **/

template<typename T>
class auto_corr_norm
{
    uint8_t *buffer_;
    int slen_, dlen_;
    IppEnum alg_;

    auto_corr_norm();
    auto_corr_norm(const auto_corr_norm&);
public:
    typedef typename get<T>::type itype;

    auto_corr_norm(int slen, int dlen, IppEnum alg)
    {
        int bsize = 0;
        buffer_ = 0;
        slen_ = slen; dlen_ = dlen;
        alg_ = alg;

        IppStatus status = detail::auto_corr_norm_get_buffer_size(
                slen, dlen, type_value<T>::value, alg, &bsize);
        if(status != ippStsNoErr)
            return;
        
        buffer_ = ipp::malloc<uint8_t>(bsize);
    }

    ~auto_corr_norm()
    {
        if(buffer_) ipp::free(buffer_);
    }

    IppStatus do_corr(const T* src, int slen, T *dst, int dlen)
    {
        if(slen != slen_ || dlen != dlen_)
            return ippStsSizeErr;
        else if(!buffer_)
            return ippStsMemAllocErr;
        else
            return detail::do_auto_corr_norm(
                    (const itype*)src, slen, (itype*)dst, dlen, alg_, (Ipp8u*)buffer_);
    }
};


template<typename T>
class cross_corr_norm
{
    uint8_t *buffer_;
    int s1len_, s2len_, dlen_;
    IppEnum alg_;
    int low_lag_;

    cross_corr_norm();
    cross_corr_norm(const cross_corr_norm&);
public:
    typedef typename get<T>::type itype;

    cross_corr_norm(int s1len, int s2len, int dlen, int low_lag, IppEnum alg)
    {
        int bsize = 0;
        buffer_ = 0;
        s1len_ = s1len; s2len_ = s2len;
        dlen_ = dlen; alg_ = alg;
        low_lag_ = low_lag;

        IppStatus status = detail::cross_corr_norm_get_buffer_size(
                s1len, s2len, dlen, low_lag, type_value<T>::value, alg, &bsize);
        if(status != ippStsNoErr)
            return;
        
        buffer_ = ipp::malloc<uint8_t>(bsize);
    }

    ~cross_corr_norm()
    {
        if(buffer_) ipp::free(buffer_);
    }

    IppStatus do_corr(
            const T* src1, int s1len, const T* src2, int s2len, T *dst, int dlen)
    {
        if(s1len != s1len_ || s2len != s2len_ || dlen != dlen_)
            return ippStsSizeErr;
        else if(!buffer_)
            return ippStsMemAllocErr;
        else
            return detail::do_cross_corr_norm(
                    (const itype*)src1, s1len, (const itype*)src2, s2len,
                    (itype*)dst, dlen, low_lag_, alg_, (Ipp8u*)buffer_);
    }
};


template<typename T>
class convolve
{
    uint8_t *buffer_;
    int s1len_, s2len_;
    IppEnum alg_;

    convolve();
    convolve(const convolve&);
public:
    typedef typename get<T>::type itype;

    convolve(int s1len, int s2len, IppEnum alg)
    {
        int bsize = 0;
        buffer_ = 0;
        s1len_ = s1len; s2len_ = s2len;
        alg_ = alg;

        IppStatus status = detail::convolve_get_buffer_size(
                s1len, s2len, type_value<T>::value, alg, &bsize);
        if(status != ippStsNoErr)
            return;
        
        buffer_ = ipp::malloc<uint8_t>(bsize);
    }

    ~convolve()
    {
        if(buffer_) ipp::free(buffer_);
    }

    IppStatus do_convolve(
            const T* src1, int s1len, const T* src2, int s2len, T *dst)
    {
        if(s1len != s1len_ || s2len != s2len_)
            return ippStsSizeErr;
        else if(!buffer_)
            return ippStsMemAllocErr;
        else
            return detail::do_convolve(
                    (const itype*)src1, s1len, (const itype*)src2, s2len,
                    (itype*)dst, alg_, (Ipp8u*)buffer_);
    }
};



template<typename T>
static inline IppStatus conv_biased(
        const T* src1, int s1len, const T* src2, int s2len, T* dst, int dlen, int bias)
{
    typedef get<T>::type itype;

    return detail::conv_biased(
            (const itype*)src1, s1len, (const itype*)src2, s2len, (itype*)dst, dlen, bias);
}

/**@}*/


/**
 * @defgroup TransformFunctions This chapter describes the Intel® IPP functions that perform Fourier and discrete cosine transforms (DCT), as well as Hartley, Hilbert, Walsh-Hadamard and wavelet transforms of signals. 
 **/


/**
 * @defgroup FourierTransformFunctions  The functions described in this section perform the fast Fourier transform (FFT), the discrete Fourier transform (DFT) of signal samples. It also includes variations of the basic functions to support different application requirements.
 * @ingroup TransformFunctions 
 * @{
 **/


template<typename T, bool IsCplx>
struct fft_sepc
{
    typedef typename get<T>::type itype;
    typedef typename detail::fft_spec<itype, IsCplx>::type type;
};


template<typename T, bool IsCplx>
static inline IppStatus fft_get_size(
        int order, int flag, IppHintAlgorithm hint, 
        int *spec_size, int *spec_buf_size, int *buf_size)
{
    typedef get<T>::type itype;
    return detail::fft_get_size<itype, IsCplx>(
            order, flag, hint, spec_size, spec_buf_size, buf_size);
}


template<typename T, bool IsCplx>
static inline IppStatus fft_init(
        void **spec, int order, int flag,
        IppHintAlgorithm hint, uint8_t *p_spec, uint8_t *spec_buf)
{
    typedef get<T>::type itype;
    typedef detail::fft_spec<itype, IsCplx>::type spec_type;
    return detail::fft_init<itype, spec_type>(
            (spec_type**)spec, order, flag, hint, (Ipp8u*)p_spec, (Ipp8u*)spec_buf);
}


template<typename T, bool IsCplx>
static inline IppStatus fft_forward(
        const T *sre, const T* sim, T *dre, T* dim, void *spec, uint8_t *buf)
{
    static_assert(IsCplx, "Only support complex type config");
    typedef get<T>::type itype;
    typedef detail::fft_spec<itype, IsCplx>::type spec_type;
    return detail::fft_forward<itype, spec_type, IsCplx>(
            (const itype*)sre, (const itype*)sim, (itype*)dre, (itype*)dim, 
            (spec_type*)spec, (Ipp8u*)buf);
}


/* --------------------------------------------------------------------------*/
/**
 * @brief only support perm format for real type
 *
 * @tparam T
 * @tparam IsCplx
 * @Param src
 * @Param dst
 * @Param spec
 * @Param buf
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T, bool IsCplx>
static inline IppStatus fft_forward(
        const T *src, T* dst, void *spec, uint8_t *buf)
{
    typedef get<T>::type itype;
    typedef detail::fft_spec<itype, IsCplx>::type spec_type;
    return detail::fft_forward<itype, spec_type, IsCplx>(
            (const itype*)src, (itype*)dst, 
            (spec_type*)spec, (Ipp8u*)buf);
}


template<typename T, bool IsCplx>
static inline IppStatus fft_inverse(
        const T *sre, const T* sim, T *dre, T* dim, void *spec, uint8_t *buf)
{
    static_assert(IsCplx, "Only support complex type config");
    typedef get<T>::type itype;
    typedef detail::fft_spec<itype, IsCplx>::type spec_type;
    return detail::fft_inverse<itype, spec_type, IsCplx>(
            (const itype*)sre, (const itype*)sim, (itype*)dre, (itype*)dim, 
            (spec_type*)spec, (Ipp8u*)buf);
}


/* --------------------------------------------------------------------------*/
/**
 * @brief only support perm format for real type
 *
 * @tparam T
 * @tparam IsCplx
 * @param src
 * @param dst
 * @param spec
 * @param buf
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T, bool IsCplx>
static inline IppStatus fft_inverse(
        const T *src, T* dst, void *spec, uint8_t *buf)
{
    typedef get<T>::type itype;
    typedef detail::fft_spec<itype, IsCplx>::type spec_type;
    return detail::fft_inverse<itype, spec_type, IsCplx>(
            (const itype*)src, (itype*)dst, 
            (spec_type*)spec, (Ipp8u*)buf);
}



/* --------------------------------------------------------------------------*/
/**
 * @brief only support perm format for real type
 *
 * @tparam T
 * @tparam IsCplx
 */
/* ----------------------------------------------------------------------------*/
template<typename T, bool IsCplx>
class fft
{
    void *spec_;
    uint8_t *spec_buf_,
            *work_buf_;

    int flag_, order_;
    IppHintAlgorithm hint_;

    fft();
    fft(const fft&);
public:
    typedef T value_type;
    //ipp types
    typedef typename get<T>::type itype;

    fft(int order, 
        int flag = IPP_FFT_NODIV_BY_ANY,
        IppHintAlgorithm hint = ippAlgHintFast)
        : spec_(0), spec_buf_(0), work_buf_(0),
          flag_(flag), hint_(hint), order_(order)
    {
        void *spec = 0;
        uint8_t *spec_buf, 
                *init_buf,
                *work_buf;
        int spec_size, init_size, work_size;
        if(fft_get_size<T, IsCplx>(order, flag, hint,
                    &spec_size, &init_size, &work_size) != ippStsNoErr)
            return;
        
        spec_buf = ipp::malloc<uint8_t>(spec_size);
        init_buf = ipp::malloc<uint8_t>(init_size);
        work_buf = ipp::malloc<uint8_t>(work_size);

        if(!spec_buf || (init_size && !init_buf) || (work_size && !work_buf))
            goto FAILED;

        if(fft_init<T, IsCplx>(
                    &spec, order, flag, hint, spec_buf, init_buf) != ippStsNoErr)
            goto FAILED;
        
        ipp::free(init_buf);

        spec_buf_ = spec_buf;
        work_buf_ = work_buf;
        spec_ = spec;

        return;

    FAILED:
        if(spec_buf)
            ipp::free(spec_buf);
        if(init_buf)
            ipp::free(init_buf);
        if(work_buf)
            ipp::free(work_buf);
    }

    ~fft()
    {
        if(spec_buf_)
            ipp::free(spec_buf_);
        if(work_buf_)
            ipp::free(work_buf_);
    }

    int order() const { return order_; }
    int flag() const  { return flag_; }
    IppHintAlgorithm hint() const { return hint_; }


    IppStatus forward(const T *sre, const T *sim, T *dre, T *dim)
    {
        static_assert(!is_complex<T>::value && IsCplx,
                "only support complex config and real value");

        if(spec_)
            return fft_forward<T, IsCplx>(
                    sre, sim, dre, dim, spec_, work_buf_);
        else
            return ippStsMemAllocErr;
    }

    IppStatus forward(const T *src, T *dst)
    {
        static_assert(is_complex<T>::value || !IsCplx,
                "only support complex type or real type");

        if(spec_)
            return fft_forward<T, IsCplx>(
                    src, dst, spec_, work_buf_);
        else
            return ippStsMemAllocErr;
    }

    IppStatus inverse(const T *sre, const T *sim, T *dre, T *dim)
    {
        static_assert(!is_complex<T>::value && IsCplx,
                "only support complex config and real value");

        if(spec_)
            return fft_inverse<T, IsCplx>(
                    sre, sim, dre, dim, spec_, work_buf_);
        else
            return ippStsMemAllocErr;
    }

    IppStatus inverse(const T *src, T *dst)
    {
        static_assert(is_complex<T>::value || !IsCplx,
                "only support complex type or real type");

        if(spec_)
            return fft_inverse<T, IsCplx>(
                    src, dst, spec_, work_buf_);
        else
            return ippStsMemAllocErr;
    }

    operator bool() const
    {
        return spec_ != 0;
    }

};


enum{
    FIR_HERMANN,
    FIR_BELLANGER,
    FIR_KAISER
};


static int fir_tap_estimate(
        double wp, double ws, double Ap, double As, int model = FIR_BELLANGER)
{
    //
    double dp = 1 - pow(10., - Ap / 20.);
    double ds = pow(10., -As / 20.);

    double N = 0;
    if(model == FIR_KAISER){
		N = (-20 * std::log10(pow(dp * ds, 0.5)) - 13) / ((ws - wp) * 14.6 / M_PI_2);
    }
    else if(model == FIR_BELLANGER){
		N = -(2 * std::log10(10 * dp * ds) / (3. * (ws - wp) / M_PI_2)) - 1;
    }
    else{ //FIR_BELLANGER
        double a[] = {0.005309, 0.07114, -0.4761, 0.00266, 0.5941, 0.4278};
        double b[] = {11.01217, 0.51244};

#define D(dp, ds) ((a[0] * pow(std::log10(dp), 2.) + a[1] * std::log10(dp) + a[2]) * std::log10(ds)\
        - (a[3] * pow(std::log10(dp), 2.) + a[4] * std::log10(dp) + a[5]))

#define F(dp, ds) (b[0] + b[1] * (std::log10(dp) - std::log10(ds)))

        N = (D(dp, ds) - F(dp, ds) * pow((ws - wp) / M_PI_2, 2.)) / ((ws - wp) / M_PI_2);
    }

    return int(ceil(fabs(N)));
}


#if 0
template<typename T>
class fir_lp
{
public:
    fir_lp

};
#endif




template<typename T>
class fir_sr
{
public:
    typedef typename get<T>::type itype;

private:
    void *spec_;
    itype *dly_[2]; //
    int sdly_idx_;
    uint8_t *work_buf_;

    fir_sr();
    fir_sr(const fir_sr&);
public:
    fir_sr(const itype *taps, int tap_len, IppAlgType alg = ippAlgAuto)
    {
        spec_ = 0;
        work_buf_ = 0;
        dly_[0] = dly_[1] = 0;
        sdly_idx_ = 0;

        int spec_size = 0, buf_size = 0;
        detail::fir_sr_get_size<itype>(tap_len, &spec_size, &buf_size);

        dly_[0] = ipp::malloc<T>(tap_len - 1);
        dly_[1] = ipp::malloc<T>(tap_len - 1);
        
        if(dly_[0])
            memset(dly_[0], 0, sizeof(T) * (tap_len - 1));

        
        spec_ = ipp::malloc<uint8_t>(spec_size);
        work_buf_ = ipp::malloc<uint8_t>(buf_size);
        
        if(!spec_ || !work_buf_ || !dly_[0] || !dly_[1])
            goto FAILED;


        int ret = detail::fir_sr_init<T>(taps, tap_len, alg, spec_);
        if(ret == ippStsNoErr)
            return;

FAILED:
        if(spec_){
            ipp::free(spec_);
            spec_ = 0;
        }
        //other buf will free alter
    }
    ~fir_sr()
    {
        if(spec_)
            ipp::free(spec_);
        if(work_buf_)
            ipp::free(work_buf_);
        if(dly_[0])
            ipp::free(dly_[0]);
        if(dly_[1])
            ipp::free(dly_[1]);
    }

    IppStatus filter(const T *src, T *dst, int ni, bool use_dly = true)
    {
        if(spec_ && use_dly){
            itype *sdly = dly_[sdly_idx_++],
                  *ddly = dly_[sdly_idx_ % 2];
            sdly_idx_ %= 2;

            return detail::fir_sr_filter<itype>(
                    (const itype*)src, (itype*)dst, ni, spec_, sdly, ddly, work_buf_);
        }
        else if(spec_){
            return detail::fir_sr_filter<itype>(
                    (const itype*)src, (itype*)dst, ni, spec_, 0, 0, work_buf_);
        }
        else{
            return ippStsMemAllocErr;
        }
    }
};

//only support float
template<typename T>
class fir
{
public:
    typedef typename get<T>::type itype;
private:
    void *state_;
    uint8_t *work_buf_;

public:
    fir(const itype *taps, int tap_len,
        const itype *dly = 0)
    {
        state_ = 0; 
        work_buf_ = 0;
        
        int buf_size = 0;
        detail::fir_get_state_size<itype>(tap_len, &buf_size); 
        
        work_buf_ = ipp::malloc<uint8_t>(buf_size);
        
        if(!work_buf_)
            return;
        
        IppStatus r = detail::fir_init<itype>(
                &state_, taps, tap_len, dly, work_buf_);
        if(r != ippStsNoErr){
            ipp::free(work_buf_);
            work_buf_ = 0;
            state_ = 0;
        }
    }

    ~fir()
    {
        if(work_buf_)
            ipp::free(work_buf_);
    }

    IppStatus filter(const T *src, T *dst, int ni)
    {
        if(state_){
            return detail::fir_filter(
                    (const itype*)src, (itype*)dst, ni, state_);
        }
        else{
            return ippStsMemAllocErr;
        }
    }
};

//only support float
template<typename T>
class fir_mr
{
public:
    typedef typename get<T>::type itype;
private:
    void *state_;
    uint8_t *work_buf_;

public:
    fir_mr(const itype *taps, int tap_len,
        int up_factor, int up_phase, int down_factor, int down_phase,
        const itype *dly = 0)
    {
        state_ = 0; 
        work_buf_ = 0;
        
        int buf_size = 0;
        detail::fir_mr_get_state_size<itype>(
                tap_len, up_factor, down_factor, &buf_size); 
        
        work_buf_ = ipp::malloc<uint8_t>(buf_size);
        
        if(!work_buf_)
            return;
        
        IppStatus r = detail::fir_mr_init<itype>(
                &state_, taps, tap_len, 
                up_factor, up_phase, down_factor, down_phase,
                dly, work_buf_);
        if(r != ippStsNoErr){
            ipp::free(work_buf_);
            work_buf_ = 0;
            state_ = 0;
        }
    }

    ~fir_mr()
    {
        if(work_buf_)
            ipp::free(work_buf_);
    }

    IppStatus filter(const T *src, T *dst, int ni)
    {
        if(state_){
            return detail::fir_filter(
                    (const itype*)src, (itype*)dst, ni, state_);
        }
        else{
            return ippStsMemAllocErr;
        }
    }
};




/* --------------------------------------------------------------------------*/
/**
 * @brief 
 *  x[n]---> up-L ---> H ---> down-M --- y[m]
 *  fi  -  freq in
 *  fo  -  freq out
 *  H   - low pass filter, length is N, and stop freq is wc
 *
 *
 *  fi / fo = L / M = a
 *  rollf               -- all pass filter stop freq, ie. 0.95
 *  wc = rollf / a      -- idear H low pass stop freq 
 *  win = N / nstep
 *  nstep = int(max(1 / a, a))   
 *  alpha -- Kaiser window parameter 
 *
 * @tparam T
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
class polyphase_resampling
{
    void *spec_;

public:
    typedef typename get<T>::type itype;

    polyphase_resampling(
            float win, int nstep, float rollf, float alpha,
            IppHintAlgorithm hint = ippAlgHintFast)
    {
        spec_ = 0;

        int psize = 0;
        detail::resample_polyphase_get_size<itype>(
                (Ipp32f)win, nstep, &psize, hint); 
        
        spec_ = ipp::malloc<uint8_t>(psize);

        if(!spec_)
            return;
        
        IppStatus r = detail::resample_polyphase_init<itype>(
                (Ipp32f)win, nstep, (Ipp32f)rollf, (Ipp32f)alpha, spec_,  hint);
        if(r != ippStsNoErr){
            ipp::free(spec_);
            spec_ = 0;
        }
    }

    ~polyphase_resampling()
    {
        if(spec_)
            ipp::free(spec_);
    }

    IppStatus resample(
            const T *src, int ilen, T *dst, int *olen, double *time,
            double factor, float norm)
    {
        if(spec_){
            return detail::resample_polyphase(
                    (const itype*)src, ilen, (itype*)dst, (Ipp64f)factor, 
                    (Ipp32f)norm, (Ipp64f*)time, olen, spec_); 
        }
        else{
            return ippStsMemAllocErr;
        }
    }
};

template<typename T>
class polyphase_resampling_fixed
{
    void *spec_;
    int flen_, fheight_;

public:
    typedef typename get<T>::type itype;

    polyphase_resampling_fixed(
            int in_rate, int out_rate, int len, 
            float rollf, float alpha,
            IppHintAlgorithm hint = ippAlgHintFast)
    {
        spec_ = 0;

        int psize = 0;
        detail::resample_polyphase_fixed_get_size<itype>(
                in_rate, out_rate, len,
                &psize, &flen_, &fheight_, hint);
        
        spec_ = ipp::malloc<uint8_t>(2*psize); //[FIXME] workaround to remove heap corrupt issue

        if(!spec_)
            return;

		zero((uint8_t*)spec_, psize);
        
        IppStatus r = detail::resample_polyphase_fixed_init<itype>(
                in_rate, out_rate, flen_, (Ipp32f)rollf, (Ipp32f)alpha, spec_, hint); 
        if(r != ippStsNoErr){
            ipp::free(spec_);
            spec_ = 0;
        }
    }

    ~polyphase_resampling_fixed()
    {
        if(spec_)
            ipp::free(spec_);
    }

    IppStatus resample(
            const T *src, int ilen, T *dst, int *olen, double *time,
            float norm)
    {
        if(spec_){
            return detail::resample_polyphase_fixed(
                    (const itype*)src, ilen, (itype*)dst,
                    (Ipp32f)norm, (Ipp64f*)time, olen, spec_); 
        }
        else{
            return ippStsMemAllocErr;
        }
    }


    /* --------------------------------------------------------------------------*/
    /**
     * @brief the output filter is in inverse order, 
     * ie. in_rate / out_rate = 1 / 5, and polyphase filter is Q0, Q1, Q2, Q3, Q4
     * The output should be : Q0, Q4, Q3, Q2, Q1
     *
     * @param buf
     *
     * @returns   
     */
    /* ----------------------------------------------------------------------------*/
    int get_filter(T *buf)
    {
        if(spec_){
            detail::resample_polyphase_fixed_filter<itype>(
                    buf, flen_, fheight_, spec_);
            return flen_ * fheight_;
        }
        else{
            return 0;
        }
    }

    int filter_length() const { return flen_; }
    int filter_height() const { return fheight_; }

    operator bool() const
    {
        return spec_ != 0;
    }

};




/**@}*/


}

#endif
