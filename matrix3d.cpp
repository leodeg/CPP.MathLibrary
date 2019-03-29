#include <math.h>
#include "vector3d.cpp"

namespace GameMath
{
	struct Matrix3D
	{
	private:

		float n[3][3];

	public:

		Matrix3D() = default;

		Matrix3D(float n00, float n01, float n02,
				 float n10, float n11, float n12,
				 float n20, float n21, float n22)
		{
			n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
			n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
			n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
		}

		Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c)
		{
			n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
			n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
			n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
		}

		float& operator ()(int i, int j)
		{
			return (n[j][i]);
		}

		const float& operator ()(int i, int j) const
		{
			return (n[j][i]);
		}

		Vector3D& operator [](int j)
		{
			return (*reinterpret_cast<Vector3D *>(n[j]));
		}

		const Vector3D& operator [](int j) const
		{
			return (*reinterpret_cast<const Vector3D *>(n[j]));
		}
	};

	float Determinant(const Matrix3D& M)
	{
		return (M(0,0) * (M(1,1) * M(2,2) - M(1,2) * M(2,1))
				+ M(0,1) * (M(1,2) * M(2,0) - M(1,0) * M(2,2))
				+ M(0,2) * (M(1,0) * M(2,1) - M(1,1) * M(2,0)));
	}

	// Listing 1.10

	Matrix3D Inverse(const Matrix3D& M)
	{
		const Vector3D& a = M[0];
		const Vector3D& b = M[1];
		const Vector3D& c = M[2];

		Vector3D r0 = Cross(b, c);
		Vector3D r1 = Cross(c, a);
		Vector3D r2 = Cross(a, b);

		float invDet = 1.0F / Dot(r2, c);

		return (Matrix3D(r0.x * invDet, r0.y * invDet, r0.z * invDet,
						 r1.x * invDet, r1.y * invDet, r1.z * invDet,
						 r2.x * invDet, r2.y * invDet, r2.z * invDet));
	}

	// Listing 2.1

	Matrix3D MakeRotationX(float t)
	{
		float c = cos(t);
		float s = sin(t);

		return (Matrix3D(1.0F, 0.0F, 0.0F,
						 0.0F,  c,   -s,
						 0.0F,  s,    c  ));
	}

	Matrix3D MakeRotationY(float t)
	{
		float c = cos(t);
		float s = sin(t);

		return (Matrix3D( c,   0.0F,  s,
						  0.0F, 1.0F, 0.0F,
						  -s,   0.0F,  c  ));
	}

	Matrix3D MakeRotationZ(float t)
	{
		float c = cos(t);
		float s = sin(t);

		return (Matrix3D( c,   -s,   0.0F,
						  s,    c,   0.0F,
						  0.0F, 0.0F, 1.0F));
	}

	// Listing 2.2

	Matrix3D MakeRotation(float t, const Vector3D& a)
	{
		float c = cos(t);
		float s = sin(t);
		float d = 1.0F - c;

		float x = a.x * d;
		float y = a.y * d;
		float z = a.z * d;
		float axay = x * a.y;
		float axaz = x * a.z;
		float ayaz = y * a.z;

		return (Matrix3D(c + x * a.x, axay - s * a.z, axaz + s * a.y,
						 axay + s * a.z, c + y * a.y, ayaz - s * a.x,
						 axaz - s * a.y, ayaz + s * a.x, c + z * a.z));
	}

	// Listing 2.3

	Matrix3D MakeReflection(const Vector3D& a)
	{
		float x = a.x * -2.0F;
		float y = a.y * -2.0F;
		float z = a.z * -2.0F;
		float axay = x * a.y;
		float axaz = x * a.z;
		float ayaz = y * a.z;

		return (Matrix3D(x * a.x + 1.0F, axay, axaz,
						 axay, y * a.y + 1.0F, ayaz,
						 axaz, ayaz, z * a.z + 1.0F));
	}

	// Listing 2.4

	Matrix3D MakeInvolution(const Vector3D& a)
	{
		float x = a.x * 2.0F;
		float y = a.y * 2.0F;
		float z = a.z * 2.0F;
		float axay = x * a.y;
		float axaz = x * a.z;
		float ayaz = y * a.z;

		return (Matrix3D(x * a.x - 1.0F, axay, axaz,
						 axay, y * a.y - 1.0F, ayaz,
						 axaz, ayaz, z * a.z - 1.0F));
	}

	// Listing 2.5

	Matrix3D MakeScale(float sx, float sy, float sz)
	{
		return (Matrix3D(sx, 0.0F, 0.0F, 0.0F, sy, 0.0F, 0.0F, 0.0F, sz));
	}

	// Listing 2.6

	Matrix3D MakeScale(float s, const Vector3D& a)
	{
		s -= 1.0F;
		float x = a.x * s;
		float y = a.y * s;
		float z = a.z * s;
		float axay = x * a.y;
		float axaz = x * a.z;
		float ayaz = y * a.z;

		return (Matrix3D(x * a.x + 1.0F, axay, axaz,
						 axay, y * a.y + 1.0F, ayaz,
						 axaz, ayaz, z * a.z + 1.0F));
	}

	// Listing 2.7

	Matrix3D MakeSkew(float t, const Vector3D& a, const Vector3D& b)
	{
		t = tan(t);
		float x = a.x * t;
		float y = a.y * t;
		float z = a.z * t;

		return (Matrix3D(x * b.x + 1.0F, x * b.y, x * b.z,
						 y * b.x, y * b.y + 1.0F, y * b.z,
						 z * b.x, z * b.y, z * b.z + 1.0F));
	}
}
