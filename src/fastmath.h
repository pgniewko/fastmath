#ifndef FAST_MATH_H
#define	FAST_MATH_H

#define SQRT_MAGIC_D 0x5fe6ec85e7de30da

namespace fastmath
{
    inline double fast_sin(double x)
    {
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
        union
        {
            double x;
            uint64_t i;
        } u { invpi* x + magicround };
        uint64_t odd_period = u.i << 63;
        u.x = x + negpi * int32_t(u.i & 0xffffffff);

        // 7th degree odd polynomial followed by IEEE754 sign flip on odd periods.
        double x2 = u.x * u.x;
        double p = d + x2 * (c + x2 * (b + x2 * a));
        u.i ^= odd_period;
        return u.x * p;
    }

    inline double fast_cos(double x)
    {
        const double pi_2 =  1.57079632679489661923132169163975144;
        return fast_sin(x + pi_2);
    }

    inline double fast_invsqrt(double x)
    {
        const double xhalf = 0.5F * x;
        union // get bits for floating value
        {
            double x;
            long i;
        } u;

        u.x = x;
        u.i = SQRT_MAGIC_D - (u.i >> 1);  // gives initial guess y0
//        u.x = u.x*(1.5F - xhalf*u.x*u.x);
        u.x = u.x * (1.5F - xhalf * u.x * u.x);
        return u.x * (1.5F - xhalf * u.x * u.x); // Newton step, repeating increases accuracy
    }

    inline double fast_sqrt(double x)
    {
        return x * fast_invsqrt(x);
    }
}

#endif
