/**
 * @file ipptype_test.hpp
 * @Brief 
 * @author Red Li
 * @version 
 * @date 2014-12-26
 */

#include "ipptype.hpp"

#define STATIC_CHECK(exp) static_assert((exp), #exp)
#define CHECK_SAME(T0, T1) static_assert(std::is_same<T0, T1>::value, #T0 " is not same as " #T1)

STATIC_CHECK(ipp::is_integer<int>::value);
STATIC_CHECK(ipp::is_integer<char>::value);
STATIC_CHECK(!ipp::is_integer<float>::value);
STATIC_CHECK(!ipp::is_integer<double>::value);
STATIC_CHECK(!ipp::is_integer<std::complex<float> >::value);

STATIC_CHECK(!ipp::is_float<int>::value);
STATIC_CHECK(ipp::is_float<float>::value);
STATIC_CHECK(ipp::is_float<double>::value);
STATIC_CHECK(!ipp::is_float<std::complex<double> >::value);

STATIC_CHECK(!ipp::is_complex<int>::value);
STATIC_CHECK(!ipp::is_complex<float>::value);
STATIC_CHECK(ipp::is_complex<std::complex<float> >::value);

STATIC_CHECK(ipp::type_index<int>::value == ipp::TYPE_INT);
STATIC_CHECK(ipp::type_index<float>::value == ipp::TYPE_FLOAT);
STATIC_CHECK(ipp::type_index<std::complex<float> >::value == ipp::TYPE_COMPLEX);

STATIC_CHECK(ipp::is_signed_integer<int>::value);
STATIC_CHECK(!ipp::is_signed_integer<unsigned int>::value);

CHECK_SAME(ipp::get<char>::type, Ipp8s);
CHECK_SAME(ipp::get<unsigned char>::type, Ipp8u);
CHECK_SAME(ipp::get<int8_t>::type, Ipp8s);
CHECK_SAME(ipp::get<uint8_t>::type, Ipp8u);

CHECK_SAME(ipp::get<short>::type, Ipp16s);
CHECK_SAME(ipp::get<unsigned short>::type, Ipp16u);
CHECK_SAME(ipp::get<int16_t>::type, Ipp16s);
CHECK_SAME(ipp::get<uint16_t>::type, Ipp16u);

CHECK_SAME(ipp::get<float>::type, Ipp32f);
CHECK_SAME(ipp::get<double>::type, Ipp64f);

CHECK_SAME(ipp::get<std::complex<float>>::type, Ipp32fc);
CHECK_SAME(ipp::get<std::complex<double>>::type, Ipp64fc);


#undef STATIC_CHECK
#undef CHECK_SAME

