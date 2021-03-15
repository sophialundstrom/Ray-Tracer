#include "Disc.h"

Disc::Disc(const Vector3D& color, const Vector3D& c, const Vector3D& n, const double& r)
	:Shape(color), center(c), normal(n), radius(r)
{
	normal.Normalize();
}

bool Disc::Intersection(const Ray& ray, double& t)
{
	Vector3D origin = ray.origin;
	Vector3D direction = ray.direction;

	//DESC
	/*
	//-------------------------------------------------------------- RAY
	//
	//  A point p in a ray is given by: 
	//  p = o + dt
	//
	//  where o = origin of ray 
	//  d = direction of ray
	//  and p a point given by a specific t value.
	//-------------------------------------------------------------- PLANE
	//
	//  A Ray-plane intersection:
	//  
	//  A point p in the plane is valid if: (p - p0) * n = 0
	//  where p0 is a point in the plane and n the normal vector.
	//  
	//  switch out point p to ray equation ->
	//  ((o + dt) - p0) * n = 0
	//  ->
	//  (o + dt - p0) * n = 0
	//  ->
	//  t = (n*p0 - n*o) / d*n
	//  ->
	//  t = n(p0 - o) / d*n
	// (normal * point) - (normal * origin) / normal * direction = t
	//-------------------------------------------------------------- DISC ADAPTION
	//
	//	To check that the form given will be a disc and not just an infinite plane 
	//	we need to make sure that the point given by t is within the given radius.
	//-------------------------------------------------------------- CALCULATIONS	
	*/

	Vector3D OC = center - origin;

	//Check if ray is parallell to plane
	double denominator = direction.DotProduct(normal);

	if (std::abs(denominator) < 0.0000001f)
		return false;

	//Calculate t
	double normalDotOC = OC.DotProduct(normal);
	t = normalDotOC / denominator;

	//Check if plane is behind ray
	if (t < 0.0)
		return false;
	
	//Calculate if the given point is within the radius
	Vector3D intersectionPoint = origin + direction * t;
	double distanceFromCenter = (intersectionPoint - center).Magnitude();

	return distanceFromCenter <= radius;
}
