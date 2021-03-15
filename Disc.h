#pragma once

#include "Shape.h"

class Disc :public Shape
{
private:
	Vector3D center;
	Vector3D normal;
	double radius;

public:
	Disc(const Vector3D& color, const Vector3D& c, const Vector3D& n, const double& r);

	virtual bool Intersection(const Ray& ray, double& t) override;
};