#pragma once

#include <cmath>

class Vector3D
{
private:
	double x, y, z;

public:
	Vector3D();
	Vector3D(const double& x, const double& y, const double& z);
	Vector3D(const Vector3D& vector);

	Vector3D operator+(const Vector3D& vector);

	Vector3D operator-(const Vector3D& vector);

	Vector3D operator*(const double& value);

	Vector3D operator/(const double& value);

	Vector3D operator=(const Vector3D& vector);

	double DotProduct(const Vector3D& vector);
	Vector3D CrossProduct(const Vector3D& vector);

	double Magnitude();
	double Square();

	Vector3D Normalize();

	double GetX() const;
	double GetY() const;
	double GetZ() const;
};