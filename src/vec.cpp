#include "vec.h"
#include <assert.h>
#include <math.h>



// template<typename T, size_t SIZE>
// Vec<T,SIZE>::Vec(const Vec &v2)
// {
//   for(int i = 0; i < 4; i++)
//   {
//       data_[i] = v2[i];
//   }
// }

// // Getters/Setters
// template<typename T, size_t SIZE>
// float Vec<T,SIZE>::operator [](unsigned int index) const
// {
//   return data_[index];
// }

// template<typename T, size_t SIZE>
// float& Vec<T,SIZE>::operator [](unsigned int index)
// {
//   return data_[index];
// }

// template<typename T, size_t SIZE>
// float Vec<T,SIZE>::operator ()(unsigned int index) const
// {
//   assert(index < 4);
//   return data_[index];
// }

// template<typename T, size_t SIZE>
// float& Vec<T,SIZE>::operator ()(unsigned int index)
// {
//   assert(index < 4);
//   return data_[index];
// }

// // Operators
// template<typename T, size_t SIZE>
// Vec<T,SIZE>& Vec<T,SIZE>::operator =(const Vec &v2)
// {
//   for(int i = 0; i < 4; i++)
//   {
//     data_[i] = v2[i];
//   }
//   return (*this);
// }

// template<typename T, size_t SIZE>
// bool Vec<T,SIZE>::operator ==(const Vec &v2) const
// {
//   for(int i = 0; i < 4; i++)
//   {
//     if(data_[i] != v2[i])
//     {
//       return false;
//     }
//   }
//   return true;
// }

// template<typename T, size_t SIZE>
// bool Vec<T,SIZE>::operator !=(const Vec &v2) const
// {
//   return !((*this) == v2);
// }

// template<typename T, size_t SIZE>
// Vec<T,SIZE>& Vec<T,SIZE>::operator +=(const Vec &v2)
// {
//   for(int i = 0; i < 4; i++)
//   {
//     data_[i] += v2[i];
//   }
//   return (*this);
// }

// template<typename T, size_t SIZE>
// Vec<T,SIZE>& Vec<T,SIZE>::operator -=(const Vec &v2)
// {
//   for(int i = 0; i < 4; i++)
//   {
//     data_[i] -= v2[i];
//   }
//   return (*this);
// }

// template<typename T, size_t SIZE>
// Vec<T,SIZE>& Vec<T,SIZE>::operator *=(float c)
// {
//   for(int i = 0; i < 4; i++)
//   {
//     data_[i] *= c;
//   }
//   return (*this);
// }

// template<typename T, size_t SIZE>
// Vec<T,SIZE>& Vec<T,SIZE>::operator /=(float c)
// {
//   for(int i = 0; i < 4; i++)
//   {
//     data_[i] /= c;
//   }
//   return (*this);
// }

// template<typename T, size_t SIZE>
// Vec<T,SIZE> Vec<T,SIZE>::operator +(const Vec &v2) const
// {
//   Vec ret = Vec();
//   for(int i = 0; i < 4; i++)
//   {
//     ret[i] = data_[i] + v2[i];
//   }
//   return ret;
// }

// template<typename T, size_t SIZE>
// Vec<T,SIZE> Vec<T,SIZE>::operator -(const Vec &v2) const
// {
//   Vec ret = Vec();
//   for(int i = 0; i < 4; i++)
//   {
//     ret[i] = data_[i] - v2[i];
//   }
//   return ret;
// }
// template<typename T, size_t SIZE>
// Vec<T,SIZE> Vec<T,SIZE>::operator *(float c) const
// {
//   Vec ret = Vec();
//   for(int i = 0; i < 4; i++)
//   {
//     ret[i] = data_[i] * c;
//   }
//   return ret;
// }

// template<typename T, size_t SIZE>
// Vec<T,SIZE> Vec<T,SIZE>::operator /(float c) const
// {
//   Vec ret = Vec();
//   for(int i = 0; i < 4; i++)
//   {
//     ret[i] = data_[i] / c;
//   }
//   return ret;
// }

// // Other Operations 
// template<typename T, size_t SIZE>
// float Vec<T,SIZE>::length() const
// {
//     // Sum the squared of each coordinate and then take the square root
//   return sqrtf(data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2] + data_[3] * data_[3]);
// }

// template<typename T, size_t SIZE>
// Vec<T,SIZE> Vec<T,SIZE>::normalize() const
// {
//   return (*this) / length();
// }

// template<typename T, size_t SIZE>
// void Vec<T,SIZE>::norm()
// {
//   (*this) /= length();
// }

//--------------------------------Out of class operations-----------------------------------------

template<typename T, size_t SIZE>
float dot(const Vec<T,SIZE> &v1, const Vec<T,SIZE> &v2)
{
  float sum = 0.0;
  for(int i = 0; i < 4; i++)
  {
    sum += v1[i] * v2[i];
  }

  return sum;
}

template<typename T, size_t SIZE>
Vec<T,SIZE> cross(const Vec<T,SIZE> &v1, const Vec<T,SIZE> &v2)
{
  Vec<T,SIZE> ret;

  // Cross product formula for each coordinate
  ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
  ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
  ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
  ret[3] = 0.0;

  return ret;
}

template<typename T, size_t SIZE>
Vec<T,SIZE> operator*(float c, const Vec<T,SIZE> &v)
{
  return v * c;
}

template<typename T, size_t SIZE>
std::ostream &operator<<(std::ostream &o, const Vec<T,SIZE> &v)
{
  o << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
  return o;
}
