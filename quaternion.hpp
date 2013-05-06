#ifndef QUATERNION_LIB
#define QUATERNION_LIB
#include <iostream>
#include <sstream>
#include <cmath>
#include "vector.hpp"
#include "matrix.hpp"

namespace de
{
template <typename Type>
class Quaternion
{
    Type data[4];
    public:
    inline Type& operator [] (const unsigned int i)
    {
        return data[i];
    }
    inline const Type& operator [] (const unsigned int i) const
    {
        return data[i];
    }

    //constructors use C++0x unified initialization magic
    Quaternion() {}
    Quaternion(Type r, Type i, Type j, Type k): data({r, i, j, k}) {}
    Quaternion(const Quaternion<Type>& that): data({that[0], that[1], that[2], that[3]}) {}

    Quaternion operator * (const Quaternion that) const
    {
        return Quaternion(data[0]*that[0] - data[1]*that[1] - data[2]*that[2] - data[3]*that[3],
                          data[0]*that[1] + data[1]*that[0] + data[2]*that[3] - data[3]*that[2],
                          data[0]*that[2] - data[1]*that[3] + data[2]*that[0] + data[3]*that[1],
                          data[0]*that[3] + data[1]*that[2] - data[2]*that[1] + data[3]*that[0]);
    }
    Quaternion operator * (const Type s) const
    {
        return Quaternion(data[0]*s, data[1]*s, data[2]*s, data[3]*s);
    }
    Quaternion operator / (const Type s) const
    {
        return Quaternion(data[0]/s, data[1]/s, data[2]/s, data[3]/s);
    }
    Quaternion operator + (const Quaternion that) const
    {
        return Quaternion(data[0] + that[0], data[1] + that[1], data[2] + that[2], data[3] + that[3]);
    }
    inline Quaternion conj() const
    {
        return Quaternion(data[0], -data[1], -data[2], -data[3]);
    }
    inline Type squaredLength() const
    {
        return data[0]*data[0] + data[1]*data[1] + data[2]*data[2] + data[3]*data[3];
    }
    float length() const
    {
        return sqrt(squaredLength());
    }
    Quaternion<Type> normalize() const
    {
        return (*this)/this->length();
    }
    //TODO: can probably be optimized
    Vector3d<Type> transform(const Vector3d<Type> v) const
    {
        Quaternion q = operator * (Quaternion(0,v[0],v[1],v[2])) * conj();
        return Vector3d<Type>(q[1],q[2],q[3]);
    }
    Type dotProduct(const Quaternion<float>& that)
    {
        return data[0]*that[0] + data[1]*that[1] + data[2]*that[2] + data[3]*that[3];
    }
    Quaternion<float> nlerp(const Quaternion<float>& that, const float t) const
    {
        return ((*this)*(1-t) + that*t).normalize();
    }
    Quaternion<float> slerp(const Quaternion<float>& that, const float t) const
    {
        const float cosAngle = data[0]*that[0] + data[1]*that[1] + data[2]*that[2] + data[3]*that[3];
        //when consHalfAngle is (close to) 1, acos(1) will be 0, which will result in division by zero
        //so instead use linear interpolation
        if(cosAngle > 0.999995)
        {
            return nlerp(that, t);
        }

        const float theta = acos(cosAngle);

        return ((*this)*sin((1-t)*theta) + that*sin(t*theta))/sin(theta);
    }
    static Quaternion<float> axisAngle (Vector3d<float> axis, float angle)
    {
        const float s = sin(angle/2), c = cos(angle/2);
        return Quaternion<float>(c, s*axis[0], s*axis[1], s*axis[2]);
    }
    static Quaternion<double> axisAngle (Vector3d<double> axis, double angle)
    {
        const double s = sin(angle/2), c = cos(angle/2);
        return Quaternion<double>(c, s*axis[0], s*axis[1], s*axis[2]);
    }
    //TODO: can probably be optimized
    static Quaternion eulerAngles (Type x, Type y, Type z)
    {
        return axisAngle(Vector3d<Type>(0.0,0.0,1.0), z) *
               axisAngle(Vector3d<Type>(0.0,1.0,0.0), y) *
               axisAngle(Vector3d<Type>(1.0,0.0,0.0), x);
    }
    static Quaternion eulerAngles (Type angles[3])
    {
        return eulerAngles(angles[0], angles[1], angles[2]);
    }
    static Quaternion invEulerAngles (Type x, Type y, Type z)
    {
        return axisAngle(Vector3d<Type>(-1.0,0.0,0.0), x) *
               axisAngle(Vector3d<Type>(0.0,-1.0,0.0), y) *
               axisAngle(Vector3d<Type>(0.0,0.0,-1.0), z);
    }
    static Quaternion invEulerAngles (Type angles[3])
    {
        return invEulerAngles(angles[0], angles[1], angles[2]);
    }
    //TODO: can be optimized for unit quaternions (www.cprogramming.com/tutorial/3d/quaternions.html)
    Matrix4d<Type> toMatrix() const
    {
        return Matrix4d<Type>(data[0]*data[0] + data[1]*data[1] - data[2]*data[2] - data[3]*data[3], 2*data[1]*data[2] - 2*data[0]*data[3], 2*data[1]*data[3] + 2*data[0]*data[2], 0,
                              2*data[1]*data[2] + 2*data[0]*data[3], data[0]*data[0] - data[1]*data[1] + data[2]*data[2] - data[3]*data[3], 2*data[2]*data[3] + 2*data[0]*data[1], 0,
                              2*data[1]*data[3] - 2*data[0]*data[2], 2*data[2]*data[3] - 2*data[0]*data[1], data[0]*data[0] - data[1]*data[1] - data[2]*data[2] + data[3]*data[3], 0,
                              0, 0, 0, 1);
    }
    std::string toString() const
    {
        std::ostringstream stream;
        stream << "Q(" << data[0] << " + " << data[1] << "i + " << data[2] << "j + " << data[3] << "k)";
        return stream.str();
    }
};
}
template <typename Type>
std::ostream& operator << (std::ostream& outStream, const de::Quaternion<Type>& temp )
{
    return outStream << temp.toString();
}
#endif
