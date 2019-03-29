#include <math.h>

namespace GameMath
{
	struct Vector4D
	{
		float		x, y, z, w;

		Vector4D() = default;

		Vector4D(float a, float b, float c, float d)
		{
			x = a;
			y = b;
			z = c;
			w = d;
		}

		float& operator [](int i)
		{
			return ((&x)[i]);
		}

		const float& operator [](int i) const
		{
			return ((&x)[i]);
		}

		Vector4D& operator *=(float s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return (*this);
		}

		Vector4D& operator /=(float s)
		{
			s = 1.0F / s;
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return (*this);
		}

		Vector4D& operator +=(const Vector4D& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return (*this);
		}

		Vector4D& operator -=(const Vector4D& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return (*this);
		}
	};
}
