#pragma once
#include "Shape.h"
#include <memory>
#include <cmath>

class Box :public Shape
{
private:
	Vector3D center;
	Vector3D vectors[3];

	double dimensions[3];

public:
	Box(const Vector3D& color, const Vector3D& center, const Vector3D& dimensions, const Vector3D& rot_values);

	virtual bool Intersection(const Ray& ray, double& t) override;
};