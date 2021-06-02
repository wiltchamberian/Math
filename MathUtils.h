#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "NumericLimits.h"
#include "MathConstants.h"
#include <cmath>

/**
 * @projectName   SoftRenderer
 * @brief         math auxiliary functions.
 * @author        YangWC
 * @date          2019-04-28
 */
namespace Sun
{
typedef unsigned int uint;

#define PI_ANGLE 180
#define SMALL_NUMBER		(1.e-8f)
#define KINDA_SMALL_NUMBER	(1.e-4f)

	inline bool equal(double a, double b)
	{
		double d = a - b;
		d = d < 0 ? (-d) : d;
		return d < EPSILON_dbl;
	}

	inline double radians(double angle)
	{
		return angle * A_PI / PI_ANGLE;
	}

	inline double angles(double radians)
	{
		return radians * PI_ANGLE / A_PI;
	}

	inline float fabs(float number) {
		return number > 0 ? number : (-number);
	}

	inline float invSqrt(float number) {
		return 1 / ::sqrt(number);
	}

	//逆平方根算法(from quake3)
	inline float quickInvSqrt(float number) {
		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long*)&y;						// evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1);               // what the fuck?
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));   // 1st iteration

		return y;
	}

	inline float sqrt(float x) {
		//return x * invSqrt(x);
		return ::sqrt(x);
	}

	////////////////////////////////////////////////////////////
	//求上界
	template <typename T>
	T upperBound(const T& t) {
		return t;
	}

	template <typename T, typename ... Args>
	T upperBound(const T& t, Args ... args) {
		T c = upperBound(args...);
		return c > t ? c : t;
	}
	//求下界
	template <typename T>
	T lowerBound(const T& t) {
		return t;
	}

	template <typename T, typename ... Args>
	T lowerBound(const T& t, Args ... args) {
		T c = lowerBound(args...);
		return c > t ? c : t;
	}

	//线性插值
	template<typename _Key , typename _Iter>
	typename _Iter::value_type interpolate_linear(_Iter start, _Iter end, const _Key& key) {
		for (_Iter it = start; it != end; ++it) {
			if (key < it->key()) {
				if (it == start) {
					return *it;
				}
				else{
					_Iter pre = it;
					--pre;
					double frac = (key - pre->key()) / (it->key() - pre->key());
					typename _Iter::value_type res;
					res.value() = pre->value() * (1 - frac) + it->value() * frac;
					res.key() = key;
					return res;
				}
			}
			else if (key > it->key()) {

			}
			else {
				return *it;
			}
		}
		if (end!=start) {
			return *(--end);
		}
		return _Iter::value_type();
	}

	inline void mat2qua(float(*m)[3], float* qua)
	{
		float q1 = sqrt(m[0][0] + m[1][1] + m[2][2] + 1) / 2;
		float q2, q3, q4, tr, s;
		if (q1 != 0.0) {
			q2 = (m[2][1] - m[1][2]) / 4 / q1;
			q3 = (m[0][2] - m[2][0]) / 4 / q1;
			q4 = (m[1][0] - m[0][1]) / 4 / q1;
		}
		else {
			tr = m[0][0] + m[1][1] + m[2][2];
			if (tr > 0) {
				s = sqrt(tr + 1.0) * 2;
				q1 = 0.25 * s;
				q2 = (m[2][1] - m[1][2]) / s;
				q3 = (m[0][2] - m[2][0]) / s;
				q4 = (m[1][0] - m[0][1]) / s;
			}
			else if ((m[0][0] > m[1][1]) && (m[0][0] > m[2][2])) {
				s = sqrt(1.0 + m[0][0] - m[1][1] - m[2][2]) * 2;
				q1 = (m[2][1] - m[1][2]) / s;
				q2 = 0.25 * s;
				q3 = (m[0][1] + m[1][0]) / s;
				q4 = (m[0][2] + m[2][0]) / s;
			}
			else if (m[1][1] > m[2][2])
			{
				s = sqrt(1.0 + m[1][1] - m[0][0] - m[2][2]) * 2;
				q1 = (m[0][2] - m[2][0]) / s;
				q2 = (m[0][1] + m[1][0]) / s;
				q3 = 0.25 * s;
				q4 = (m[1][2] + m[2][1]) / s;
			}
			else {
				s = sqrt(1.0 + m[2][2] - m[0][0] - m[1][1]) * 2;
				q1 = (m[1][0] - m[0][1]) / s;
				q2 = (m[0][2] + m[2][0]) / s;
				q3 = (m[1][2] + m[2][1]) / s;
				q4 = 0.25 * s;
			}
		}
		qua[0] = q1;
		qua[1] = q2;
		qua[2] = q3;
		qua[3] = q4;
	}

}

#endif // MATHUTILS_H
