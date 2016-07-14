#include "Timer.h"

Timer::Timer() : t0(0), final(0) {}

Timer::Timer(const Timer& orig) : t0(orig.t0), final(orig.final) {}

Timer::~Timer() {}

void Timer::tic()
{
    t0 = clock();
}

void Timer::toc()
{
    final += clock() - t0;
}

double Timer::time()
{
    return double(final) / double(CLOCKS_PER_SEC);
}

double read_timer( )
{
    static bool initialized = false;
    static struct timeval start;
    struct timeval end;

    if ( !initialized )
    {
        gettimeofday( &start, NULL );
        initialized = true;
    }

    gettimeofday( &end, NULL );
    return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}