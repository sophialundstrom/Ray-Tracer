#include "Triangle.h"

Triangle::Triangle(const Vector3D& color, const Vector3D& p0, const Vector3D& p1, const Vector3D& p2)
    :Shape(color), p0(p0), p1(p1), p2(p2)
{
}

bool Triangle::Intersection(const Ray& ray, double& t)
{
    Vector3D direction = ray.direction;
    Vector3D origin = ray.origin;

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
    //-------------------------------------------------------------- TRIANGLE
    //
    //  A point (u,v) = (1 - u - v)p0 + up1 + vp2
    //  (with w calculated from of it)
    //  is a valid point in the triangle with the given points p0, p1, p2
    //  if the following criterias are followed:
    //
    //  u + v + w = 1
    //
    //  u >= 0, v >= 0, w >= 0
    //
    //  Where then u,v,w works as "sliders" for points within the triangle.
    //  How much of each exists in one point, ex. u = 0.2, v = 0.5, w = 0.3
    //  where the sum must be 1. Like a limited coordinate system.
    //
    //-------------------------------------------------------------- COMBINATION
    //
    //  Replacing the point with ray equation.
    //
    //  o + dt = (1 - u - v)p0 + up1 + vp2
    //  ->
    //  o + dt = p0 - up0 - vp0 + up1 + vp1
    //  ->
    //  o - p0 = -td + u(p1 - p0) + v(p2 - p0)
    //  ->
    //  (-d, p1 - p0, p2 - p0) * (t, u, v) = o - p0
    //  
    //  Resulting in a matrix * vector calculation
    //  -> 
    //  A * x = y
    //  ->
    //  x = A^(-1) * y 
    //  
    //  Instead of using determinants to calculate the inverse we simply use
    //  crossproducts. We get the following equation:
    //
    //  (t, u, v) = 1 / (d x (p2 - p0)) * (p1 -p0)) * { 
    //                                                  ((o - p0) x (p1 - p0) * (p2 - p0))),  
    //                                                  (d x (p2 - p0) * (o - p0)) 
    //                                                  ((o - p0) x (p1 - p0) * d) 
    //                                                }
    //
    //  By then calculating u & v and using the criterias we can confirm if t
    //  provides a valid solution.
    //-------------------------------------------------------------- CALCULATIONS
    */

    //Make vectors out of given points
    Vector3D e1 = p1 - p0;
    Vector3D e2 = p2 - p0;

    // (d x (p2 - p0))
    Vector3D a = direction.CrossProduct(e2);

    // (d x (p2 - p0)) * (p1 - p0)
    double denominator = e1.DotProduct(a);

    //if valid denominator value
    if (std::abs(denominator) < 0.000001)
        return false;

    double f = 1 / denominator;

    Vector3D s = origin - p0;

    // (o - p0) x (p1 - p0)
    Vector3D r = s.CrossProduct(e1);

    //Equation looks like:
    // (t, u, v) = f * {
    //                  (r * e2),
    //                  (a * s),
    //                  (r * direction)
    //                 }

    //calculate u
    // f * ((o - p0) * (d x (p2 - p0))
    double u = f * (s.DotProduct(a));

    //calculate v
    // f * (d * ((o - p0) x (p1 - p0)))
    double v = f * (direction.DotProduct(r));

    //Check criterias
    if (u < 0.0)
        return false;

    if (v < 0.0 || u + v > 1)
        return false;

    t = f * e2.DotProduct(r);

    if (t < 0.0)
        return false;

    return true;
}