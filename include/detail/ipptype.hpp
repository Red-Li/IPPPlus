/**
 * @file ipptype_detail.hpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2014-12-26
 */

#ifndef IPPPLUS_DETAIL_IPPTYPE_HPP
#define IPPPLUS_DETAIL_IPPTYPE_HPP

namespace ipp{
namespace detail{

template<typename T, bool Cplx>
struct type_cat_index;

template<typename T>
struct type_cat_index<T, true>
{
    static const int value = TYPE_CAT_COMPLEX;
};

template<typename T>
struct type_cat_index<T, false>
{
    static const int value = TYPE_CAT_INT + is_float<T>::value;
};


/* --------------------------------------------------------------------------*/
/**
 * @brief get integer type by size and signed flag 
 *
 * @tparam Size
 * @tparam Signed
 */
/* ----------------------------------------------------------------------------*/
template<int Size, bool Signed>
struct get_int
{
    static_assert(Size == 0, "unsupported integer type");
};

template<>
struct get_int<1, true>{ typedef Ipp8s type;};
template<>
struct get_int<1, false>{ typedef Ipp8u type;};
template<>
struct get_int<2, true>{ typedef Ipp16s type;};
template<>
struct get_int<2, false>{ typedef Ipp16u type;};
template<>
struct get_int<4, true>{ typedef Ipp32s type;};
template<>
struct get_int<4, false>{ typedef Ipp32u type;};
template<>
struct get_int<8, true>{ typedef Ipp64s type;};
template<>
struct get_int<8, false>{ typedef Ipp64u type;};


template<typename T>
struct get_float
{
    static_assert(sizeof(T) == 0, "unsupported float type");
};

template<>
struct get_float<float>{ typedef Ipp32f type; };
template<>
struct get_float<double>{ typedef Ipp64f type; };


template<typename T>
struct get_cplx
{
    static_assert(sizeof(T) == 0, "unsupported complex type");
};

template<>
struct get_cplx<float> { typedef Ipp32fc type; };
template<>
struct get_cplx<double> { typedef Ipp64fc type; };


template<typename T, int Tid>
struct get;

template<typename T>
struct get<T, TYPE_CAT_INT>
{
    typedef typename get_int<
        sizeof(T), is_signed_integer<T>::value>::type type;
};
template<typename T>
struct get<T, TYPE_CAT_COMPLEX>
{
    typedef typename get_cplx<typename value_type<T>::type>::type type;
};
template<typename T>
struct get<T, TYPE_CAT_FLOAT>
{
    typedef typename get_float<T>::type type;
};




}}
#endif