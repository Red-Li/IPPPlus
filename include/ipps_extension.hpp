/**
 * @file ipps_extension.hpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2015-03-18
 */


#ifndef IPPPLUS_IPPS_EXTENSION_HPP
#define IPPPLUS_IPPS_EXTENSION_HPP

#include "ipps.hpp"

namespace ipp{

//only support float
template<typename T>
class integer_sample_down
{
    int N_;
    int idx_;
    int time_;
    int ntaps_;

    T *taps_;
    T *wbuf_; //work buf
    T *dly_;

public:
    integer_sample_down(
            int N, int idx, int ntaps,
            T *dly,
            float rollf,
			IppWinType wtype = ippWinHamming)
        : N_(N),
          idx_(idx),
          taps_(0),
          ntaps_(ntaps | 0x1), //always be odd
          wbuf_(0),
          dly_(0),
          time_(0)
    {
        if(N < 2 || idx >= N || ntaps_ < 5)
            return;

        double *taps = ipp::malloc<double>(ntaps_);
        if(!taps)
            return;
        
        //
        dly_ = ipp::malloc<T>(ntaps_ - 1);
        if(!dly_){
            ipp::free(taps);
            return;
        }

        if(dly)
            ipp::copy<T>(dly, dly_, ntaps_ - 1);
        else
            ipp::zero<T>(dly_, ntaps_ - 1);

        //filter design
        double dw = 0.5 / N;
        IppStatus ret = ippStsNoErr;
        if(idx == 0){ //low pass
            double w = dw * rollf;
            ret = ippsFIRGenLowpass_64f(w, taps, ntaps_, wtype, ippTrue);
        }
        else if(idx == N - 1){ //high pass
            double w = 0.5 - dw * rollf;
            ret = ippsFIRGenHighpass_64f(w, taps, ntaps_, wtype, ippTrue);
        }
        else{ //band  pass
            double w = dw * (1 - rollf);
            double w1 = dw * idx + w;
            double w2 = dw * (idx + 1) - w;

            ret = ippsFIRGenBandpass_64f(
                    w1, w2, taps, ntaps_, wtype, ippTrue);
        }


        if(ret != ippStsNoErr){
            ipp::free(taps);
            ipp::free(dly_);
            return;
        }
        
        wbuf_ = ipp::malloc<T>(ntaps_);
        if(!wbuf_){
            ipp::free(taps);
            ipp::free(dly_);
            return;
        }
        
        taps_ = (T*)taps;
        for(int i = 0; i < ntaps_; ++i)
            taps_[i] = (T)taps[i];
    };

    ~integer_sample_down()
    {
        if(taps_){
            ipp::free(taps_);
            ipp::free(dly_);
            ipp::free(wbuf_);
        }
    }

    IppStatus resample(const T* src, int ilen, T *dst, int *olen)
    {
        if(!taps_)
            return ippStsMemAllocErr;

        int i = time_;
        int di = 0;
        while(i < ilen && i < ntaps_ - 1){
            int dl = ntaps_ - i - 1;
            ipp::mul<T>(dly_, taps_, wbuf_, dl);
            ipp::mul<T>(src, taps_ + dl, wbuf_ + dl, i + 1); 
            
            ipp::sum<T>(wbuf_, ntaps_, dst + di);

            ++di;
            i += N_;
        }

        while(i < ilen){
            int idx = i + 1 - ntaps_;
            ipp::mul<T>(src + idx, taps_, wbuf_, ntaps_);
            ipp::sum<T>(wbuf_, ntaps_, dst + di);

            ++di;
            i += N_;
        }

        
        time_ = i % ilen;
        ipp::copy(src + ilen - ntaps_, dly_, ntaps_);

		*olen = di;

        return ippStsNoErr;
    }

    IppStatus set_delay_line(const T *dly)
    {
        if(dly){
            return ipp::copy<T>(dly, dly_, ntaps_ - 1);
        }
        else{
            return ipp::zero<T>(dly_, ntaps_ - 1);
        }
    }
    
    void set_time(int time)
    {
        time_ = time;
    }

    int ntaps() const
    {
        return ntaps_;
    }

    IppStatus get_taps(T *taps)
    {
        if(taps_)
            return ipp::copy<T>(taps_, taps, ntaps_);
        else
            return ippStsMemAllocErr;
    }

}; //class integer_sample_down

}


#endif
