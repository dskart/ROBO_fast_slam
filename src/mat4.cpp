#include "mat4.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

// Constructors
mat4::mat4()
{
    data[0] = vec4(1.0, 0.0, 0.0, 0.0);
    data[1] = vec4(0.0, 1.0, 0.0, 0.0);
    data[2] = vec4(0.0, 0.0, 1.0, 0.0);
    data[3] = vec4(0.0, 0.0, 0.0, 1.0);
}

mat4::mat4(float diag)
{
    data[0] = vec4(diag, 0.0, 0.0, 0.0);
    data[1] = vec4(0.0, diag, 0.0, 0.0);
    data[2] = vec4(0.0, 0.0, diag, 0.0);
    data[3] = vec4(0.0, 0.0, 0.0, diag);
}

mat4::mat4(const vec4 &col0, const vec4 &col1, const vec4 &col2, const vec4& col3)
{
    data[0] = col0;
    data[1] = col1;
    data[2] = col2;
    data[3] = col3;
}

mat4::mat4(const mat4 &m2)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] = m2[i];
    }
}

// Getters

const vec4 &mat4::operator[](unsigned int index) const
{
    return data[index];
}

vec4 &mat4::operator[](unsigned int index)
{
    return data[index];
}

const vec4 &mat4::operator()(unsigned int index) const
{
    assert(index < 4);
    return data[index];
}

vec4 &mat4::operator()(unsigned int index)
{
    assert(index < 4);
    return data[index];
}

// Static Initializers

mat4 mat4::rot(float angle, float x, float y, float z)
{
    angle = (M_PI * angle) / 180;
    float sqsum = x * x + y * y + z * z;
    float m11 = ((x * x) + ((y * y + z * z) * cosf(angle))) / sqsum;
    float m22 = ((y * y) + ((x * x + z * z) * cosf(angle))) / sqsum;
    float m33 = ((z * z) + ((y * y + x * x) * cosf(angle))) / sqsum;
    float m21 = ((x * y * (1 - cosf(angle))) + (z * sqrtf(sqsum) * sinf(angle))) / sqsum;
    float m12 = ((x * y * (1 - cosf(angle))) - (z * sqrtf(sqsum) * sinf(angle))) / sqsum;
    float m31 = ((x * z * (1 - cosf(angle))) - (y * sqrtf(sqsum) * sinf(angle))) / sqsum;
    float m13 = ((x * z * (1 - cosf(angle))) + (y * sqrtf(sqsum) * sinf(angle))) / sqsum;
    float m23 = ((y * z * (1 - cosf(angle))) - (x * sqrtf(sqsum) * sinf(angle))) / sqsum;
    float m32 = ((y * z * (1 - cosf(angle))) + (x * sqrtf(sqsum) * sinf(angle))) / sqsum;

    vec4 c1 = vec4(m11, m21, m31, 0.0);
    vec4 c2 = vec4(m12, m22, m32, 0.0);
    vec4 c3 = vec4(m13, m23, m33, 0.0);
    vec4 c4 = vec4(0.0, 0.0, 0.0, 1.0);

    return mat4(c1, c2, c3, c4);
}

mat4 mat4::trans(float x, float y, float z)
{
    mat4 ret = mat4();
    ret[3] = vec4(x, y, z, 1.0);
    return ret;
}

mat4 mat4::scale(float x, float y, float z)
{
    vec4 c1 = vec4(x, 0.0, 0.0, 0.0);
    vec4 c2 = vec4(0.0, y, 0.0, 0.0);
    vec4 c3 = vec4(0.0, 0.0, z, 0.0);
    vec4 c4 = vec4(0.0, 0.0, 0.0, 1.0);
    return mat4(c1, c2, c3, c4);
}

// Operators

mat4 &mat4::operator=(const mat4 &m2)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] = m2[i];
    }
    return (*this);
}

bool mat4::operator==(const mat4 &m2) const
{
    for(int i = 0; i < 4; i++)
    {
        if(data[i] != m2[i])
        {
            return false;
        }
    }
    return true;
}

bool mat4::operator!=(const mat4 &m2) const
{
    return !((*this) == m2);
}

mat4& mat4::operator+=(const mat4 &m2)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] += m2[i];
    }
    return (*this);
}

mat4& mat4::operator-=(const mat4 &m2)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] -= m2[i];
    }
    return (*this);
}

mat4& mat4::operator*=(float c)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] *= c;
    }
    return (*this);
}

mat4& mat4::operator/=(float c)
{
    for(int i = 0; i < 4; i++)
    {
        data[i] /= c;
    }
    return (*this);
}

mat4 mat4::operator+(const mat4 &m2) const
{
    mat4 ret = mat4();
    for(int i = 0; i < 4; i++)
    {
        ret[i] = data[i] + m2[i];
    }
    return ret;
}
mat4  mat4::operator-(const mat4 &m2) const
{
    mat4 ret = mat4();
    for(int i = 0; i < 4; i++)
    {
        ret[i] = data[i] - m2[i];
    }
    return ret;
}

mat4 mat4::operator*(float c) const
{
    mat4 ret = mat4();
    for(int i = 0; i < 4; i++)
    {
        ret[i] = data[i] * c;
    }
    return ret;
}

mat4 mat4::operator/(float c) const
{
    mat4 ret = mat4();
    for(int i = 0; i < 4; i++)
    {
        ret[i] = data[i] / c;
    }
    return ret;
}

mat4 mat4::operator*(const mat4 &m2) const
{
    mat4 ret = mat4();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ret[j][i] = 0;
            for (int k = 0; k < 4; k++)
            {
                ret[j][i] += data[k][i] * m2[j][k];
            }
        }
    }

    return ret;
}

vec4 mat4::operator*(const vec4 &v) const
{
    vec4 ret = vec4();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ret[i] += data[j][i] * v[j];
        }
    }

    return ret;
}

mat4 mat4::transpose() const
{
    mat4 ret = mat4();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ret[i][j] = data[j][i];
        }
    }

    return ret;
}

const vec4 &mat4::col(unsigned int index) const
{
    return data[index];
}

vec4 &mat4::col(unsigned int index)
{
    return data[index];
}

// Out of class operators
mat4 operator*(float c, const mat4 &m)
{
    return m * c;
}

vec4 operator*(const vec4 &v, const mat4 &m)
{
    vec4 ret = vec4();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ret[i] += v[j] * m[i][j];
        }
    }

    return ret;
}

std::ostream &operator<<(std::ostream &o, const mat4 &m)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            o << m[j][i] << "\t";
        }
        if(i < 3)
        {
            o << "\n";
        }
    }

    return o;
}
