#ifndef VECTOR3D_H
#define	VECTOR3D_H

#include <iostream>
#include <fstream>
#include <cmath>

class Vector3Dd
{
    public:
        inline Vector3Dd() : x(0), y(0), z(0) {}
        inline Vector3Dd(double a, double b, double c) : x(a), y(b), z(c) {}
        inline Vector3Dd(const Vector3Dd& orig) : x(orig.x), y(orig.y), z(orig.z) {}
        inline virtual ~Vector3Dd() {};

        inline const Vector3Dd& operator +=(const Vector3Dd& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        inline const Vector3Dd& operator -=(const Vector3Dd& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        inline const Vector3Dd& operator *=(const double a)
        {
            x *= a;
            y *= a;
            z *= a;
            return *this;
        }
        inline const Vector3Dd& operator /=(const double a)
        {
            return *this *= 1.0 / a;
        }

        inline double length() const
        {
            return sqrt(x * x + y * y + z * z);
        }
        inline double length2() const
        {
            return x * x + y * y + z * z;
        }

        inline void setLength(double r)
        {
            if (length() != 0)
            {
                double rl = r / length();
                x *= rl;
                y *= rl;
                z *= rl;
            }
        }

        inline void normalize()
        {
            double len = length();
            x /= len;
            y /= len;
            z /= len;
        }

        double x, y, z;

        inline double angle(const Vector3Dd&) const;
};

template <typename InputStreamT>
inline InputStreamT& operator>>(InputStreamT& s, Vector3Dd& v)
{
    s >> v.x >> v.y >> v.z;
    return s;
}

template <typename OutputStreamT>
inline OutputStreamT& operator<<(OutputStreamT& s, const Vector3Dd& v)
{
    s <<  v.x << ' ' << v.y << ' ' << v.z << ' ';
    return s;
}

inline Vector3Dd operator+(const Vector3Dd& u, const Vector3Dd& v)
{
    return Vector3Dd(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vector3Dd operator-(const Vector3Dd& v)
{
    return Vector3Dd(-v.x, -v.y, -v.z);
}

inline Vector3Dd operator -(const Vector3Dd& u, const Vector3Dd& v)
{
    return u + -v;
}

inline double operator *(const Vector3Dd& u, const Vector3Dd& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline bool operator ==(const Vector3Dd& u, const Vector3Dd& v)
{
    return (u.x == v.x && u.y == v.y && u.z == v.z);
}

inline bool operator !=(const Vector3Dd& u, const Vector3Dd& v)
{
    return (u.x != v.x || u.y != v.y || u.z != v.z);
}

/* Secondary operations */
inline Vector3Dd operator *(const Vector3Dd& v, const double a)
{
    return Vector3Dd(v.x * a, v.y * a, v.z * a);
}

inline Vector3Dd operator *(const double a, const Vector3Dd& v)
{
    return v * a;
}

inline Vector3Dd operator /(const Vector3Dd& v, const double a)
{
    return v * (1.0 / a);
}

/* Tertiary  operations */
inline Vector3Dd abs(const Vector3Dd& v)
{
    return Vector3Dd(fabs(v.x), fabs(v.y), fabs(v.z));
}

inline Vector3Dd crossd(const Vector3Dd& v1, const Vector3Dd& v2)
{
    return Vector3Dd((v1.y * v2.z - v2.y * v1.z),
                     (v2.x * v1.z - v1.x * v2.z),
                     (v1.x * v2.y - v2.x * v1.y));
}

inline double Vector3Dd::angle(const Vector3Dd& v) const
{
    double d = *this * v;
    double l1 = length();
    double l2 = v.length();
    double angle = acos(d / (l1 * l2));
    return angle;
}

//inline double dotd(const Vector3Dd& v1, const Vector3Dd& v2)
//{
//    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
//}

#endif	/* VECTOR3D_H */