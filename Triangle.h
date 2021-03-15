#pragma once
#include "Shape.h"

class Triangle :public Shape
{
private:
	Vector3D p0, p1, p2;
public:
	Triangle(const Vector3D& color, const Vector3D& p0, const Vector3D& p1, const Vector3D& p2);

	virtual bool Intersection(const Ray& ray, double& t) override;
};