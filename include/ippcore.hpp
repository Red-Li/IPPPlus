/**
 * @file ippcore.hpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2014-12-19
 */

#ifndef IPPPLUS_IPPCORE_HPP
#define IPPPLUS_IPPCORE_HPP


#include <ippcore.h>

#include "ipptype.hpp"

namespace ipp{

static inline const IppLibraryVersion *getLibVersion()
{
    return ippGetLibVersion();
}

static inline IppStatus init()
{
    return ippInit();
}


/* --------------------------------------------------------------------------*/
/**
 * @brief allocate memory aligned to 64-byte boundary 
 *
 * @tparam T
 * @param len
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
template<typename T>
static inline void* malloc(int len)
{
    return ippMalloc(sizeof(get<T>::type) * len);
};


}

#endif
