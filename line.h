#ifndef LINE_H
#define LINE_H

#include <math.h>
#include "vector3d.h"
#include "transform4d.h"
#include "plane.h"

namespace GameMath
{
	struct Line
	{
		Vector3D	direction;
		Vector3D	moment;

		Line() = default;

		Line(float vx, float vy, float vz, float mx, float my, float mz) :
			direction(vx, vy, vz), moment(mx, my, mz)
		{
		}

		Line(const Vector3D& v, const Vector3D& m)
		{
			direction = v;
			moment = m;
		}
	};

	// Listing 3.11

	Line Transform(const Line& line, const Transform4D& H)
	{
		Matrix3D adj(Cross(H[1], H[2]), Cross(H[2], H[0]), Cross(H[0], H[1]));
		const Point3D& t = H.GetTranslation();

		Vector3D v = H * line.direction;
		Vector3D m = adj * line.moment + Cross(t, v);
		return (Line(v, m));
	}

	// Listing 4.1

	inline Line operator ^(const Point3D& p, const Point3D& q)
	{
		return (Line(q.x - p.x, q.y - p.y, q.z - p.z,
					 p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, p.x * q.y - p.y * q.x));
	}

	inline Line operator ^(const Plane& f, const Plane& g)
	{
		return (Line(f.y * g.z - f.z * g.y,
					 f.z * g.x - f.x * g.z,
					 f.x * g.y - f.y * g.x,
					 g.x * f.w - f.x * g.w,
					 g.y * f.w - f.y * g.w,
					 g.z * f.w - f.z * g.w));
	}

	inline Plane operator ^(const Line& L, const Point3D& p)
	{
		return (Plane(L.direction.y * p.z - L.direction.z * p.y + L.moment.x,
					  L.direction.z * p.x - L.direction.x * p.z + L.moment.y,
					  L.direction.x * p.y - L.direction.y * p.x + L.moment.z,
					  -L.moment.x * p.x - L.moment.y * p.y - L.moment.z * p.z));
	}

	inline Plane operator ^(const Point3D& p, const Line& L)
	{
		return (L ^ p);
	}

	inline Vector4D operator ^(const Line& L, const Plane& f)
	{
		return (Vector4D(
					L.moment.y * f.z - L.moment.z * f.y + L.direction.x * f.w,
					L.moment.z * f.x - L.moment.x * f.z + L.direction.y * f.w,
					L.moment.x * f.y - L.moment.y * f.x + L.direction.z * f.w,
					-L.direction.x * f.x - L.direction.y * f.y - L.direction.z * f.z));
	}

	inline Vector4D operator ^(const Plane& f, const Line& L)
	{
		return (L ^ f);
	}

	inline float operator ^(const Line& L1, const Line& L2)
	{
		return (-(Dot(L1.direction, L2.moment) + Dot(L2.direction, L1.moment)));
	}

	inline float operator ^(const Point3D& p, const Plane& f)
	{
		return (p.x * f.x + p.y * f.y + p.z * f.z + f.w);
	}

	inline float operator ^(const Plane& f, const Point3D& p)
	{
		return (-(p ^ f));
	}
}

#endif
