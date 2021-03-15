#include "Vector3D.h"

Vector3D::Vector3D()
	:x(0.0), y(0.0), z(0.0)
{
}

Vector3D::Vector3D(const double& x, const double& y, const double& z)
	:x(x), y(y), z(z)
{
}

Vector3D::Vector3D(const Vector3D& vector)
{
	this->x = vector.GetX();
	this->y = vector.GetY();
	this->z = vector.GetZ();
}

Vector3D Vector3D::operator+(const Vector3D& vector)
{
	return Vector3D(this->x + vector.GetX(), this->y + vector.GetY(), this->z + vector.GetZ());
}

Vector3D Vector3D::operator-(const Vector3D& vector)
{
	return Vector3D(this->x - vector.GetX(), this->y - vector.GetY(), this->z - vector.GetZ());
}

Vector3D Vector3D::operator*(const double& value)
{
	return Vector3D(this->x * value, this->y * value, this->z * value);
}

Vector3D Vector3D::operator/(const double& value)
{
	Vector3D return_vector;

	if (value != 0.0)
		return_vector = Vector3D(this->x / value, this->y / value, this->z / value);

	return return_vector;
}

Vector3D Vector3D::operator=(const Vector3D& vector)
{
	this->x = vector.GetX();
	this->y = vector.GetY();
	this->z = vector.GetZ();
	return *this;
}

double Vector3D::DotProduct(const Vector3D& vector)
{
	return (this->x * vector.GetX() +this->y * vector.GetY() + this->z * vector.GetZ());
}

Vector3D Vector3D::CrossProduct(const Vector3D& vector)
{
	double new_x = this->y * vector.GetZ() -this->z * vector.GetY();
	double new_y = this->z * vector.GetX() - this->x * vector.GetZ();
	double new_z = this->x * vector.GetY() - this->y * vector.GetX();

	return Vector3D(new_x, new_y, new_z);
}

double Vector3D::Magnitude()
{
	return sqrt(Square());
}

double Vector3D::Square()
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

Vector3D Vector3D::Normalize()
{
	Vector3D return_vector;

	if (Magnitude() != 0)
		return_vector = *this * (1 / Magnitude());

	return return_vector;
}

double Vector3D::GetX() const
{
	return this->x;
}

double Vector3D::GetY() const
{
	return this->y;
}

double Vector3D::GetZ() const
{
	return this->z;
}