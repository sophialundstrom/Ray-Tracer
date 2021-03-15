#include "Shape.h"

Shape::Shape(const Vector3D& color)
	:color(color)
{
}

const Vector3D& Shape::GetColor()
{
	return this->color;
}
