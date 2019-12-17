#pragma once
#include<math.h>

class Vector3
{
public:
	float x;
	float y;
	float z;
	static int moveRate;

	Vector3() { if (moveRate == 0) moveRate = 1; x = 0.0; y = 0.0; z = 0.0; }
	Vector3(float a, float b, float c) { if (moveRate == 0) moveRate = 1; x = a; y = b; z = c; }


	Vector3 operator+(Vector3 &t1)
	{
		Vector3 t2;
		t2.x = x + t1.x;
		t2.z = z + t1.z;
		t2.y = y + t1.y;
		return t2;
	}
	Vector3 operator-(Vector3 &t1)
	{
		Vector3 t2;
		t2.x = x - t1.x;
		t2.z = z - t1.z;
		t2.y = y - t1.y;
		return t2;
	}
	void reset(float a, float b, float c) { x = a; y = b; z = c; }
	Vector3 unit()
	{
		Vector3 t2;
		t2.x = moveRate * x / (sqrtf(x*x + z * z));
		t2.z = moveRate * z / (sqrtf(x*x + z * z));
		t2.y = 0;
		return t2;
	}
	Vector3 unit_inv()
	{
		Vector3 t2;
		t2.x = z;
		t2.z = -x;
		t2.y = 0;
		return t2;
	}

	static void setRate(float rate)
	{
		moveRate = rate;
	}

	double getLength()
	{
		return sqrt(x*x + y * y + z * z);
	}

	double getSquareLength()
	{
		return x * x + y * y + z * z;
	}

	double operator*(Vector3 &t1) {
		return (x*t1.x + y * t1.y + z * t1.z);
	}
};
