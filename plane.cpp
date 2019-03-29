#include <math.h>
#include "vector3d.cpp"
#include "point3d.cpp"
#include "transform4d.cpp"

namespace GameMath
{
	struct Plane
	{
		float		x, y, z, w;

		Plane() = default;

		Plane(float nx, float ny, float nz, float d)
		{
			x = nx;
			y = ny;
			z = nz;
			w = d;
		}

		Plane(const Vector3D& n, float d)
		{
			x = n.x;
			y = n.y;
			z = n.z;
			w = d;
		}

		const Vector3D& GetNormal(void) const
		{
			return (reinterpret_cast<const Vector3D&>(x));
		}
	};

	float Dot(const Plane& f, const Vector3D& v)
	{
		return (f.x * v.x + f.y * v.y + f.z * v.z);
	}

	float Dot(const Plane& f, const Point3D& p)
	{
		return (f.x * p.x + f.y * p.y + f.z * p.z + f.w);
	}

	// Listing 3.5

	Transform4D MakeReflection(const Plane& f)
	{
		float x = f.x * -2.0F;
		float y = f.y * -2.0F;
		float z = f.z * -2.0F;
		float nxny = x * f.y;
		float nxnz = x * f.z;
		float nynz = y * f.z;

		return (Transform4D(x * f.x + 1.0F, nxny, nxnz, x * f.w,
							nxny, y * f.y + 1.0F, nynz, y * f.w,
							nxnz, nynz, z * f.z + 1.0F, z * f.w));
	}

	// Listing 3.6

	float IntersectLinePlane(const Point3D& p, const Vector3D& v,
							 const Plane& f, Point3D *q)
	{
		float fv = Dot(f, v);
		if (fabs(fv) > FLT_MIN)
		{
			*q = p - v * (Dot(f, p) / fv);
			return (true);
		}

		return (false);
	}

	// Listing 3.7

	bool IntersectThreePlanes(const Plane& f1, const Plane& f2,
							  const Plane& f3, Point3D *p)
	{
		const Vector3D& n1 = f1.GetNormal();
		const Vector3D& n2 = f2.GetNormal();
		const Vector3D& n3 = f3.GetNormal();

		Vector3D n1xn2 = Cross(n1, n2);
		float det = Dot(n1xn2, n3);
		if (fabs(det) > FLT_MIN)
		{
			*p = (Cross(n3, n2) * f1.w + Cross(n1, n3) * f2.w
				  - n1xn2 * f3.w) / det;
			return (true);
		}

		return (false);
	}

	// Listing 3.8

	bool IntersectTwoPlanes(const Plane& f1, const Plane& f2,
							Point3D *p, Vector3D *v)
	{
		const Vector3D& n1 = f1.GetNormal();
		const Vector3D& n2 = f2.GetNormal();

		*v = Cross(n1, n2);
		float det = Dot(*v, *v);
		if (fabs(det) > FLT_MIN)
		{
			*p = (Cross(*v, n2) * f1.w + Cross(n1, *v) * f2.w) / det;
			return (true);
		}

		return (false);
	}

	// Listing 3.9

	Plane operator *(const Plane& f, const Transform4D& H)
	{
		return (Plane(f.x * H(0,0) + f.y * H(1,0) + f.z * H(2,0),
					  f.x * H(0,1) + f.y * H(1,1) + f.z * H(2,1),
					  f.x * H(0,2) + f.y * H(1,2) + f.z * H(2,2),
					  f.x * H(0,3) + f.y * H(1,3) + f.z * H(2,3) + f.w));
	}

}
