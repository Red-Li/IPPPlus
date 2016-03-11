/**
 * @file ipptype.hpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2014-12-26
 */

#ifndef IPPPLUS_IPPTYPE_HPP
#define IPPPLUS_IPPTYPE_HPP

#include <stdint.h>
#include <complex>

#include <ippcore.h>

/**
 * @defgroup Types
 * @{
*/
namespace ipp{

template<typename T>
struct is_complex
{
    static const bool value = false;
};

template<>
struct is_complex<Ipp32fc>
{
    static const bool value = true;
};

template<>
struct is_complex<Ipp64fc>
{
    static const bool value = true;
};

template<>
struct is_complex<Ipp32fc&>
{
    static const bool value = true;
};

template<>
struct is_complex<Ipp64fc&>
{
    static const bool value = true;
};



template<>
struct is_complex<const Ipp32fc>
{
    static const bool value = true;
};

template<>
struct is_complex<const Ipp64fc>
{
    static const bool value = true;
};

template<>
struct is_complex<const Ipp32fc&>
{
    static const bool value = true;
};

template<>
struct is_complex<const Ipp64fc&>
{
    static const bool value = true;
};

template<typename T>
struct is_complex<std::complex<T> >
{
    static const bool value = true;
};
template<typename T>
struct is_complex<std::complex<T>& >
{
    static const bool value = true;
};
template<typename T>
struct is_complex<const std::complex<T> >
{
    static const bool value = true;
};
template<typename T>
struct is_complex<const std::complex<T>& >
{
    static const bool value = true;
};


template<typename T, bool FloatSelected, bool Cplx>
struct _test_equal
{
    static const bool value = false;
};
template<typename T>
struct _test_equal<T, true, false>
{
    static const bool value = (T(0.5) == 0.5);
};
template<typename T>
struct _test_equal<T, false, false>
{
    static const bool value = (T(0.5) == 0);
};


template<typename T>
struct is_integer
{
    static const bool value = 
        _test_equal<T, false, is_complex<T>::value>::value;
};

template<typename T>
struct is_signed_integer
{
    static_assert(is_integer<T>::value, "need integer type");
    static const bool value = (T(-1) < 0);
};

template<typename T>
struct is_float
{
    static const bool value = 
        _test_equal<T, true, is_complex<T>::value>::value;
};

template<typename T>
struct value_type
{
    typedef T type;
};

template<typename T>
struct value_type<std::complex<T> >
{
    typedef T type;
};
template<typename T>
struct value_type<std::complex<T> &>
{
    typedef T type;
};
template<typename T>
struct value_type<const std::complex<T> &>
{
    typedef T type;
};
template<typename T>
struct value_type<const std::complex<T>>
{
    typedef T type;
};





//type category
enum{
    TYPE_CAT_INT,
    TYPE_CAT_FLOAT,
    TYPE_CAT_COMPLEX,
};

} //namespace ipp


#include "detail/ipptype.hpp"


namespace ipp{

template<size_t Size, bool Signed>
struct get_int
{
    typedef typename detail::get_int<Size, Signed>::type type;
};


template<typename T>
struct type_cat_index
{
    static const int value = 
        detail::type_cat_index<T, is_complex<T>::value >::value;
};


template<typename T>
struct get
{
    typedef typename detail::get<
        T, type_cat_index<T>::value>::type type;
};


template<typename T>
struct type_value
{
    static const IppDataType value = 
        detail::type_value<get<T>::type>::value;
};


typedef enum{
    LOW,
    MEDIUN,
    HIGH
}PerciseType;


}

/*@}*/

#endif
