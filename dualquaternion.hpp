#ifndef DUALQUATERNION_LIB
#define DUALQUATERNION_LIB
#include <iostream>
#include <sstream>
#include <math.h>
#include "vector.hpp"
#include "matrix.hpp"
#include "quaternion.hpp"

namespace de
{
template <typename Type>
class DualQuaternion
{
    Type data[8];
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
    DualQuaternion() {}
    DualQuaternion(Type r, Type i, Type j, Type k, Type er, Type ei, Type ej, Type ek) : data({r, i, j, k, er, ei, ej, ek}) {}
    DualQuaternion(const DualQuaternion<Type>& that) : data({that[0], that[1], that[2], that[3], that[4], that[5], that[6], that[7]}) {}
    DualQuaternion(const Quaternion<Type>& rot) : data({rot[0], rot[1], rot[2], rot[3], 0, 0, 0, 0}) {}
    DualQuaternion(const Vector3d<Type>& pos) : data({1,0,0,0,0,pos[0]/2, pos[1]/2, pos[2]/2}) {}

    void place(Vector3d<Type> pos)
    {
        pos /=2;
        data[4] = -pos[0]*data[1] - pos[1]*data[2] - pos[2]*data[3];
        data[5] =  pos[0]*data[0] + pos[1]*data[3] - pos[2]*data[2];
        data[6] = -pos[0]*data[3] + pos[1]*data[0] + pos[2]*data[1];
        data[7] =  pos[0]*data[2] - pos[1]*data[1] + pos[2]*data[0];
    }
    //makes a DualQuaternion which first rotates and then translates
    //optimized version of: (*this) = DualQuaternion(pos) * DualQuaternion(rot);
    DualQuaternion(const Quaternion<Type>& rot, Vector3d<Type> pos)
    {
        data[0] = rot[0];
        data[1] = rot[1];
        data[2] = rot[2];
        data[3] = rot[3];
        place(pos);
    }

    DualQuaternion operator * (const DualQuaternion that) const
    {
        return DualQuaternion(data[0]*that[0] - data[1]*that[1] - data[2]*that[2] - data[3]*that[3],
                              data[0]*that[1] + data[1]*that[0] + data[2]*that[3] - data[3]*that[2],
                              data[0]*that[2] - data[1]*that[3] + data[2]*that[0] + data[3]*that[1],
                              data[0]*that[3] + data[1]*that[2] - data[2]*that[1] + data[3]*that[0],

                              data[0]*that[4] - data[1]*that[5] - data[2]*that[6] - data[3]*that[7] + data[4]*that[0] - data[5]*that[1] - data[6]*that[2] - data[7]*that[3],
                              data[0]*that[5] + data[1]*that[4] + data[2]*that[7] - data[3]*that[6] + data[4]*that[1] + data[5]*that[0] + data[6]*that[3] - data[7]*that[2],
                              data[0]*that[6] - data[1]*that[7] + data[2]*that[4] + data[3]*that[5] + data[4]*that[2] - data[5]*that[3] + data[6]*that[0] + data[7]*that[1],
                              data[0]*that[7] + data[1]*that[6] - data[2]*that[5] + data[3]*that[4] + data[4]*that[3] + data[5]*that[2] - data[6]*that[1] + data[7]*that[0]);
    }
    DualQuaternion operator * (const Type s) const
    {
        return DualQuaternion(data[0]*s, data[1]*s, data[2]*s, data[3]*s, data[4]*s, data[5]*s, data[6]*s, data[7]*s);
    }
    DualQuaternion operator + (const DualQuaternion that) const
    {
        return DualQuaternion(data[0]+that[0], data[1]+that[1], data[2]+that[2], data[3]+that[3], data[4]+that[4], data[5]+that[5], data[6]+that[6], data[7]+that[7]);
    }
    void operator += (const DualQuaternion that)
    {
        data[0]+=that[0];
        data[1]+=that[1];
        data[2]+=that[2];
        data[3]+=that[3];
        data[4]+=that[4];
        data[5]+=that[5];
        data[6]+=that[6];
        data[7]+=that[7];
    }
    DualQuaternion operator - ()
    {
        return DualQuaternion(-data[0], -data[1], -data[2], -data[3], -data[4], -data[5], -data[6], -data[7]);
    }
    DualQuaternion dualConj () const
    {
        return DualQuaternion(data[0],  data[1],  data[2],  data[3], -data[4], -data[5], -data[6], -data[7]);
    }
    DualQuaternion quatConj () const
    {
        return DualQuaternion(data[0], -data[1], -data[2], -data[3],  data[4], -data[5], -data[6], -data[7]);
    }
    DualQuaternion bothConj () const
    {
        //optimized version of: return this->dualQuat().conjQuat();
        return DualQuaternion(data[0], -data[1], -data[2], -data[3], -data[4],  data[5],  data[6],  data[7]);
    }
    //TODO: can probably be further optimized
    Vector3d<Type> getMovement() const
    {
        DualQuaternion<Type> temp = *this * this->bothConj();           //DualQuaternion(vector(0,0,0)) = 1
        return Vector3d<Type>(temp[5], temp[6], temp[7]);
    }
    Quaternion<Type> getRotation() const
    {
        return Quaternion<Type>(data[0], data[1], data[2], data[3]);
    }
    //TODO: can be optimized
    Vector3d<Type> transform(Vector3d<Type> v) const
    {
        DualQuaternion<Type> temp = *this * DualQuaternion(1,0,0,0,0,v[0],v[1],v[2]) * this->bothConj();
        return Vector3d<Type>(temp[5], temp[6], temp[7]);
    }
    Vector3d<Type> rotate(Vector3d<Type> v) const
    {
        return getRotation().transform(v);
    }
    std::string toString() const
    {
        std::ostringstream stream;
        stream << "DQ(" << data[0] << " + " << data[1] << "i  + " << data[2] << "j + " << data[3] << "k + " << data[4] << "e + " << data[5] << "ei + " << data[6] << "ej + " << data[7] << "ek)";
        return stream.str();
    }
};
}
template <typename Type>
std::ostream& operator << (std::ostream& outStream, const de::DualQuaternion<Type>& temp )
{
    return outStream << temp.toString();
}
#endif
