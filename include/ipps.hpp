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


}

#endif
