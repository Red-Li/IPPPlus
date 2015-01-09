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


template<size_t Size, bool Signed>
struct get_int_cplx
{
    static_assert(Size == 0, "unsupported integer complex");
};

template<>
struct get_int_cplx<2, true>
{
    typedef Ipp16sc type;
};

template<>
struct get_int_cplx<4, true>
{
    typedef Ipp32sc type;
};


template<typename T>
struct get_cplx
{
    typedef typename value_type<T>::type integer_type;
    static_assert(is_integer<integer_type>::value, "need integer type");
    typedef typename get_int_cplx<
        sizeof(integer_type), 
        is_signed_integer<integer_type>::value >::type type;
};

template<>
struct get_cplx<std::complex<float> >
{ 
    typedef Ipp32fc type;
};
template<>
struct get_cplx<std::complex<double> >
{
    typedef Ipp64fc type; 
};


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
    typedef typename get_cplx<T>::type type;
};
template<typename T>
struct get<T, TYPE_CAT_FLOAT>
{
    typedef typename get_float<T>::type type;
};



template<typename T>
struct type_value;

#define TYPE_VALUE_ASM(Suffix)\
template<>\
struct type_value<Ipp##Suffix>\
{ static const IppDataType value = ipp##Suffix; }

TYPE_VALUE_ASM(8s);
TYPE_VALUE_ASM(8u);
TYPE_VALUE_ASM(16s);
TYPE_VALUE_ASM(16u);
TYPE_VALUE_ASM(32s);
TYPE_VALUE_ASM(32u);
TYPE_VALUE_ASM(64s);
TYPE_VALUE_ASM(64u);
TYPE_VALUE_ASM(32f);
TYPE_VALUE_ASM(64f);
TYPE_VALUE_ASM(16sc);
TYPE_VALUE_ASM(32sc);
TYPE_VALUE_ASM(32fc);
TYPE_VALUE_ASM(64fc);


#undef TYPE_VALUE_ASM










}}
#endif
