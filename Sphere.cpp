#include "Sphere.h"

Sphere::Sphere(const Vector3D& color, const Vector3D& c, const double& r)
    :Shape(color), center(c), radius(r)
{
}

bool Sphere::Intersection(const Ray& ray, double& t)
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
    //-------------------------------------------------------------- SPHERE
    //
    //  A point p is a valid point of a sphere if:
    //  
    //  || p - c || = r     =>      || p - c || - r = 0
    //
    //-------------------------------------------------------------- COMBINE
    //
    //  By replacing the point with the rays equations we get the following:
    //
    //  || (o + dt) - c || - r = 0
    //  
    //  Based on the fact that ||u|| = u*u we can use it in our equation:
    //
    //  (o + dt - c)^2 - r^2 = 0
    //
    //  And using the distibutive law we get:
    //
    //  (o + dt - c)(o + dt - c) - r^2 = 0
    //
    //  Mix it up a bit:
    //
    //  (dt + (o - c))(dt + (o - c)) - r^2 = 0
    //
    //  Multiply:
    //
    //  dt*dt + dt*(o - c) + dt*(o - c) + (o - c)^2 - r^2 = 0
    //
    //  We get a quadratic equation on t, which means that it can have two real roots,
    //  where the ray hits the sphere in one or two points, or two imaginary roots where
    //  the ray does not intersect. 
    //
    //  Quadratic equation: ax^2 + bx + c = 0
    //
    //  In our equation:
    //  
    //  d^2 * t^2 + 2d(o - c)t + ((o - c)^2 - r^2) = 0
    //
    //  or
    //
    //  t^2 + 2bt + c = 0
    //
    //  Where d*d = 1 (normalized vector ||d|| = 1)
    //  b = d * (o - c)
    //  c = (o - c)^2 - r^2
    //
    //  Continuing with calculating t:
    //
    //  t =  -b +- sqrt(b^2 - c)
    //
    //  Where we then check the root to see how many valid answers we can get:
    //
    //  If (b^2 - c) > 0 we get two t values, = 0 we get one, and < 0 we get none.    
    //  
    //  If we have one or more continue with calculating the t value.
    //-------------------------------------------------------------- CALCULATIONS
    */

    double b = direction.DotProduct(origin - center);
    double c = pow((origin - center).Magnitude(), 2) - pow(radius, 2);

    double delta_value = pow(b, 2) - c;

    if (delta_value < 0)
        return false;

    else if (delta_value == 0)
    {
        t = -b;

        if (t < 0.0)
            return false;

        return true;
    }

    else
    {
        double t1 = -b + sqrt(pow(b, 2) - c);
        double t2 = -b - sqrt(pow(b, 2) - c);

        if (t1 < t2)
            t = t1;

        else
            t = t2; 
    }

    if (t < 0.0)
        return false;

    return true;
}
