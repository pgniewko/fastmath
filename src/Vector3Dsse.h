#ifndef Vector3DSSE_H
#define Vector3DSSE_H

#include <smmintrin.h>

#ifndef _MM_ALIGN16
#ifdef __GNUC__
#define _MM_ALIGN16 __attribute__((aligned (16)))
#endif
#ifdef __MSVC__
#define _MM_ALIGN16 __declspec(align(16))
#endif
#endif

#ifndef malloc_simd
#ifdef WIN32
#define malloc_simd(x) (_aligned_malloc(x, 16))
#endif
#ifdef __linux__
#define  malloc_simd(x) (_mm_malloc(x, 16))
#endif
#ifdef   __MACH__
#define  malloc_simd(x) (malloc(x))
#endif
#endif

#ifndef free_simd
#ifdef WIN32
#define free_simd(x) ( _aligned_free(x) )
#endif
#ifdef __linux__
#define  free_simd(x) (_mm_free(x))
#endif
#ifdef   __MACH__
#define  free_simd(x) ( free(x))
#endif
#endif


#ifdef __GNUC__
class __attribute__((aligned (16))) Vector3Dsse
#else
_MM_ALIGN16 class Vector3Dsse
#endif
{
    public:
        inline Vector3Dsse() : mmvalue(_mm_setzero_ps()) {}
        inline Vector3Dsse(float x, float y, float z) : mmvalue(_mm_set_ps(0, z, y, x)) {}
        inline Vector3Dsse(__m128 m) : mmvalue(m) {}
        virtual ~Vector3Dsse() {}

        inline Vector3Dsse operator+(const Vector3Dsse& b) const
        {
            return _mm_add_ps(mmvalue, b.mmvalue);
        }
        inline Vector3Dsse operator-(const Vector3Dsse& b) const
        {
            return _mm_sub_ps(mmvalue, b.mmvalue);
        }
        inline Vector3Dsse operator*(const Vector3Dsse& b) const
        {
            return _mm_mul_ps(mmvalue, b.mmvalue);
        }
        inline Vector3Dsse operator/(const Vector3Dsse& b) const
        {
            return _mm_div_ps(mmvalue, b.mmvalue);
        }

        inline Vector3Dsse& operator+=(const Vector3Dsse& b)
        {
            mmvalue = _mm_add_ps(mmvalue, b.mmvalue);
            return *this;
        }
        inline Vector3Dsse& operator-=(const Vector3Dsse& b)
        {
            mmvalue = _mm_sub_ps(mmvalue, b.mmvalue);
            return *this;
        }
        inline Vector3Dsse& operator*=(const Vector3Dsse& b)
        {
            mmvalue = _mm_mul_ps(mmvalue, b.mmvalue);
            return *this;
        }
        inline Vector3Dsse& operator/=(const Vector3Dsse& b)
        {
            mmvalue = _mm_div_ps(mmvalue, b.mmvalue);
            return *this;
        }

        inline Vector3Dsse operator+(float b) const
        {
            return _mm_add_ps(mmvalue, _mm_set1_ps(b));
        }
        inline Vector3Dsse operator-(float b) const
        {
            return _mm_sub_ps(mmvalue, _mm_set1_ps(b));
        }
        inline Vector3Dsse operator*(float b) const
        {
            return _mm_mul_ps(mmvalue, _mm_set1_ps(b));
        }
        inline Vector3Dsse operator/(float b) const
        {
            return _mm_div_ps(mmvalue, _mm_set1_ps(b));
        }

        inline Vector3Dsse& operator+=(float b)
        {
            mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(b));
            return *this;
        }
        inline Vector3Dsse& operator-=(float b)
        {
            mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(b));
            return *this;
        }
        inline Vector3Dsse& operator*=(float b)
        {
            mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(b));
            return *this;
        }
        inline Vector3Dsse& operator/=(float b)
        {
            mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(b));
            return *this;
        }

        inline bool operator==(const Vector3Dsse& b) const
        {
            return (((_mm_movemask_ps(_mm_cmpeq_ps(mmvalue, b.mmvalue))) & 0x7) == 0x7);
        }

        inline bool operator!=(const Vector3Dsse& b) const
        {
            return !(*this == b);
        }

        inline Vector3Dsse cross(const Vector3Dsse& b) const
        {
            return _mm_sub_ps(
                       _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
                       _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)))
                   );
        }

        inline float dot(const Vector3Dsse& b) const
        {
            return _mm_cvtss_f32(_mm_dp_ps(mmvalue, b.mmvalue, 0x71));
        }
        inline float length() const
        {
            return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mmvalue, mmvalue, 0x71)));
        }
        // 1/length() of the vector
        inline float rlength() const
        {
            return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_dp_ps(mmvalue, mmvalue, 0x71)));
        }

        // returns the vector scaled to unit length
        inline void normalize()
        {
            mmvalue = normalize_accurate(mmvalue);
        }

        inline Vector3Dsse normalize_fast() const
        {
            return _mm_mul_ps(mmvalue, _mm_rsqrt_ps(_mm_dp_ps(mmvalue, mmvalue, 0x7F)));
        }
        // (x,y,z) / sqrt(x^2 + y^2 + z^2)
        inline __m128 normalize_accurate(__m128& v) const
        {
            return _mm_div_ps(mmvalue, _mm_sqrt_ps(_mm_dp_ps(mmvalue, mmvalue, 0x7F)) );
        }

        // overloaded operators that ensure alignment
        inline void* operator new[](size_t x)
        {
            return malloc_simd(x);
        }
        inline void operator delete[](void* x)
        {
            if (x)
            {
                free_simd(x);
            }
        }

        union
        {
            struct
            {
                float x, y, z;
            };
            __m128 mmvalue;
        };
};

inline Vector3Dsse cross_sse_func(const Vector3Dsse& a, const Vector3Dsse& b)
{
    return _mm_sub_ps(
               _mm_mul_ps(_mm_shuffle_ps(a.mmvalue, a.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
               _mm_mul_ps(_mm_shuffle_ps(a.mmvalue, a.mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)))
           );
}

inline float dot(const Vector3Dsse& a, const Vector3Dsse& b)
{
    return _mm_cvtss_f32(_mm_dp_ps(a.mmvalue, b.mmvalue, 0x71));
}

inline Vector3Dsse operator+(float a, const Vector3Dsse& b)
{
    return b + a;
}
inline Vector3Dsse operator-(float a, const Vector3Dsse& b)
{
    return Vector3Dsse(_mm_set1_ps(a)) - b;
}
inline Vector3Dsse operator*(float a, const Vector3Dsse& b)
{
    return b * a;
}
inline Vector3Dsse operator/(float a, const Vector3Dsse& b)
{
    return Vector3Dsse(_mm_set1_ps(a)) / b;
}

#endif	/* Vector3DSSE_H */
