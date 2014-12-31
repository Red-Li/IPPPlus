/**
 * @file ipptype_test.hpp
 * @Brief 
 * @author Red Li
 * @version 
 * @date 2014-12-26
 */

#include "ipptype.hpp"

#include "test_utils.hpp"

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

STATIC_CHECK(ipp::type_cat_index<int>::value == ipp::TYPE_CAT_INT);
STATIC_CHECK(ipp::type_cat_index<float>::value == ipp::TYPE_CAT_FLOAT);
STATIC_CHECK(ipp::type_cat_index<std::complex<float> >::value == ipp::TYPE_CAT_COMPLEX);

STATIC_CHECK(ipp::is_signed_integer<int>::value);
STATIC_CHECK(!ipp::is_signed_integer<unsigned int>::value);

SAME_TYPE_CHECK(ipp::get<char>::type, Ipp8s);
SAME_TYPE_CHECK(ipp::get<unsigned char>::type, Ipp8u);
SAME_TYPE_CHECK(ipp::get<int8_t>::type, Ipp8s);
SAME_TYPE_CHECK(ipp::get<uint8_t>::type, Ipp8u);

SAME_TYPE_CHECK(ipp::get<short>::type, Ipp16s);
SAME_TYPE_CHECK(ipp::get<unsigned short>::type, Ipp16u);
SAME_TYPE_CHECK(ipp::get<int16_t>::type, Ipp16s);
SAME_TYPE_CHECK(ipp::get<uint16_t>::type, Ipp16u);

SAME_TYPE_CHECK(ipp::get<float>::type, Ipp32f);
SAME_TYPE_CHECK(ipp::get<double>::type, Ipp64f);

SAME_TYPE_CHECK(ipp::get<std::complex<float>>::type, Ipp32fc);
SAME_TYPE_CHECK(ipp::get<std::complex<double>>::type, Ipp64fc);
SAME_TYPE_CHECK(ipp::get<std::complex<short>>::type, Ipp16sc);
SAME_TYPE_CHECK(ipp::get<std::complex<int16_t>>::type, Ipp16sc);
SAME_TYPE_CHECK(ipp::get<std::complex<int>>::type, Ipp32sc);



