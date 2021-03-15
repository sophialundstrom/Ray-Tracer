#include "Plane.h"

Plane::Plane(const Vector3D& color, const Vector3D& normal, const Vector3D& point)
    :Shape(color), normal(normal), point(point)
{
    this->normal.Normalize();
}

bool Plane::Intersection(const Ray& ray, double& t)
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
    //-------------------------------------------------------------- CALCULATIONS
    */

    double dp = normal.DotProduct(point);
    double denominator = normal.DotProduct(direction);

    if (std::abs(denominator) < 0.00001)
        return false;
   
    t = (dp - normal.DotProduct(origin)) / denominator;

    if (t < 0.0)
        return false;

    return true;
}
