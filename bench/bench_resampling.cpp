/**
 * @file bench_resampling.cpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2015-03-16
 */


#include <gtest/gtest.h>
#include <cmath>

#include "ipps.hpp"
#include "ipps_extension.hpp"

namespace ipps{


///////PolyphaseResample////
typedef std::pair<int, int> ResamplePair;

#ifndef M_PI
#define M_PI 3.1415926f 
#endif

float kaiserBeta(float As)
{
    if(As > 50.f)
        return 0.1102f * (As - 8.7f);
    else if(As >= 21.f)
        return 0.5842f * pow(As - 21.f, 0.4f) + 0.07886f * (As - 21.f);
    else
        return 0.f;
}

int kaiserTapsEstimate(float delta, float As)
{
    return int((As - 8.f) / (2.285 * delta) + 0.5);
}




template<typename T>
long polyphaseResampleFixed(int inFreq,
                            int outFreq,
                            long inSize,
                            int psize,
                            float rollf = 0.9f,
                            float As = 80.f //Db
                            )
{
    float alpha = kaiserBeta(As);
    float delta = (1.f - rollf) * M_PI;
    int N = kaiserTapsEstimate(delta, As);

    ipp::polyphase_resampling_fixed<T> pf(inFreq, outFreq, N, rollf, alpha);


    int history = int(pf.filter_length() / 2 + 0.5);

    T *bufIn = ipp::malloc<T>(psize + history + 2);
    T *bufOut = ipp::malloc<T>(int((psize - history) * outFreq / float(inFreq)) + 2);

#if 0
	int fflen = pf.get_filter(bufIn);
	FILE *fp = fopen("filter.bin", "wb");
	fwrite(bufIn, sizeof(T)* fflen, 1, fp);
	fclose(fp);
#endif

    for(int i = 0; i < psize + history + 2; ++i)
        bufIn[i] = T(i % 10);

    long counter = 0;
    long outCounter = 0;
    double time = history;
    int lastread = history;

    while(counter < inSize){
		int nread = psize - lastread;
        int nout = 0;
        lastread += nread;

        pf.resample(bufIn, lastread - history - (int)time,
                    bufOut, &nout, &time, 1.f); 

        ipp::move<T>(bufIn + (int)time - history, bufIn, lastread - (int)time + history);
        lastread -= (int)time - history;
        time -= (int)time - history;

        outCounter += nout;
        counter += nread;
    }

    ipp::free(bufIn);
    ipp::free(bufOut);

    return outCounter;
}


template<typename T>
long polyphaseResample(int inFreq,
                       int outFreq,
                       long inSize,
                       int psize,
                       float rollf = 0.9f,
                       float As = 80.f //Db
                        )
{
    float alpha = kaiserBeta(As);
    float delta = (1.f - rollf) * M_PI;
    float a = inFreq / float(outFreq);
	int nstep = a > 1 / a ? int(a) : int(1 / a) ;

    int N = kaiserTapsEstimate(delta / nstep, As);
    float win = N / float(nstep);
    int history = N;

    ipp::polyphase_resampling<T> pf(win, nstep, rollf, alpha);


    T *bufIn = ipp::malloc<T>(psize + history + 2);
    T *bufOut = ipp::malloc<T>(int((psize - history) * outFreq / float(inFreq)) + 2);

    for(int i = 0; i < psize + history + 2; ++i)
        bufIn[i] = T(i % 10);

    long counter = 0;
    long outCounter = 0;
    double time = history;
    int lastread = history;

    while(counter < inSize){
		int nread = psize - lastread;
        int nout = 0;
        lastread += nread;

        pf.resample(bufIn, lastread - history - (int)time,
                    bufOut, &nout, &time, 1. / a, 1.f); 

        ipp::move<T>(bufIn + (int)time - history, bufIn, lastread - (int)time + history);
        lastread -= (int)time - history;
        time -= (int)time - history;

        outCounter += nout;
        counter += nread;
    }

    ipp::free(bufIn);
    ipp::free(bufOut);

    return outCounter;
}


class PolyphaseResample : public testing::TestWithParam<ResamplePair>
{
public:

};

//
TEST_P(PolyphaseResample, ResampleFixed)
{
    auto pair = GetParam();
    int insize = 1 << 23;
    int psize = 1 << 14;

    polyphaseResampleFixed<float>(
            pair.first,
            pair.second,
            insize, 
            psize);


    RecordProperty("BenchCount", insize);
    RecordProperty("BenchCountUnit", "B");
}


TEST_P(PolyphaseResample, Resample)
{
    auto pair = GetParam();
    int insize = 1 << 23;
    int psize = 1 << 14;

    polyphaseResample<float>(
            pair.first,
            pair.second,
            insize, 
            psize);


    RecordProperty("BenchCount", insize);
    RecordProperty("BenchCountUnit", "B");
}


INSTANTIATE_TEST_CASE_P(PolyphaseResample, PolyphaseResample,
	::testing::Values(
			ResamplePair(1, 10),
			ResamplePair(2, 10),
			ResamplePair(3, 10),
			ResamplePair(5, 10),
			ResamplePair(6, 10),
			ResamplePair(7, 10)
	));






template<typename T>
long integerResampleBench(int N,
                     int idx,
                     float rollf,
                     long inSize,
                     int psize
                     )
{
    double dw = M_PI / N;
    double wp = dw / 2. * rollf;
    double ws = dw / 2.;

    int ntaps = ipp::fir_tap_estimate(wp, ws, 1., 50.);

    ipp::integer_sample_down<T> is(N, idx, ntaps, 0, 0.5f * rollf + 0.5f);

    int CACHE = 16 << 20;
    int nbuf = CACHE / psize - 1;

    T *sbuf = ipp::malloc<T>(CACHE);
    T *dbuf = ipp::malloc<T>(CACHE);

#if 0
    //sample rate
    float srate = 1.f;
    float dt = 1.f / srate;
    ipp::vector_slope<T>(sbuf, CACHE, 0.f, dt); 
    ipp::copy<T>(sbuf, dbuf, CACHE);
    ipp::mul<T>(sbuf, sbuf, sbuf, CACHE);
    ipp::mul_const<T>(sbuf, T(M_PI_2) * 0.6f / inSize / 2.5f, sbuf, CACHE);
    ippsSin_32f_A24(sbuf, sbuf, CACHE);
#else
    ipp::rand_uniform<T> ru(0., 1., 0);

    ru.generate(sbuf, CACHE);

#endif

    int counter = 0;
    int ocounter = 0;
    while(counter < inSize){
        T *src = sbuf + (counter % CACHE);
        T *dst = dbuf + (ocounter % CACHE);

        int olen = 0;
        is.resample(src, psize, dst, &olen);

        ocounter += olen;
        counter += psize;
    }
    
#if 0
    FILE *fp = fopen("integer_resample.bin", "wb");
    T header[5] = { T(N), T(idx), T(counter), T(ocounter), T(is.ntaps())};
    
    fwrite(header, sizeof(T), 5, fp);
    fwrite(sbuf, sizeof(T), counter, fp);
    fwrite(dbuf, sizeof(T), ocounter, fp);
    
    is.get_taps(dbuf);
    fwrite(dbuf, sizeof(T), is.ntaps(), fp);

    fclose(fp);

#endif


    ipp::free(sbuf);
    ipp::free(dbuf);

    return ocounter;
}



class IntegerResample : public testing::TestWithParam<int>
{
public:

};

//
TEST_P(IntegerResample, ResampleFixed)
{
    auto N = GetParam();
    int insize = 1 << 27;
    int psize = 1 << 16;

    integerResampleBench<float>(
            N,
            1,
            0.9f,
            insize, 
            psize);

    RecordProperty("BenchCount", insize / 1000000);
    RecordProperty("BenchCountUnit", "MB");
}


#if 1
INSTANTIATE_TEST_CASE_P(IntegerResample, IntegerResample,
	::testing::Values(
        2,
        3, 
        4,
        6,
        10,
        15,
        30,
        40,
        50,
        100,
        200
	));

#else
INSTANTIATE_TEST_CASE_P(IntegerResample, IntegerResample,
	::testing::Values(
		10
	));
#endif










}
