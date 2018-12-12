#include "vec4.h"
#include <assert.h>
#include <math.h>

// Constructors

vec4::vec4()
{
    data[0] = 0.0;
    data[1] = 0.0;
    data[2] = 0.0;
    data[3] = 0.0;
}

vec4::vec4(float x, float y, float z, float w)
{
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = w;
}

vec4::vec4(const vec4 &v2)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] = v2[i];
    }
}

// Getters/Setters

float vec4::operator [](unsigned int index) const
{
    return data[index];
}

float &vec4::operator [](unsigned int index)
{
    return data[index];
}

float vec4::operator ()(unsigned int index) const
{
    assert(index < 4);
    return data[index];
}

float &vec4::operator ()(unsigned int index)
{
    assert(index < 4);
    return data[index];
}

// Operators

vec4 &vec4::operator =(const vec4 &v2)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] = v2[i];
    }
    return (*this);
}

bool vec4::operator ==(const vec4 &v2) const
{
    for(int i = 0; i < 4; i++)
    {
        if(data[i] != v2[i])
        {
            return false;
        }
    }
    return true;
}

bool vec4::operator !=(const vec4 &v2) const
{
    return !((*this) == v2);
}

vec4 &vec4::operator +=(const vec4 &v2)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] += v2[i];
    }
    return (*this);
}

vec4 &vec4::operator -=(const vec4 &v2)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] -= v2[i];
    }
    return (*this);
}

vec4 &vec4::operator *=(float c)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] *= c;
    }
    return (*this);
}

vec4 &vec4::operator /=(float c)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] /= c;
    }
    return (*this);
}

vec4 vec4::operator +(const vec4 &v2) const
{
    vec4 ret = vec4();
    for(int i = 0; i < 4; i++)
    {
        ret[i] = data[i] + v2[i];
    }
    return ret;
}

vec4 vec4::operator -(const vec4 &v2) const
{
    vec4 ret = vec4();
    for(int i = 0; i < 4; i++)
    {
        ret[i] = data[i] - v2[i];
    }
    return ret;
}

vec4 vec4::operator *(float c) const
{
    vec4 ret = vec4();
    for(int i = 0; i < 4; i++)
    {
        ret[i] = data[i] * c;
    }
    return ret;
}

vec4 vec4::operator /(float c) const
{
    vec4 ret = vec4();
    for(int i = 0; i < 4; i++)
    {
        ret[i] = data[i] / c;
    }
    return ret;
}

// Other Operations

float vec4::length() const
{
    // Sum the squared of each coordinate and then take the square root
    return sqrtf(data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3]);
}

vec4 vec4::normalize() const
{
    return (*this) / length();
}

void vec4::norm()
{
    (*this) /= length();
}

// Out of class operations

float dot(const vec4 &v1, const vec4 &v2)
{
    float sum = 0.0;
    for(int i = 0; i < 4; i++)
    {
        sum += v1[i] * v2[i];
    }

    return sum;
}

vec4 cross(const vec4 &v1, const vec4 &v2)
{
    vec4 ret = vec4();

    // Cross product formula for each coordinate
    ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
    ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
    ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
    ret[3] = 0.0;

    return ret;
}

vec4 operator*(float c, const vec4 &v)
{
    return v * c;
}

std::ostream &operator<<(std::ostream &o, const vec4 &v)
{
    o << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
    return o;
}
