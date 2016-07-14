/*
 * Author : Pawel Gniewek (UC Berkeley)
 * Email  : pawel.gniewek@berkeley.edu
 * License: BSD
 */

#include <iostream>    /* cout, cin */
#include <math.h>      /* log, sqrt */


#include "src/random.h"
#include "src/Timer.h"

inline double fast_sin(double x) {
    // Polynomial constants generated with sollya.
    // fpminimax(sin(x), [|1,3,5,7|], [|D...|], [-pi/2;pi/2]);
    // Both relative and absolute error is 9.39e-7.
    const double magicround =  6755399441055744.0;
    const double negpi      = -3.14159265358979323846264338327950288;
    const double invpi      =  0.31830988618379067153776752674502872;
    const double a          = -0.00018488140186756154724131984146140;
    const double b          =  0.00831189979755905285208061883395203;
    const double c          = -0.16665554092439083255783316417364403;
    const double d          =  0.99999906089941981157664940838003531;

    // Range-reduce to [-pi/2, pi/2] and store if period is odd.
    union { double x; uint64_t i; } u { invpi*x + magicround };
    uint64_t odd_period = u.i << 63;
    u.x = x + negpi*int32_t(u.i & 0xffffffff);

    // 7th degree odd polynomial followed by IEEE754 sign flip on odd periods.
    double x2 = u.x*u.x;
    double p = d + x2*(c + x2*(b + x2*a));
    u.i ^= odd_period;
    return u.x * p;
}

inline double fast_cos(double x) {
    const double pi_2 =  1.57079632679489661923132169163975144;
    return fast_sin(x + pi_2);
}


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
        tmp += fabs( fast_cos(*rnd_number) );
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
            result_sin2 += fabs( fast_sin(*rnd_number) );
            result_cos2 += fabs( fast_cos(*rnd_number) );
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
