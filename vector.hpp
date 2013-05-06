/*
When using UnitVector() make sure that the length of your vector isn't 0. If this is the case numbers will be divided by zero. The function doesn't check for this.
*/

#ifndef VECTOR_LIB
#define VECTOR_LIB
#include <cmath>
#include <string>
#include <sstream>

namespace de
{
template <typename Type>
class Vector3d
{
    Type coords[3];
    public:

    Vector3d()
    {
    }
    Vector3d (Type tempx, Type tempy, Type tempz)
    {
        coords[0] = tempx;
        coords[1] = tempy;
        coords[2] = tempz;
    }
    Vector3d (Type Coords[3])
    {
        coords[0] = Coords[0];
        coords[1] = Coords[1];
        coords[2] = Coords[2];
    }

    Vector3d (const Vector3d& temp)
    {
        coords[0] = temp.coords[0];
        coords[1] = temp.coords[1];
        coords[2] = temp.coords[2];
    }

    Type* getArray()
    {
        return coords;
    }
    const Type* getArray() const
    {
        return coords;
    }

    Type& operator[](unsigned int iterator)
    {
        return coords[iterator];
    }

    const Type& operator[](unsigned int iterator) const
    {
        return coords[iterator];
    }

    void set (Type tempx, Type tempy, Type tempz)
    {
        coords[0] = tempx;
        coords[1] = tempy;
        coords[2] = tempz;
    }
    void set (Type Coords[3])
    {
        coords[0] = Coords[0];
        coords[1] = Coords[1];
        coords[2] = Coords[2];
    }

    void set (const Vector3d temp)
    {
        coords[0] = temp.coords[0];
        coords[1] = temp.coords[1];
        coords[2] = temp.coords[2];
    }

    Vector3d operator + (const Vector3d temp) const
    {
        Vector3d temp2;
        temp2.coords[0] = coords[0] + temp.coords[0];
        temp2.coords[1] = coords[1] + temp.coords[1];
        temp2.coords[2] = coords[2] + temp.coords[2];
        return temp2;
    }
    Vector3d operator - (const Vector3d temp) const
    {
        Vector3d temp2;
        temp2.coords[0] = coords[0] - temp.coords[0];
        temp2.coords[1] = coords[1] - temp.coords[1];
        temp2.coords[2] = coords[2] - temp.coords[2];
        return temp2;
    }
    Vector3d operator * (const Vector3d temp) const
    {
        Vector3d temp2;
        temp2.coords[0] = coords[0] * temp.coords[0];
        temp2.coords[1] = coords[1] * temp.coords[1];
        temp2.coords[2] = coords[2] * temp.coords[2];
        return temp2;
    }

    Vector3d operator / (const Vector3d temp) const
    {
        Vector3d temp2;
        temp2.coords[0] = coords[0] / temp.coords[0];
        temp2.coords[1] = coords[1] / temp.coords[1];
        temp2.coords[2] = coords[2] / temp.coords[2];
        return temp2;
    }

    const Vector3d& operator = (Vector3d temp)
    {
        coords[0] = temp.coords[0];
        coords[1] = temp.coords[1];
        coords[2] = temp.coords[2];
        return *this;
    }

    Vector3d operator += (const Vector3d temp)
    {
        coords[0] += temp.coords[0];
        coords[1] += temp.coords[1];
        coords[2] += temp.coords[2];
        return *this;
    }
    Vector3d operator -= (const Vector3d temp)
    {
        coords[0] -= temp.coords[0];
        coords[1] -= temp.coords[1];
        coords[2] -= temp.coords[2];
        return *this;
    }
    Vector3d operator *= (const Vector3d temp)
    {
        coords[0] *= temp.coords[0];
        coords[1] *= temp.coords[1];
        coords[2] *= temp.coords[2];
        return *this;
    }
    Vector3d operator /= (const Vector3d temp)
    {
        coords[0] /= temp.coords[0];
        coords[1] /= temp.coords[1];
        coords[2] /= temp.coords[2];
        return *this;
    }

    Vector3d operator * (Type temp) const
    {
        Vector3d temp2;
        temp2.coords[0] = coords[0] * temp;
        temp2.coords[1] = coords[1] * temp;
        temp2.coords[2] = coords[2] * temp;
        return temp2;
    }
    Vector3d operator / (Type temp) const
    {
        Vector3d temp2;
        temp2.coords[0] = coords[0] / temp;
        temp2.coords[1] = coords[1] / temp;
        temp2.coords[2] = coords[2] / temp;
        return temp2;
    }
    Vector3d operator *= (Type temp)
    {
        coords[0] *= temp;
        coords[1] *= temp;
        coords[2] *= temp;
        return *this;
    }
    Vector3d operator /= (Type temp)
    {
        coords[0] /= temp;
        coords[1] /= temp;
        coords[2] /= temp;
        return *this;
    }

    bool operator == (Vector3d temp) const
    {
        return (coords[0] == temp.coords[0] && coords[1] == temp.coords[1] && coords[2] == temp.coords[2]);
    }
    bool operator != (Vector3d temp) const
    {
        return !(coords[0] == temp.coords[0] && coords[1] == temp.coords[1] && coords[2] == temp.coords[2]);
    }
    bool operator < (Vector3d temp) const
    {
        return ((coords[0]*coords[0]+coords[1]*coords[1]+coords[2]*coords[2]+coords[3]*coords[3])<(temp.coords[0]*temp.coords[0]+temp.coords[1]*temp.coords[1]+temp.coords[2]*temp.coords[2]));
    }
    bool operator > (const Vector3d& temp) const
    {
        return ((coords[0]*coords[0]+coords[1]*coords[1]+coords[2]*coords[2]+coords[3]*coords[3])>(temp.coords[0]*temp.coords[0]+temp.coords[1]*temp.coords[1]+temp.coords[2]*temp.coords[2]));
    }
    bool operator <= (const Vector3d& temp) const
    {
        return ((coords[0]*coords[0]+coords[1]*coords[1]+coords[2]*coords[2]+coords[3]*coords[3])<=(temp.coords[0]*temp.coords[0]+temp.coords[1]*temp.coords[1]+temp.coords[2]*temp.coords[2]));
    }
    bool operator >= (const Vector3d& temp) const
    {
        return ((coords[0]*coords[0]+coords[1]*coords[1]+coords[2]*coords[2]+coords[3]*coords[3])>=(temp.coords[0]*temp.coords[0]+temp.coords[1]*temp.coords[1]+temp.coords[2]*temp.coords[2]));
    }
    Vector3d operator - () const
    {
        return Vector3d(-coords[0], -coords[1], -coords[2]);
    }

    Vector3d abs() const
    {
        return Vector3d((coords[0]>0) ? coords[0] : -coords[0], (coords[1]>0) ? coords[1] : -coords[1], (coords[2]>0) ? coords[2] : -coords[2]);
    }

    Type length() const
    {
        return sqrt(coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2]);
    }

    Vector3d unitVector() const
    {
        return *this/length();
    }

    Type squaredLength() const
    {
        return coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2];
    }
    std::string toString() const
    {
        std::ostringstream stream;
        stream << "V(" << coords[0] << ", " << coords[1] << ", " << coords[2] << ")";
        return stream.str();
    }
    Type lowest () const
    {
        return (((coords[0]<coords[1]) ? coords[0] : coords[1])<coords[2]) ? ((coords[0]<coords[1]) ? coords[0] : coords[1]) : coords[2];
    }
    Type highest () const
    {
        return (((coords[0]>coords[1]) ? coords[0] : coords[1])>coords[2]) ? ((coords[0]>coords[1]) ? coords[0] : coords[1]) : coords[2];
    }
    Type sum() const
    {
        return coords[0] + coords[1] + coords[2];
    }
    Type dotProduct(const Vector3d v)
    {
        return operator *(v).sum();
    }
    Vector3d crossProduct(const Vector3d v)
    {
        return Vector3d(coords[1]*v[2] - coords[2]*v[1], coords[2]*v[0] - coords[0]*v[2], coords[0]*v[1] - coords[1]*v[0]);
    }
};
template <typename Type>
std::ostream& operator<< (std::ostream& outStream, const de::Vector3d<Type>& temp )
{
    return outStream << temp.toString();
}

template <typename Type>
class Vector2d
{
    Type coords[2];
    public:

    Vector2d()
    {
    }
    Vector2d(Type tempx, Type tempy)
    {
        coords[0] = tempx;
        coords[1] = tempy;
    }
    Vector2d (const Type Coords[2])
    {
        coords[0] = Coords[0];
        coords[1] = Coords[1];
    }

    Vector2d (const Vector2d& temp)
    {
        coords[0] = temp.coords[0];
        coords[1] = temp.coords[1];
    }

    const Type* getArray() const
    {
        return coords;
    }
    Type* getArray()
    {
        return coords;
    }

    Type& operator[](const unsigned int iterator)
    {
        return coords[iterator];
    }

    const Type& operator[](const unsigned int iterator) const
    {
        return coords[iterator];
    }

    void Set (Type tempx, Type tempy)
    {
        coords[0] = tempx;
        coords[1] = tempy;
    }
    void set (const Type Coords[2])
    {
        coords[0] = Coords[0];
        coords[1] = Coords[1];
    }
    void set (const Vector2d temp)
    {
        coords[0] = temp.coords[0];
        coords[1] = temp.coords[1];
    }

    Vector2d operator + (const Vector2d temp) const
    {
        Vector2d temp2;
        temp2.coords[0] = coords[0] + temp.coords[0];
        temp2.coords[1] = coords[1] + temp.coords[1];
        return temp2;
    }
    Vector2d operator - (const Vector2d temp) const
    {
        Vector2d temp2;
        temp2.coords[0] = coords[0] - temp.coords[0];
        temp2.coords[1] = coords[1] - temp.coords[1];
        return temp2;
    }
    Vector2d operator * (const Vector2d temp) const
    {
        Vector2d temp2;
        temp2.coords[0] = coords[0] * temp.coords[0];
        temp2.coords[1] = coords[1] * temp.coords[1];
        return temp2;
    }
    Vector2d operator / (const Vector2d temp) const
    {
        Vector2d temp2;
        temp2.coords[0] = coords[0] / temp.coords[0];
        temp2.coords[1] = coords[1] / temp.coords[1];
        return temp2;
    }

    const Vector2d& operator = (const Vector2d temp)
    {
        coords[0] = temp.coords[0];
        coords[1] = temp.coords[1];
        return *this;
    }

    const Vector2d& operator += (const Vector2d temp)
    {
        coords[0] += temp.coords[0];
        coords[1] += temp.coords[1];
        return *this;
    }
    const Vector2d& operator -= (const Vector2d temp)
    {
        coords[0] -= temp.coords[0];
        coords[1] -= temp.coords[1];
        return *this;
    }
    const Vector2d& operator *= (const Vector2d temp)
    {
        coords[0] *= temp.coords[0];
        coords[1] *= temp.coords[1];
        return *this;
    }
    const Vector2d& operator /= (const Vector2d temp)
    {
        coords[0] /= temp.coords[0];
        coords[1] /= temp.coords[1];
        return *this;
    }

    Vector2d operator * (const Type temp) const
    {
        Vector2d temp2;
        temp2.coords[0] = coords[0] * temp;
        temp2.coords[1] = coords[1] * temp;
        return temp2;
    }
    Vector2d operator / (const Type temp) const
    {
        Vector2d temp2;
        temp2.coords[0] = coords[0] / temp;
        temp2.coords[1] = coords[1] / temp;
        return temp2;
    }
    const Vector2d& operator *= (const Type temp)
    {
        coords[0] *= temp;
        coords[1] *= temp;
        return *this;
    }
    const Vector2d& operator /= (const Type temp)
    {
        coords[0] /= temp;
        coords[1] /= temp;
        return *this;
    }

    bool operator == (const Vector2d temp) const
    {
        return (coords[0] == temp.coords[0] && coords[1] == temp.coords[1]);
    }
    bool operator != (const Vector2d temp) const
    {
        return !(coords[0] == temp.coords[0] && coords[1] == temp.coords[1]);
    }
    bool operator < (const Vector2d temp) const
    {
        return ((coords[0]*coords[0]+coords[1]*coords[1]+coords[2]*coords[2]+coords[3]*coords[3])<(temp.coords[0]*temp.coords[0]+temp.coords[1]*temp.coords[1]));
    }
    bool operator > (const Vector2d temp) const
    {
        return ((coords[0]*coords[0]+coords[1]*coords[1]+coords[2]*coords[2]+coords[3]*coords[3])>(temp.coords[0]*temp.coords[0]+temp.coords[1]*temp.coords[1]));
    }
    bool operator <= (const Vector2d temp) const
    {
        return ((coords[0]*coords[0]+coords[1]*coords[1]+coords[2]*coords[2]+coords[3]*coords[3])<=(temp.coords[0]*temp.coords[0]+temp.coords[1]*temp.coords[1]));
    }
    bool operator >= (const Vector2d temp) const
    {
        return ((coords[0]*coords[0]+coords[1]*coords[1]+coords[2]*coords[2]+coords[3]*coords[3])>=(temp.coords[0]*temp.coords[0]+temp.coords[1]*temp.coords[1]));
    }
    Vector2d operator - () const
    {
        return Vector2d(-coords[0], -coords[1]);
    }

    Vector2d abs() const
    {
        return Vector2d((coords[0]>0) ? coords[0] : -coords[0], (coords[1]>0) ? coords[1] : -coords[1]);
    }

    Type length() const
    {
        return sqrt(coords[0]*coords[0] + coords[1]*coords[1]);
    }

    Vector2d unitVector () const
    {
        return *this/length();
    }

    Type squareLength() const
    {
        return coords[0]*coords[0] + coords[1]*coords[1];
    }

    std::string toString() const
    {
        std::ostringstream stream;
        stream << "V(" << coords[0] << ", " << coords[1] << ")";
        return stream.str();
    }

    Type lowest () const
    {
        return (coords[0]<coords[1]) ? coords[0] : coords[1];
    }
    Type highest () const
    {
        return (coords[0]>coords[1]) ? coords[0] : coords[1];
    }
    Type sum() const
    {
        return coords[0] + coords[1];
    }
    Type dotProduct(const Vector2d v)
    {
        return operator *(v).sum();
    }
};

template <typename Type>
std::ostream& operator << (std::ostream& outStream, const de::Vector2d<Type>& temp )
{
    return outStream << temp.toString();
}
}
#endif

