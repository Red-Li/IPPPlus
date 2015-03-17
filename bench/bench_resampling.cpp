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

namespace ipps{

template<typename T>
T from_int(int v)
{
    return T(v);
}

template<>
std::complex<float> from_int<std::complex<float> >(int v)
{
    return std::complex<float>((float)v, (float)v);
}

template<>
std::complex<double> from_int<std::complex<double> >(int v)
{
    return std::complex<double>(v, v);
}

template<>
std::complex<short> from_int<std::complex<short> >(int v)
{
    return std::complex<short>((short)v, (short)v);
}

template<>
std::complex<int> from_int<std::complex<int> >(int v)
{
    return std::complex<int>(v, v);
}


template<typename T>
T _sqrt(T v)
{
	return sqrt(v);
}

template<>
unsigned char _sqrt(unsigned char v)
{
	return (unsigned char)sqrt(float(v));
}

template<>
short _sqrt(short v)
{
	return (short)sqrt(float(v));
}

template<>
unsigned short _sqrt(unsigned short v)
{
	return (unsigned short)sqrt(float(v));
}


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


INSTANTIATE_TEST_CASE_P(PolyphaseResample, PolyphaseResample,
	::testing::Values(
			ResamplePair(1, 10),
			ResamplePair(2, 10),
			ResamplePair(3, 10),
			ResamplePair(5, 10),
			ResamplePair(6, 10),
			ResamplePair(7, 10)
	));

}
