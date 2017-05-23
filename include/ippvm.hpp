/** 
 * @file ippvm.hpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2016-03-09
 */


#ifndef IPPPLUS_IPPVM_HPP
#define IPPPLUS_IPPVM_HPP

#include "detail/ippvm.hpp"

namespace ipp{

template<typename T, PerciseType P>
static inline IppStatus sincos(const T* src, T* sin, T *cos, int len)
{
    typedef get<T>::type itype;
    return detail::sincos<itype, P>(src, sin, cos, len);
}

template<typename T, PerciseType P>
static inline IppStatus sin(const T* src, T* dst, int len)
{
    typedef get<T>::type itype;
    return detail::sin<itype, P>(src, dst, len);
}

template<typename T, PerciseType P>
static inline IppStatus cos(const T* src, T* dst, int len)
{
    typedef get<T>::type itype;
    return detail::cos<itype, P>(src, dst, len);
}


template<typename T, PerciseType P>
static inline IppStatus log10(const T* src, T* dst, int len)
{
    typedef get<T>::type itype;
    return detail::log10<itype, P>(src, dst, len);
}




}
#endif
