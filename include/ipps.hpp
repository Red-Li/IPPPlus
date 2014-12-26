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

namespace ipp{


/**
 * @defgroup VectorInitFunc Vector Initialization Functions
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
static inline IppStatus copy(const T* src, T* dst, int len);

#define COPY_ASM(Type, Suffix)\
    template<>\
    static inline IppStatus copy(const Type *src, Type *dst, int len)\
    {\
        typedef get<Type>::type ipptype;\
        return ippsCopy_#Suffix((const ipptype*)src, (ipptype*)dst, len);\
    }

COPY_ASM(int8_t, 8s);
COPY_ASM(int16_t, 16s);
COPY_ASM(int32_t, 32s);
COPY_ASM(int64_t, 64s);
COPY_ASM(float, 32f);
COPY_ASM(double, 64f);
COPY_ASM(std::complex<float>, 32fc);
COPY_ASM(std::complex<double>, 64fc);


template<typename T>
static inline IppStatus move(const T* src, T* dst, int len);

#define MOVE_ASM(Type, Suffix)\
template<>\
static inline IppStatus move(const Type *src, Type *dst, int len)\
{\
    typedef get<Type>::type ipptype;\
    return ippsMove_#Suffix((const ipptype*)src, (ipptype*)dst, len)






/**@}*/

}

#endif
