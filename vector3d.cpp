#include <math.h>
#include "matrix3d.cpp"

namespace GameMath
{
	struct Vector3D
	{
		float		x, y, z;

		Vector3D() = default;

		Vector3D(float a, float b, float c)
		{
			x = a;
			y = b;
			z = c;
		}

		float& operator [](int i)
		{
			return ((&x)[i]);
		}

		const float& operator [](int i) const
		{
			return ((&x)[i]);
		}

		Vector3D& operator *=(float s)
		{
			x *= s;
			y *= s;
			z *= s;
			return (*this);
		}

		Vector3D& operator /=(float s)
		{
			s = 1.0F / s;
			x *= s;
			y *= s;
			z *= s;
			return (*this);
		}

		Vector3D& operator +=(const Vector3D& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return (*this);
		}

		Vector3D& operator -=(const Vector3D& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return (*this);
		}
	};

	inline Vector3D operator *(const Vector3D& v, float s)
	{
		return (Vector3D(v.x * s, v.y * s, v.z * s));
	}

	inline Vector3D operator /(const Vector3D& v, float s)
	{
		s = 1.0F / s;
		return (Vector3D(v.x * s, v.y * s, v.z * s));
	}

	inline Vector3D operator -(const Vector3D& v)
	{
		return (Vector3D(-v.x, -v.y, -v.z));
	}

	inline float Magnitude(const Vector3D& v)
	{
		return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	}

	inline Vector3D Normalize(const Vector3D& v)
	{
		return (v / Magnitude(v));
	}

	inline Vector3D operator +(const Vector3D& a, const Vector3D& b)
	{
		return (Vector3D(a.x + b.x, a.y + b.y, a.z + b.z));
	}

	inline Vector3D operator -(const Vector3D& a, const Vector3D& b)
	{
		return (Vector3D(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	Vector3D operator *(const Matrix3D& M, const Vector3D& v)
	{
		return (Vector3D(M(0,0) * v.x + M(0,1) * v.y + M(0,2) * v.z,
						 M(1,0) * v.x + M(1,1) * v.y + M(1,2) * v.z,
						 M(2,0) * v.x + M(2,1) * v.y + M(2,2) * v.z));
	}

	Vector3D operator *(const Vector3D& n, const Transform4D& H)
	{
		return (Vector3D(n.x * H(0,0) + n.y * H(1,0) + n.z * H(2,0),
						 n.x * H(0,1) + n.y * H(1,1) + n.z * H(2,1),
						 n.x * H(0,2) + n.y * H(1,2) + n.z * H(2,2)));
	}

	inline float Dot(const Vector3D& a, const Vector3D& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	inline Vector3D Cross(const Vector3D& a, const Vector3D& b)
	{
		return (Vector3D(a.y * b.z - a.z * b.y,
						 a.z * b.x - a.x * b.z,
						 a.x * b.y - a.y * b.x));
	}

	inline Vector3D Project(const Vector3D& a, const Vector3D& b)
	{
		return (b * (Dot(a, b) / Dot(b, b)));
	}

	inline Vector3D Reject(const Vector3D& a, const Vector3D& b)
	{
		return (a - b * (Dot(a, b) / Dot(b, b)));
	}

}
