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


class Fir : public testing::TestWithParam<int>
{
public:

};

template<typename T>
void fir_sr_bench(int isize, int psize, int ntaps, IppAlgType alg)
{
    T *taps = ipp::malloc<T>(ntaps);

    int CACHE = 16 << 20;
    int nbuf = CACHE / psize - 1;

    T *sbuf = ipp::malloc<T>(CACHE);
    T *dbuf = ipp::malloc<T>(CACHE);

    ipp::fir_sr<T> fs(taps, ntaps, alg);

    int counter = 0;
    while(counter < isize){
        T *src = sbuf + (rand() % nbuf) * psize;
        T *dst = dbuf + (rand() % nbuf) * psize;

        fs.filter(src, dst, psize, true);
        counter += psize;
    }

    ipp::free(taps);
    ipp::free(sbuf);
    ipp::free(dbuf);

}

template<typename T>
void fir_bench(int isize, int psize, int ntaps)
{
    T *taps = ipp::malloc<T>(ntaps);

    int CACHE = 16 << 20;
    int nbuf = CACHE / psize - 1;

    T *sbuf = ipp::malloc<T>(CACHE);
    T *dbuf = ipp::malloc<T>(CACHE);

    ipp::fir<T> fs(taps, ntaps);

    int counter = 0;
    while(counter < isize){
        T *src = sbuf + (rand() % nbuf) * psize;
        T *dst = dbuf + (rand() % nbuf) * psize;

        fs.filter(src, dst, psize);
        counter += psize;
    }

    ipp::free(taps);
    ipp::free(sbuf);
    ipp::free(dbuf);
}

template<typename T>
void fir_mr_bench(int isize, int psize, int ntaps, int up, int down)
{
    T *taps = ipp::malloc<T>(ntaps);

    int CACHE = 16 << 20;
    int nbuf = CACHE / psize - 2;

    T *sbuf = ipp::malloc<T>(CACHE);
    T *dbuf = ipp::malloc<T>(CACHE);

    ipp::fir_mr<T> fs(taps, ntaps, up, 0, down, 0);

    int counter = 0;
    while(counter < isize){
		T *src = sbuf;// +(rand() % nbuf) * psize;
		T *dst = dbuf;// +(rand() % nbuf) * psize;

        int ret = fs.filter(src, dst, psize);
        if(ret != 0){
            std::cerr << "FirMr filter failed " << ret << std::endl;
            break;
        }

        counter += psize;
    }

    ipp::free(taps);
    ipp::free(sbuf);
    ipp::free(dbuf);
}





//
TEST_P(Fir, FirSRDirect)
{
    auto ntaps = GetParam();
    int insize = 1 << 23;
    int psize = 1 << 14;

    fir_sr_bench<float>(insize, psize, ntaps, ippAlgDirect);

    RecordProperty("BenchCount", insize / (1 << 20));
    RecordProperty("BenchCountUnit", "MB");
}

TEST_P(Fir, FirSRFFT)
{
    auto ntaps = GetParam();
    int insize = 1 << 23;
    int psize = 1 << 14;

    fir_sr_bench<float>(insize, psize, ntaps, ippAlgFFT);

    RecordProperty("BenchCount", insize / (1 << 20));
    RecordProperty("BenchCountUnit", "MB");
}

TEST_P(Fir, FirNormal)
{
    auto ntaps = GetParam();
    int insize = 1 << 25;
    int psize = 1 << 16;

    fir_bench<float>(insize, psize, ntaps);

    RecordProperty("BenchCount", insize / (1 << 20));
    RecordProperty("BenchCountUnit", "MB");
}

TEST_P(Fir, FirMR)
{
    auto ntaps = GetParam();
    int insize = 1 << 25;
    int psize = 1 << 16;

    fir_mr_bench<float>(insize, psize, ntaps, 1, 10);

    RecordProperty("BenchCount", insize / (1 << 20));
    RecordProperty("BenchCountUnit", "MB");
}


INSTANTIATE_TEST_CASE_P(Fir, Fir,
	::testing::Values(
        10,
        30, 
        60,
        120,
        240,
        480,
        980,
        1960
	));

}
