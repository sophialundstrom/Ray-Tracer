#pragma once

#include "Shape.h"

class Sphere :public Shape
{
private:
	Vector3D center;
	double radius;

public:
	Sphere(const Vector3D& color, const Vector3D& c, const double& r);

	virtual bool Intersection(const Ray& ray, double& t) override;
};