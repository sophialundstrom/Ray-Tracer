#include "Box.h"

Box::Box(const Vector3D& color, const Vector3D& center, const Vector3D& dimensions, const Vector3D& rot_values)
    :Shape(color), center(center)
{
    //create Pi-constant
    const double PI = acos(-1);

    //Calculate radians, ordered Z,X,Y because of the compositions order
    double alpha = rot_values.GetZ() * (PI / 180);
    double beta = rot_values.GetX() * (PI / 180);
    double gamma = rot_values.GetY() * (PI / 180);

    //Calculate the rotation-matrix
    this->vectors[0] = Vector3D(cos(alpha) * cos(beta), sin(alpha) * cos(beta), -sin(beta));
    this->vectors[1] = Vector3D(cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma), sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma), cos(beta) * sin(gamma));
    this->vectors[2] = Vector3D(cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma), sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma), cos(beta) * cos(gamma));

    //Calculate the half-lenghts
    this->dimensions[0] = dimensions.GetX() * 0.5;
    this->dimensions[1] = dimensions.GetY() * 0.5;
    this->dimensions[2] = dimensions.GetZ() * 0.5;
}

bool Box::Intersection(const Ray& ray, double& t)
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
    //-------------------------------------------------------------- OBB ADAPTION
    //
    //  We create two parallell planes with the same normal but two different translations
    //  based of origin and the OBB's dimensions.
    //  With that we are given two t values and we later on compare the two to get
    //  the correct value that is the closest t that is within the bounds of the 
    //  dimensions given.
    //-------------------------------------------------------------- CALCULATIONS
    */

    //point p0 in plane
    Vector3D OP = center - origin;

    double t_min = -std::numeric_limits<double>::max();
    double t_max = std::numeric_limits<double>::max();

    double t1, t2;

    for (unsigned int i = 0; i < 3; ++i)
    {
        double e = vectors[i].DotProduct(OP);
        double denominator = vectors[i].DotProduct(direction);

        //if valid denominator value
        if (std::abs(denominator) > 0.0)
        {
            //two different t values of the two planes
            t1 = (e + dimensions[i]) / denominator;
            t2 = (e - dimensions[i]) / denominator;

            //if t1 is less than t2, make t2 -> t1 to compare to t_min later on etc.
            if (t1 > t2)
            {
                double temp = t1;
                t1 = t2;
                t2 = temp;
            }

            if (t1 > t_min)
                t_min = t1;

            if (t2 < t_max)
                t_max = t2;

            if (t_min > t_max)
                return false;
            
            if (t_max < 0.0)
                return false;
        }

        //if ray is parallell to the plane
        else if (-e - dimensions[i] > 0.0 || -e + dimensions[i] < 0.0)
            return false;
    }

    if (t_min > 0.0)
    {
        t = t_min;
        return true;
    }

    return false;
}