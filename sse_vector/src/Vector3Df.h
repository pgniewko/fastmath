#ifndef VECTOR3DF_H
#define	VECTOR3DF_H

#include <iostream>
#include <fstream>
#include <cmath>

class Vector3Df
{
    public:
        inline Vector3Df() : x(0), y(0), z(0) {}
        inline Vector3Df(float a, float b, float c) : x(a), y(b), z(c) {}
        inline Vector3Df(const Vector3Df& orig) : x(orig.x), y(orig.y), z(orig.z) {}
        inline virtual ~Vector3Df() {}

        inline const Vector3Df& operator +=(const Vector3Df& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        inline const Vector3Df& operator -=(const Vector3Df& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        inline const Vector3Df& operator *=(const double a)
        {
            x *= a;
            y *= a;
            z *= a;
            return *this;
        }

        inline const Vector3Df& operator /=(const double a)
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
            float len = length();
            x /= len;
            y /= len;
            z /= len;
        }

        float x, y, z;

        inline double angle(const Vector3Df&) const;
};

template <typename InputStreamT>
inline InputStreamT& operator>>(InputStreamT& s, Vector3Df& v)
{
    s >> v.x >> v.y >> v.z;
    return s;
}

template <typename OutputStreamT>
inline OutputStreamT& operator<<(OutputStreamT& s, const Vector3Df& v)
{
    s <<  v.x << ' ' << v.y << ' ' << v.z << ' ';
    return s;
}

inline Vector3Df operator+(const Vector3Df& u, const Vector3Df& v)
{
    return Vector3Df(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vector3Df operator-(const Vector3Df& v)
{
    return Vector3Df(-v.x, -v.y, -v.z);
}

inline Vector3Df operator -(const Vector3Df& u, const Vector3Df& v)
{
    return u + -v;
}

inline double operator *(const Vector3Df& u, const Vector3Df& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline bool operator ==(const Vector3Df& u, const Vector3Df& v)
{
    return (u.x == v.x && u.y == v.y && u.z == v.z);
}

inline bool operator !=(const Vector3Df& u, const Vector3Df& v)
{
    return (u.x != v.x || u.y != v.y || u.z != v.z);
}

/* Secondary operations */
inline Vector3Df operator *(const Vector3Df& v, const double a)
{
    return Vector3Df(v.x * a, v.y * a, v.z * a);
}

inline Vector3Df operator *(const double a, const Vector3Df& v)
{
    return v * a;
}

inline Vector3Df operator /(const Vector3Df& v, const double a)
{
    return v * (1.0 / a);
}

/* Tertiary  operations */
inline Vector3Df abs(const Vector3Df& v)
{
    return Vector3Df (fabs(v.x), fabs(v.y), fabs(v.z));
}

inline Vector3Df crossf(const Vector3Df& v1, const Vector3Df& v2)
{
    return Vector3Df((v1.y * v2.z - v2.y * v1.z),
                     (v2.x * v1.z - v1.x * v2.z),
                     (v1.x * v2.y - v2.x * v1.y));
}

inline double Vector3Df::angle(const Vector3Df& v) const
{
    double d = *this * v;
    double l1 = length();
    double l2 = v.length();
    double angle = acos(d / (l1 * l2));
    return angle;
}
//inline float dotf(const Vector3Df& v1, const Vector3Df& v2)
//{
//    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
//}

#endif	/* VECTOR3DF_H */