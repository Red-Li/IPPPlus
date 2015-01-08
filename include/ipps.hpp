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

#include "ippcore.h"
#include "ipptype.hpp"
#include "ippcore.hpp"
#include "detail/ipps.hpp"

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
static inline IppStatus sum(const T *src, int len, T *sum_, IppHintAlgorithm hint)
{
    typedef get<T>::type itype;
    return detail::sum(
            (const itype*)src, len, (itype*)sum_, hint);
}

template<typename T1, typename T2>
static inline IppStatus sum(const T1 *src, int len, T2 *sum_, int scale = 0)
{
    typedef get<T1>::type itype1;
    typedef get<T2>::type itype2;
    return detail::sum(
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
            (const itype*)src, (itype*)srcdst, len);
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
            (const itype*)src, (itype*)srcdst, len);
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

}

#endif
