/*
 * Author : Pawel Gniewek (UC Berkeley)
 * Email  : pawel.gniewek@berkeley.edu
 * License: BSD
 */

#include <iostream>    /* cout, cin */
#include <fstream>     /* ios, ofstream*/
#include <stdio.h>     /* printf, fgets */
#include <argp.h>      /* argp_parse */
#include <stdlib.h>    /* atoi,  strtod */
#include <math.h>      /* log, sqrt */
#include <string>

#include "src/random.h"
#include "src/Timer.h"
#include "src/Vector3Df.h"
#include "src/Vector3Dd.h"
#include "src/Vector3Dsse.h"

Timer clocks[12];
double simulation_time;

int main(int argc, char** argv)
{
    unsigned long init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
    init_by_array(init, length);

    int N = 15000;
    double x[N];
    double y[N];
    double z[N];

    for (int i = 0; i < N; i++)
    {
        x[i] = uniform(-1.0, 1.0);
        y[i] = uniform(-1.0, 1.0);
        z[i] = uniform(-1.0, 1.0);
    }

#ifdef PTR
    Vector3Dsse* v_sse_array = new Vector3Dsse[N];
    Vector3Df*   v_f_array = new Vector3Df[N];
    Vector3Dd*   v_d_array = new Vector3Dd[N];
#else
    Vector3Dsse v_sse_array[N];
    Vector3Df   v_f_array[N];
    Vector3Dd   v_d_array[N];
#endif  

    Vector3Dsse v_sse_test(1.23, 2.34, 3.45);
    Vector3Df v_f_test(1.23, 2.34, 3.45);
    Vector3Dd v_d_test(1.23, 2.34, 3.45);

//    std::cout << "== POINTER CHECK  ==" << "\n";
//    printf("%p %p %p %p %p\n", &v_sse_array[0], &v_sse_array[1], &v_sse_array[2], &v_sse_array[3], &v_sse_array[N-1]);
//    printf("%p %p %p %p %p\n", &v_f_array[0]  , &v_f_array[1]  , &v_f_array[2]  , &v_f_array[3]  , &v_f_array[N-1]);
//    printf("%p %p %p %p %p\n", &v_d_array[0]  , &v_d_array[1]  , &v_d_array[2]  , &v_d_array[3]  , &v_d_array[N-1]);

    for (int i = 0; i < N; i++)
    {
        v_sse_array[i].x = (float) x[i];
        v_sse_array[i].y = (float) y[i];
        v_sse_array[i].z = (float) z[i];

        v_f_array[i].x = (float) x[i];
        v_f_array[i].y = (float) y[i];
        v_f_array[i].z = (float) z[i];

        v_d_array[i].x = x[i];
        v_d_array[i].y = y[i];
        v_d_array[i].z = z[i];

    }

    // TEST NUMBER 1
    Vector3Dsse v_sse_t1[N];
    clocks[0].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            v_sse_t1[i] += v_sse_array[i];
        }
    }

    clocks[0].toc();

    Vector3Df v_f_t1[N];
    clocks[1].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            v_f_t1[i] += v_f_array[i];
        }
    }

    clocks[1].toc();

    Vector3Dd v_d_t1[N];
    clocks[2].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            v_d_t1[i] += v_d_array[i];
        }
    }

    clocks[2].toc();


    // TEST NUMBER 2
    clocks[3].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            v_sse_array[i].normalize();
        }
    }

    clocks[3].toc();


    clocks[4].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            v_f_array[i].normalize();
        }
    }

    clocks[4].toc();

    clocks[5].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            v_d_array[i].normalize();
        }
    }

    clocks[5].toc();



    // TEST NUMBER 3
    Vector3Dsse cross_sse[N];
    clocks[6].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            cross_sse[i] = cross_sse_func(v_sse_array[i], v_sse_test );
        }
    }

    clocks[6].toc();

    Vector3Df cross_f[N];
    clocks[7].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            cross_f[i] = crossf(v_f_array[i], v_f_test);
        }
    }

    clocks[7].toc();

    Vector3Dd cross_d[N];
    clocks[8].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            cross_d[i] = crossd(v_d_array[i], v_d_test);
        }
    }

    clocks[8].toc();

    // TEST NUMBER 4
    float l_sse[N];
    clocks[9].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            l_sse[i] = v_sse_array[i].length();
        }
    }

    clocks[9].toc();

    float l_f[N];
    clocks[10].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            l_f[i] = v_f_array[i].length();
        }
    }

    clocks[10].toc();

    float l_d[N];
    clocks[11].tic();

    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            l_d[i] = v_d_array[i].length();
        }
    }

    clocks[11].toc();

    for (int j = 0; j < N; j++)
    {
        l_sse[j] *= 1.0;
        l_f[j] *= 1.0;
        l_d[j] *= 1.0;
    }

    // TIMING RESULTS
    std::cout << "== TEST 1 (SUM)  ==" << "\n";
    std::cout << "TOTAL EXECUTION [SSE] WALL-TIME = " << clocks[0].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [FLT] WALL-TIME = " << clocks[1].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [DBL] WALL-TIME = " << clocks[2].time() << " [s] \n";

    std::cout << "== TEST 2 (NORM) ==" << "\n";
    std::cout << "TOTAL EXECUTION [SSE] WALL-TIME = " << clocks[3].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [FLT] WALL-TIME = " << clocks[4].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [DBL] WALL-TIME = " << clocks[5].time() << " [s] \n";

    std::cout << "== TEST 3 (CROSS)==" << "\n";
    std::cout << "TOTAL EXECUTION [SSE] WALL-TIME = " << clocks[6].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [FLT] WALL-TIME = " << clocks[7].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [DBL] WALL-TIME = " << clocks[8].time() << " [s] \n";

    std::cout << "== TEST 4 (LEN)  ==" << "\n";
    std::cout << "TOTAL EXECUTION [SSE] WALL-TIME = " << clocks[9].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [FLT] WALL-TIME = " << clocks[10].time() << " [s] \n";
    std::cout << "TOTAL EXECUTION [DBL] WALL-TIME = " << clocks[11].time() << " [s] \n";

#ifdef PTR
    delete[] v_sse_array;
    delete[] v_f_array;
    delete[] v_d_array;
#endif

    return (EXIT_SUCCESS);
}
