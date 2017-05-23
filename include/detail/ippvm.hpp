/** 
 * @file ippvm.hpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2016-03-09
 */

#ifndef IPPPLUS_DETAIL_IPPVM_HPP
#define IPPPLUS_DETAIL_IPPVM_HPP

#include <ippvm.h>
#include "ipptype.hpp"

namespace ipp{
namespace detail{


template<typename T, PerciseType P>
static inline IppStatus sincos(const T*, T*, T*, int);

#define SINCOS_INST(T, TF, P, SF)\
template<>\
static inline IppStatus sincos<T, P>(const T *src, T *sin, T *cos, int len)\
{\
    return ippsSinCos_##TF##_##SF(src, sin, cos, len);\
}


SINCOS_INST(Ipp32f, 32f, LOW, A11)
SINCOS_INST(Ipp32f, 32f, MEDIUN, A21)
SINCOS_INST(Ipp32f, 32f, HIGH, A24)
SINCOS_INST(Ipp64f, 64f, LOW, A26)
SINCOS_INST(Ipp64f, 64f, MEDIUN, A50)
SINCOS_INST(Ipp64f, 64f, HIGH, A53)

#undef SINCOS_INST

template<typename T, PerciseType P>
static inline IppStatus sin(const T*, T*, int);

#define SIN_INST(T, TF, P, SF)\
template<>\
static inline IppStatus sin<T, P>(const T *src, T *dst, int len)\
{\
    return ippsSin_##TF##_##SF(src, dst, len);\
}


SIN_INST(Ipp32f, 32f, LOW, A11)
SIN_INST(Ipp32f, 32f, MEDIUN, A21)
SIN_INST(Ipp32f, 32f, HIGH, A24)
SIN_INST(Ipp32fc, 32fc, LOW, A11)
SIN_INST(Ipp32fc, 32fc, MEDIUN, A21)
SIN_INST(Ipp32fc, 32fc, HIGH, A24)
SIN_INST(Ipp64f, 64f, LOW, A26)
SIN_INST(Ipp64f, 64f, MEDIUN, A50)
SIN_INST(Ipp64f, 64f, HIGH, A53)
SIN_INST(Ipp64fc, 64fc, LOW, A26)
SIN_INST(Ipp64fc, 64fc, MEDIUN, A50)
SIN_INST(Ipp64fc, 64fc, HIGH, A53)

#undef SIN_INST

//

template<typename T, PerciseType P>
static inline IppStatus cos(const T*, T*, int);

#define COS_INST(T, TF, P, SF)\
template<>\
static inline IppStatus cos<T, P>(const T *src, T *dst, int len)\
{\
    return ippsCos_##TF##_##SF(src, dst, len);\
}


COS_INST(Ipp32f, 32f, LOW, A11)
COS_INST(Ipp32f, 32f, MEDIUN, A21)
COS_INST(Ipp32f, 32f, HIGH, A24)
COS_INST(Ipp32fc, 32fc, LOW, A11)
COS_INST(Ipp32fc, 32fc, MEDIUN, A21)
COS_INST(Ipp32fc, 32fc, HIGH, A24)
COS_INST(Ipp64f, 64f, LOW, A26)
COS_INST(Ipp64f, 64f, MEDIUN, A50)
COS_INST(Ipp64f, 64f, HIGH, A53)
COS_INST(Ipp64fc, 64fc, LOW, A26)
COS_INST(Ipp64fc, 64fc, MEDIUN, A50)
COS_INST(Ipp64fc, 64fc, HIGH, A53)

#undef COS_INST


//
template<typename T, PerciseType P>
static inline IppStatus log10(const T*, T*, int);

#define LOG10_INST(T, TF, P, SF)\
template<>\
static inline IppStatus log10<T, P>(const T *src, T *dst, int len)\
{\
    return ippsLog10_##TF##_##SF(src, dst, len);\
}


LOG10_INST(Ipp32f, 32f, LOW, A11)
LOG10_INST(Ipp32f, 32f, MEDIUN, A21)
LOG10_INST(Ipp32f, 32f, HIGH, A24)
LOG10_INST(Ipp32fc, 32fc, LOW, A11)
LOG10_INST(Ipp32fc, 32fc, MEDIUN, A21)
LOG10_INST(Ipp32fc, 32fc, HIGH, A24)
LOG10_INST(Ipp64f, 64f, LOW, A26)
LOG10_INST(Ipp64f, 64f, MEDIUN, A50)
LOG10_INST(Ipp64f, 64f, HIGH, A53)
LOG10_INST(Ipp64fc, 64fc, LOW, A26)
LOG10_INST(Ipp64fc, 64fc, MEDIUN, A50)
LOG10_INST(Ipp64fc, 64fc, HIGH, A53)

#undef LOG10_INST



}}

#endif
