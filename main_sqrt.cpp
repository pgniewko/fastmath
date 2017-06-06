/*
 * Author : Pawel Gniewek (UC Berkeley)
 * Email  : pawel.gniewek@berkeley.edu
 * License: BSD
 */

#include <iostream>    /* cout, cin */
#include <math.h>      /* log, sqrt */
//#include <cmath>      /* log, sqrt */


#include "src/random.h"
#include "src/Timer.h"
#include "src/fastmath.h"

Timer clocks[4];
double simulation_time;

int main(int argc, char** argv)
{
    unsigned long init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
    init_by_array(init, length);

    int N = 10000;
    double rnd_numbers[N];
    for (int i = 0; i < N; i++)
    {
        rnd_numbers[i] = uniform(0.0, 2.0);

    }
    double* rnd_number = rnd_numbers;

    double tmp = 0.0;
    double result_sqrt1 = 0.0;
    double result_sqrt2 = 0.0;
    double result_invsqrt1 = 0.0;
    double result_invsqrt2 = 0.0;

    // WARM-UP RUN
    for (int i = 0; i < N; i++)
    {
        tmp += fabs( sqrt(*rnd_number) );
        tmp += fabs( fastmath::fast_sqrt(*rnd_number) );
        tmp += fabs( 1.0/sqrt(*rnd_number) );
        tmp += fabs( fastmath::fast_invsqrt(*rnd_number) );
        rnd_number++;
    }

    // TEST NUMBER 1
    clocks[0].tic();
    for (int i = 0; i < N; i++)
    {
        rnd_number = rnd_numbers;
        
        for (int j = 0; j < N; j++)
        {
            result_sqrt1 += fabs( sqrt(*rnd_number) );
            rnd_number++;
        }
    }
    clocks[0].toc();


    clocks[1].tic();
    for (int i = 0; i < N; i++)
    {
        rnd_number = rnd_numbers;
        
        for (int j = 0; j < N; j++)
        {
            result_sqrt2 += fabs( fastmath::fast_sqrt(*rnd_number) );
            rnd_number++;
        }
    }
    clocks[1].toc();


    clocks[2].tic();
    for (int i = 0; i < N; i++)
    {
        rnd_number = rnd_numbers;
        for (int j = 0; j < N; j++)
        {
            result_invsqrt1 += fabs( 1.0 / sqrt(*rnd_number) );
            rnd_number++;
        }
    }
    clocks[2].toc();

    clocks[3].tic();
    for (int i = 0; i < N; i++)
    {
        rnd_number = rnd_numbers;
        for (int j = 0; j < N; j++)
        {
            result_invsqrt2 += fabs( fastmath::fast_invsqrt(*rnd_number) );
            rnd_number++;
        }
    }
    clocks[3].toc();


    // TIMING RESULTS
    std::cout << "== TEST 1 ==" << "\n";
    std::cout << "RESIDUAL ERROR FOR SQRT (per call)        = " << (result_sqrt1 - result_sqrt2) / (N*N) <<"\n";
    std::cout << "TOTAL EXECUTION [SQRT]  WALL-TIME         = " << clocks[0].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [FAST_SQRT]  WALL-TIME    = " << clocks[1].time() << " [s] \n";
    std::cout << "TOTAL SPEEDUP [FAST_SQRT/SQRT]            = " << clocks[0].time() / clocks[1].time() << "\n";

    std::cout << "== TEST 2 ==" << "\n";
    std::cout << "RESIDUAL ERROR FOR INV_SQRT (per call)    = " << (result_invsqrt1 - result_invsqrt2) / (N*N) <<"\n";
    std::cout << "TOTAL EXECUTION [INVSQRT]  WALL-TIME      = " << clocks[2].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [FAST_INVSQRT]  WALL-TIME = " << clocks[3].time() << " [s] \n";
    std::cout << "TOTAL SPEEDUP [FAST_INVSQRT/INVSQRT       = " << clocks[2].time() / clocks[3].time() << "\n";

    return (EXIT_SUCCESS);
}
