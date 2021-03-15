#pragma once
#include "Shape.h"

class Plane :public Shape
{
private:
	Vector3D normal;
	Vector3D point;

public:
	Plane(const Vector3D& color, const Vector3D& normal, const Vector3D& point);

	virtual bool Intersection(const Ray& ray, double& t) override;
};