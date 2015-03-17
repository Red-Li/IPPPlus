/**
 * @file bench_fft.cpp
 * @brief 
 * @author Red Li
 * @version 
 * @date 2015-03-17
 */


#include <gtest/gtest.h>
#include <cmath>

#include "ipps.hpp"

namespace ipps{


///////PolyphaseResample////

#ifndef M_PI
#define M_PI 3.1415926f 
#endif

static float kaiserBeta(float As)
{
    if(As > 50.f)
        return 0.1102f * (As - 8.7f);
    else if(As >= 21.f)
        return 0.5842f * pow(As - 21.f, 0.4f) + 0.07886f * (As - 21.f);
    else
        return 0.f;
}

static int kaiserTapsEstimate(float delta, float As)
{
    return int((As - 8.f) / (2.285 * delta) + 0.5);
}


class FFT : public testing::TestWithParam<int>
{
public:

};

template<typename T>
void bench_fft(long long isize, int order)
{
    ipp::fft<T, false> ft(order);

    int CACHE = 16 << 20;
    int psize = 1 << order;
    int nbuf = CACHE / psize - 1;

    T *sbuf = ipp::malloc<T>(CACHE);
    T *dbuf = ipp::malloc<T>(CACHE);

    long long counter = 0;
    while(counter < isize){
        T *src = sbuf + (rand() % nbuf) * psize;
        T *dst = dbuf + (rand() % nbuf) * psize;

        int ret = ft.forward(src, dst);
		if (ret != 0){
			ft.forward(src, dst);
			std::cerr << "FFT forward failed " << ret << std::endl;
			break;
		}

        counter += psize;
    }

    ipp::free(sbuf);
    ipp::free(dbuf);
}


//
TEST_P(FFT, FFTRealFoward)
{
    auto  order = GetParam();
    long long insize = 1LL << 30;

    bench_fft<float>(insize, order); 

    RecordProperty("BenchCount", int(insize / (1 << 20)));
    RecordProperty("BenchCountUnit", "MB");
}

INSTANTIATE_TEST_CASE_P(FFT, FFT,
	::testing::Values(
        4,
        6, 
        8,
        10,
        12,
        14,
        16,
        18,
        20,
        22
	));

}
