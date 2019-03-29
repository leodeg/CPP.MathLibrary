#ifndef POINT3D_H
#define POINT3D_H

#include <vector3d.h>

namespace GameMath
{
	struct Point3D : Vector3D
	{
		Point3D() = default;

		Point3D(float a, float b, float c) : Vector3D(a, b, c) {}

		Point3D& operator =(const Vector3D& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return (*this);
		}
	};

	inline Point3D operator +(const Point3D& a, const Vector3D& b)
	{
		return (Point3D(a.x + b.x, a.y + b.y, a.z + b.z));
	}

	inline Point3D operator -(const Point3D& a, const Vector3D& b)
	{
		return (Point3D(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	inline Vector3D operator -(const Point3D& a, const Point3D& b)
	{
		return (Vector3D(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	float DistPointLine(const Point3D& q, const Point3D& p, const Vector3D& v)
	{
		Vector3D a = Cross(q - p, v);
		return (sqrt(Dot(a, a) / Dot(v, v)));
	}

	// Listing 3.3

	float DistLineLine(const Point3D& p1, const Vector3D& v1,
					   const Point3D& p2, const Vector3D& v2)
	{
		Vector3D dp = p2 - p1;

		float v12 = Dot(v1, v1);
		float v22 = Dot(v2, v2);
		float v1v2 = Dot(v1, v2);

		float det = v1v2 * v1v2 - v12 * v22;
		if (fabs(det) > FLT_MIN)
		{
			det = 1.0F / det;

			float dpv1 = Dot(dp, v1);
			float dpv2 = Dot(dp, v2);
			float t1 = (v1v2 * dpv2 - v22 * dpv1) * det;
			float t2 = (v12 * dpv2 - v1v2 * dpv1) * det;

			return (Magnitude(dp + v2 * t2 - v1 * t1));
		}

		// The lines are nearly parallel.

		Vector3D a = Cross(dp, v1);
		return (sqrt(Dot(a, a) / v12));
	}
}
#endif
