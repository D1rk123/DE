#ifndef LIB_MATRIX
#define LIB_MATRIX
#include <iostream>
#include <string>
#include <cmath>
#include "vector.hpp"
#include "basiclib.hpp"

namespace de
{
template <typename Type>
class Matrix4d
{
    Type data[16];

    public:
    Type* getArray()
    {
        return data;
    }
    const Type* getArray() const
    {
        return data;
    }

    Matrix4d()
    {
    }
    void clear ()
    {
        data[0] = 1; data[4] = 0; data[8] = 0; data[12] = 0;
        data[1] = 0; data[5] = 1; data[9] = 0; data[13] = 0;
        data[2] = 0; data[6] = 0; data[10] = 1; data[14] = 0;
        data[3] = 0; data[7] = 0; data[11] = 0; data[15] = 1;
    }

    void set (Type temp[16])
    {
        for (int Loop=0; Loop<16; ++Loop)
        {
            data[Loop] = temp[Loop];
        }
    }
    Matrix4d(Type temp[16])
    {
        Set(temp);
    }

    void set (Type xx, Type yx, Type zx, Type wx, Type xy, Type yy, Type zy, Type wy, Type xz, Type yz, Type zz, Type wz, Type xw, Type yw, Type zw, Type ww)
    {
        data[0] = xx; data[4] = yx; data[8] = zx; data[12] = wx;
        data[1] = xy; data[5] = yy; data[9] = zy; data[13] = wy;
        data[2] = xz; data[6] = yz; data[10] = zz; data[14] = wz;
        data[3] = xw; data[7] = yw; data[11] = zw; data[15] = ww;
    }
    Matrix4d (Type xx, Type yx, Type zx, Type wx, Type xy, Type yy, Type zy, Type wy, Type xz, Type yz, Type zz, Type wz, Type xw, Type yw, Type zw, Type ww)
    {
        data[0] = xx; data[4] = yx; data[8] = zx; data[12] = wx;
        data[1] = xy; data[5] = yy; data[9] = zy; data[13] = wy;
        data[2] = xz; data[6] = yz; data[10] = zz; data[14] = wz;
        data[3] = xw; data[7] = yw; data[11] = zw; data[15] = ww;
    }
    Type& operator () (unsigned int row, unsigned int col)
    {
        return data[col*4+row];
    }
    const Type& operator () (unsigned int row, unsigned int col) const
    {
        return data[col*4+row];
    }

    Type& operator [] (unsigned int i)
    {
        return data[i];
    }
    const Type& operator [] (unsigned int i) const
    {
        return data[i];
    }

    const Matrix4d& operator = (const Matrix4d& temp)
    {
        data[0] = temp.data[0];  data[4] = temp.data[4];  data[8] = temp.data[8];    data[12] = temp.data[12];
        data[1] = temp.data[1];  data[5] = temp.data[5];  data[9] = temp.data[9];    data[13] = temp.data[13];
        data[2] = temp.data[2];  data[6] = temp.data[6];  data[10] = temp.data[10];  data[14] = temp.data[14];
        data[3] = temp.data[3];  data[7] = temp.data[7];  data[11] = temp.data[11];  data[15] = temp.data[15];

        return *this;
    }

    Matrix4d operator * (const Matrix4d& temp) const
    {
        Matrix4d temp2;
        for (int col=0; col<4; ++col)
        {
            for (int row=0; row<4; ++row)
            {
                temp2.data[row + 4*col] = data[row] * temp.data[4*col] + data[row + 4] * temp.data[1 + 4*col] + data[row + 8] * temp.data[2 + 4*col] + data[row + 12] * temp.data[3 + 4*col];
            }
        }
        return temp2;
    }

    const Matrix4d& operator *= (const Matrix4d& temp)
    {
        *this = operator *(temp);
        return *this;
    }

    std::string toHtml() const
    {
        std::ostringstream stream;
        stream << "<table><tr><td rowspan =\"4\" style =\"font-size: 95px; padding:0px; font-family:Calibri;\">[</td><td>"
                           << data[0] << "</td><td>" << data[4] << "</td><td>" << data[8]  <<  "</td><td>" << data[12] << "</td><td rowspan =\"4\" style =\"  font-size: 95px; padding:0px; font-family:Calibri;\">]</td></tr>"
             << "<tr><td>" << data[1] << "</td><td>" << data[5] << "</td><td>" << data[9]  <<  "</td><td>" << data[13] << "</td></tr>"
             << "<tr><td>" << data[2] << "</td><td>" << data[6] << "</td><td>" << data[10] <<  "</td><td>" << data[14] << "</td></tr>"
             << "<tr><td>" << data[3] << "</td><td>" << data[7] << "</td><td>" << data[11] <<  "</td><td>" << data[15] << "</td></tr><table>";
        return stream.str();
    }
    /*std::string toString() const
    {
        std::string returnTemp = " /", temp = stringOf<Type>(data[0]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[4]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[8]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[12]);
        temp.resize(6, ' ');
        returnTemp += temp + "\\\n| ";
        temp = stringOf<Type>(data[1]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[5]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[9]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[13]);
        temp.resize(6, ' ');
        returnTemp += temp + " |\n| ";
        temp = stringOf<Type>(data[2]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[6]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[10]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[14]);
        temp.resize(6, ' ');
        returnTemp += temp + " |\n \\";
        temp = stringOf<Type>(data[3]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[7]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[11]);
        temp.resize(6, ' ');
        returnTemp += temp + ' ';
        temp = stringOf<Type>(data[15]);
        temp.resize(6, ' ');
        returnTemp += temp + "/";

        return returnTemp;
    }*/
    /*Vector4d<Type> transform (Vector4d<Type> temp1) const
    {
        Vector4d<Type> temp2;
        temp2[0] = temp1[0] * data[0] + temp1[1] * data[4] + temp1[2] * data[8]  + temp1[3] * data[12];
        temp2[1] = temp1[0] * data[1] + temp1[1] * data[5] + temp1[2] * data[9]  + temp1[3] * data[13];
        temp2[2] = temp1[0] * data[2] + temp1[1] * data[6] + temp1[2] * data[10] + temp1[3] * data[14];
        temp2[3] = temp1[0] * data[3] + temp1[1] * data[7] + temp1[2] * data[11] + temp1[3] * data[15];
        return (temp2);
    }
    Vector4d<Type> operator * (Vector4d<Type> temp1) const
    {
        Vector4d<Type> temp2;
        temp2[0] = temp1[0] * data[0] + temp1[1] * data[4] + temp1[2] * data[8]  + temp1[3] * data[12];
        temp2[1] = temp1[0] * data[1] + temp1[1] * data[5] + temp1[2] * data[9]  + temp1[3] * data[13];
        temp2[2] = temp1[0] * data[2] + temp1[1] * data[6] + temp1[2] * data[10] + temp1[3] * data[14];
        temp2[3] = temp1[0] * data[3] + temp1[1] * data[7] + temp1[2] * data[11] + temp1[3] * data[15];
        return (temp2);
    }*/
    Vector3d<Type> transform (const Vector3d<Type> temp1) const
    {
        Vector3d<Type> temp2;
        temp2[0] = temp1[0] * data[0] + temp1[1] * data[4] + temp1[2] * data[8]  + data[12];
        temp2[1] = temp1[0] * data[1] + temp1[1] * data[5] + temp1[2] * data[9]  + data[13];
        temp2[2] = temp1[0] * data[2] + temp1[1] * data[6] + temp1[2] * data[10] + data[14];
        // The fourth row of the matrix isn't used because it's only a 3d vector
        return (temp2);
    }
    Vector3d<Type> operator * (const Vector3d<Type> temp1) const
    {
        return transform(temp1);
    }
    Vector3d<Type> rotate (const Vector3d<Type> temp1) const
    {
        Vector3d<Type> temp2;
        temp2[0] = temp1[0] * data[0] + temp1[1] * data[4] + temp1[2] * data[8];
        temp2[1] = temp1[0] * data[1] + temp1[1] * data[5] + temp1[2] * data[9];
        temp2[2] = temp1[0] * data[2] + temp1[1] * data[6] + temp1[2] * data[10];
        // The fourth row of the matrix isn't used because it's only a 3d vector
        return (temp2);
    }
    Vector3d<double> absRot (const Vector3d<double> temp1) const
    {
        Vector3d<double> temp2;
        temp2[0] = fabs(temp1[0] * data[0]) + fabs(temp1[1] * data[4]) + fabs(temp1[2] * data[8]);
        temp2[1] = fabs(temp1[0] * data[1]) + fabs(temp1[1] * data[5]) + fabs(temp1[2] * data[9]);
        temp2[2] = fabs(temp1[0] * data[2]) + fabs(temp1[1] * data[6]) + fabs(temp1[2] * data[10]);
        // The fourth row of the matrix isn't used because it's only a 3d vector
        return (temp2);
    }
    Vector3d<Type> getRow (unsigned char x) const
    {
        return Vector3d<Type>(data[x], data[x+4], data[x+8]);
    }
    Vector3d<Type> getColumn (unsigned char x) const
    {
        return Vector3d<Type>(data[4*x], data[4*x+1], data[4*x+2]);
    }
    Vector3d<Type> getMovement () const
    {
        return Vector3d<Type>(data[12], data[13], data[14]);
    }
    const Matrix4d& move(Type x, Type y, Type z)
    {
        data[12] += x;
        data[13] += y;
        data[14] += z;
        return *this;
    }
    const Matrix4d& move(const Vector3d<Type> x)
    {
        data[12] += x[0];
        data[13] += x[1];
        data[14] += x[2];
        return *this;
    }
    const Matrix4d& place(Type x, Type y, Type z)
    {
        data[12] = x;
        data[13] = y;
        data[14] = z;
        return *this;
    }
    const Matrix4d& place(const Vector3d<Type> x)
    {
        data[12] = x[0];
        data[13] = x[1];
        data[14] = x[2];
        return *this;
    }

    //The functions below are meant to create matrices.
    static Matrix4d makeOrigin()
    {
        return Matrix4d<Type>(1, 0, 0, 0,
                              0, 1, 0, 0,
                              0, 0, 1, 0,
                              0, 0, 0, 1);
    }

    static Matrix4d makeMove(Type xPos, Type yPos, Type zPos)
    {
        return Matrix4d<Type>(1, 0, 0, xPos,
                              0, 1, 0, yPos,
                              0, 0, 1, zPos,
                              0, 0, 0, 1);
    }

    static Matrix4d makeMove(Vector3d<Type> pos)
    {
        return Matrix4d<Type>(1, 0, 0, pos[0],
                              0, 1, 0, pos[1],
                              0, 0, 1, pos[2],
                              0, 0, 0, 1);
    }

    static Matrix4d makeScale(Type x, Type y, Type z)
    {
        return Matrix4d<Type>(x, 0, 0, 0,
                              0, y, 0, 0,
                              0, 0, z, 0,
                              0, 0, 0, 1);
    }
    static Matrix4d makeScale(Vector3d<Type> factor)
    {
        return Matrix4d<Type>(factor[0], 0, 0, 0,
                              0, factor[1], 0, 0,
                              0, 0, factor[2], 0,
                              0, 0, 0, 1);
    }

    static Matrix4d makeAxisAngle(Type xAxis, Type yAxis, Type zAxis, Type angle)
    {
        const Type c = cos(angle), s = sin(angle);
        const Type t = 1-c;
        return Matrix4d<Type>(t*xAxis*xAxis + c,       t*yAxis*xAxis - s*zAxis, t*zAxis*xAxis + s*yAxis, 0,
                              t*xAxis*yAxis + s*zAxis, t*yAxis*yAxis + c,       t*zAxis*yAxis - s*xAxis, 0,
                              t*xAxis*zAxis - s*yAxis, t*yAxis*zAxis + s*xAxis, t*zAxis*zAxis + c,       0,
                              0,                       0,                       0,                       1);
    }
    inline static Matrix4d makeAxisAngle(const Vector3d<Type> axis, Type angle)
    {
        return makeAxisAngle(axis[0], axis[1], axis[2], angle);
    }

    static Matrix4d makeXAxis(Type angle)
    {
        const Type s = sin(angle), c = cos(angle);
        return Matrix4d<Type>(1, 0, 0, 0,
                              0, c,-s, 0,
                              0, s, c, 0,
                              0, 0, 0, 1);
    }
    static Matrix4d makeYAxis(Type angle)
    {
        const Type s = sin(angle), c = cos(angle);
        return Matrix4d<Type>(c, 0, s, 0,
                              0, 1, 0, 0,
                             -s, 0, c, 0,
                              0, 0, 0, 1);
    }
    static Matrix4d makeZAxis(Type angle)
    {
        const Type s = sin(angle), c = cos(angle);
        return Matrix4d<Type>(c,-s, 0, 0,
                              s, c, 0, 0,
                              0, 0, 1, 0,
                              0, 0, 0, 1);
    }
    //TODO: can be optimized
    static Matrix4d makeEulerAngles(Type xAngle, Type yAngle, Type zAngle)
    {
        return makeZAxis(zAngle) * makeYAxis(yAngle) * makeXAxis(xAngle);
    }
    inline static Matrix4d makeEulerAngles(const Type angles[3])
    {
        return makeEulerAngles(angles[0], angles[1], angles[2]);
    }
    //TODO: can be optimized
    static Matrix4d makeInverseEulerAngles(Type xAngle, Type yAngle, Type zAngle)
    {
        return makeXAxis(xAngle) * makeYAxis(yAngle) * makeZAxis(zAngle);
    }
    inline static Matrix4d makeInverseEulerAngles(const Type angles[3])
    {
        return makeInverseEulerAngles(angles[0], angles[1], angles[2]);
    }
    static Matrix4d makePerspective(Type vertFOV, Type widthHeightRatio, Type nearClip, Type farClip)
    {
        const Type tanHalfFOV = tan(vertFOV / 2.0);
        const Type zRange = nearClip - farClip;

        return Matrix4d<Type>(-1/(widthHeightRatio*tanHalfFOV), 0, 0, 0,
                              0, -1/tanHalfFOV, 0, 0,
                              0, 0, (farClip + nearClip)/ zRange, (2*farClip*nearClip)/ zRange,
                              0, 0, -1, 0);
    }
};
template <typename Type>
std::ostream& operator<< (std::ostream& outStream, const de::Matrix4d<Type>& temp )
{
    return outStream << temp.toString();
}
}
#endif
