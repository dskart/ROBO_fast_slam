// Base code written by Jan Allbeck, Chris Czyzewicz, Cory Boatright, Tiantian Liu, Benedict Brown, and Adam Mally
// Updated by Raphael Van Hoffelen
// University of Pennsylvania

#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <array>
#include <stdio.h>
#include <cstring>

template<typename T, int SIZE>
class Vec {
  private:
    T data_[SIZE];

  public:
    int v_len_;

    Vec() 
    {
      for(int i = 0; i < SIZE; i++)
      {
        data_[i] = 0;
      }
    }

    Vec(T (&static_array)[SIZE])
    {
      v_len_ = SIZE;
      std::copy(std::begin(static_array), std::end(static_array), std::begin(data_));
    }

    // copy constructor, copies values of v2 into this
    Vec(const Vec &v2)
    {
      for(int i = 0; i < SIZE; i++)
      {
        data_[i] = v2[i];
      }
    }

    //----------------------------------------------------------------------
    // Getters/Setters
    //----------------------------------------------------------------------   

    // Returns the value at index
    // Does NOT check the array bound because doing so is slow
    float operator [](unsigned int index) const
    {
      return data_[index];
    }

    // Returns a reference to the value at index
    // Does NOT check the array bound because doing so is slow
    float &operator [](unsigned int index)
    {
      return data_[index];
    }

    // Returns the value at index
    // DOES check the array bound with assert even though is slow
    float operator ()(unsigned int index) const
    {
      if(index < SIZE)
      {
        return data_[index];
      };
    }

    // Returns a reference to the value at index
    // DOES check the array bound with assert even though is slow
    float &operator ()(unsigned int index)
    {
      if(index < SIZE)
      {
        return data_[index];
      };
    }

    // Assign v2 to this and return a reference to this
    Vec &operator =(const Vec &v2)
    {
      for(int i = 0; i < SIZE; i++)
      {
        data_[i] = v2[i];
      }
      return (*this);
    }

    // Test for equality
    bool operator ==(const Vec &v2) const
    {
      for(int i = 0; i < SIZE; i++)
      {
        if(data_[i] != v2[i])
        {
          return false;
        }
      }
      return true;
    }

    // Test for inequality
    bool operator !=(const Vec &v2) const
    {
      return !((*this) == v2);
    }

    //------------ARITHMETIC------------
    // e.g. += adds v2 to this and return this (like regular +=)
    //      +  returns a new Vector that is sum of this and v2
    Vec &operator +=(const Vec &v2)
    {
      for(int i = 0; i < SIZE; i++)
      {
        data_[i] += v2[i];
      }
      return (*this);
    }

    Vec &operator -=(const Vec &v2)
    {
      for(int i = 0; i < SIZE; i++)
      {
        data_[i] -= v2[i];
      }
      return (*this);
    }

    Vec &operator *=(float c) //multiplication by scalar
    {
      for(int i = 0; i < SIZE; i++)
      {
        data_[i] *= c;
      }
      return (*this);
    }

    Vec &operator /=(float c) //division by a scalar
    {
      for(int i = 0; i < SIZE; i++)
      {
        data_[i] /= c;
      }
      return (*this);
    }

    Vec operator +(const Vec &v2) const
    {
      Vec ret = Vec();
      for(int i = 0; i < SIZE; i++)
      {
        ret[i] = data_[i] + v2[i];
      }
      return ret;
    }

    Vec operator -(const Vec &v2) const
    {
      Vec ret = Vec();
      for(int i = 0; i < SIZE; i++)
      {
        ret[i] = data_[i] - v2[i];
      }
      return ret;
    }

    Vec operator *(float c) const // multiplication by a scalar
    {
      Vec ret = Vec();
      for(int i = 0; i < SIZE; i++)
      {
        ret[i] = data_[i] * c;
      }
      return ret;
    }

    Vec operator /(float c) const // division by a scalar
    {
      Vec ret = Vec();
      for(int i = 0; i < SIZE; i++)
      {
        ret[i] = data_[i] / c;
      }
      return ret;
    }

    //----------------------------------------------------------------------
    // Other Methods
    //----------------------------------------------------------------------   

    // Returns the geometric length of the input Vector
    float length() const
    {
      float sqr_sum;
      for(int ii = 0; ii < SIZE; ++ii)
      {
        sqr_sum += (float)data_[ii] * (float)data_[ii];
      }
      float square_root = this->sqrtf(sqr_sum);
      return square_root;
    }

    // return a new Vec that is a normalized (unit-length) version of this one
    Vec normalize() const
    {
      return (*this) / length();
    }

    // noralize this Vector in place
    void norm()
    {
      (*this) /= length();
    }
};

//----------------------------------------------------------------------
// Other Functions (not part of the Vec class)
//----------------------------------------------------------------------		



/// Dot Product
template<typename T, int SIZE>
float dot(const Vec<T,SIZE> &v1, const Vec<T,SIZE> &v2)
{
  float sum = 0.0;
  for(int i = 0; i < SIZE; i++)
  {
    sum += v1[i] * v2[i];
  }

  return sum;
}

// /// Cross Product
// vec cross(const vec &v1, const vec &v2)
// {
//   vec ret = vec4();

//     // Cross product formula for each coordinate
//   ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
//   ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
//   ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
//   ret[3] = 0.0;

//   return ret;
// }

/// Scalar Multiplication (c * v)
template<typename T, int SIZE>
Vec<T,SIZE> operator*(float c, const Vec<T,SIZE> &v)
{
  return v * c;
}

/// Prints the Vector to a stream in a nice format for integration with cout
template<typename T, int SIZE>
std::ostream &operator<<(std::ostream &o, const Vec<T,SIZE> &v)
{
  o << "(";
  for(int ii = 0; ii < SIZE; ++ii)
  {
    if (ii == SIZE-1)
    {
      o << v[ii]; 
    }
    else
    {
      o << v[ii] << ", "; 
    }
  }
  o << ")";

  return o;
}

#endif /* VEC_H */
