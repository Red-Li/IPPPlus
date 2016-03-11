/** 
 * @file ipps_extension.hpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2016-03-11
 */


#ifndef IPPPLUS_IPPS_DETAIL_EXTENSION_HPP
#define IPPPLUS_IPPS_DETAIL_EXTENSION_HPP


namespace ipp{
namespace detail{

template<typename T>
void transpose(const T *src, T *dst, int nrows, int ncols)
{
    for(int i = 0; i < nrows; ++i)
        for(int j = 0; j < ncols; ++j)
            dst[j*nrows+i] = src[i*ncols+j];
}


template<typename T, bool InPlace>
void prefix_sum(const T *src, T *dst, int size)
{
    T sum = 0;
    for(int i = 0; i < size; ++i){
        sum += src[i];
        dst[i] = sum;
    }
}



}}
#endif
