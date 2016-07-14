/*
 * Author : Pawel Gniewek (UC Berkeley)
 * Email  : pawel.gniewek@berkeley.edu
 * License: BSD
 */

#include <iostream>    /* cout, cin */
#include <math.h>      /* log, sqrt */


#include "src/random.h"
#include "src/Timer.h"
#include "src/fastmath.h"

Timer clocks[2];
double simulation_time;

int main(int argc, char** argv)
{
    unsigned long init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
    init_by_array(init, length);

    int N = 15000;
    double rnd_numbers[N];
    for (int i = 0; i < N; i++)
    {
        rnd_numbers[i] = uniform(-3.14159265358979*5.0, 3.14159265358979*5.0);

    }
    double* rnd_number = rnd_numbers;

    double tmp = 0.0;
    double result_sin1 = 0.0;
    double result_sin2 = 0.0;
    double result_cos1 = 0.0;
    double result_cos2 = 0.0;

    // WARM-UP RUN
    for (int i = 0; i < N; i++)
    {
        tmp += fabs( sin(*rnd_number) );
        tmp += fabs( fastmath::fast_cos(*rnd_number) );
        rnd_number++;
    }

    // TEST NUMBER 1
    clocks[0].tic();
    for (int i = 0; i < N; i++)
    {
        rnd_number = rnd_numbers;
        
        for (int j = 0; j < N; j++)
        {
            result_sin1 += fabs( sin(*rnd_number) );
            result_cos1 += fabs( cos(*rnd_number) );
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
            result_sin2 += fabs( fastmath::fast_sin(*rnd_number) );
            result_cos2 += fabs( fastmath::fast_cos(*rnd_number) );
            rnd_number++;
        }
    }
    clocks[1].toc();


    // TIMING RESULTS
    std::cout << "== TEST 1 ==" << "\n";
    std::cout << "RESIDUAL ERROR FOR SIN (per call) = " << (result_sin1 - result_sin2) / (N*N) <<"\n";
    std::cout << "RESIDUAL ERROR FOR COS (per call) = " << (result_cos1 - result_cos2) / (N*N) <<"\n";
    std::cout << "TOTAL EXECUTION [SIN/COS] WALL-TIME = "           << clocks[0].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [FAST_SIN/FAST_COS] WALL-TIME = " << clocks[1].time() << " [s] \n";

    return (EXIT_SUCCESS);
}
