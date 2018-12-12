// Base code written by Jan Allbeck, Chris Czyzewicz, Cory Boatright, Tiantian Liu, Benedict Brown, and Adam Mally
// University of Pennsylvania

#ifndef VEC4_H
#define VEC4_H

#include <iostream>

class vec4 {
 private:
    ///The set of floats representing the coordinates of the vector
	float data[4];
 public:
	///----------------------------------------------------------------------
	/// Constructors
	///----------------------------------------------------------------------
    vec4();                                     // initialize the vector to (0, 0, 0, 0)
    vec4(float x, float y, float z, float w);   // initialize the vector to (x, y, z, w)
    vec4(const vec4 &v2);                       // copy constructor, copies values of v2 into this
	
	///----------------------------------------------------------------------
	/// Getters/Setters
	///----------------------------------------------------------------------		

	/// Returns the value at index
  /// Does NOT check the array bound because doing so is slow
    float operator[](unsigned int index) const;
    
	/// Returns a reference to the value at index
  /// Does NOT check the array bound because doing so is slow
    float &operator[](unsigned int index);

  /// Returns the value at index
  /// DOES check the array bound with assert even though is slow
    float operator()(unsigned int index) const;
    
	/// Returns a reference to the value at index
  /// DOES check the array bound with assert even though is slow
    float& operator()(unsigned int index);

	///----------------------------------------------------------------------
	/// Operator Methods
	///----------------------------------------------------------------------		

	/// Assign v2 to this and return a reference to this
    vec4 &operator=(const vec4 &v2);

	/// Test for equality
		bool operator==(const vec4 &v2) const;	   //Component-wise comparison
	
	/// Test for inequality
		bool operator!=(const vec4 &v2) const;	   //Component-wise comparison
	
	/// Arithmetic:
	/// e.g. += adds v2 to this and return this (like regular +=)
	///      +  returns a new vector that is sum of this and v2
    vec4& operator+=(const vec4 &v2);
    vec4& operator-=(const vec4 &v2);
    vec4& operator*=(float c);                 // multiplication by a scalar
    vec4& operator/=(float c);                 // division by a scalar
	
    vec4  operator+(const vec4 &v2) const;
    vec4  operator-(const vec4 &v2) const;
    vec4  operator*(float c) const;             // multiplication by a scalar
    vec4  operator/(float c) const;             // division by a scalar

	///----------------------------------------------------------------------
	/// Other Methods
	///----------------------------------------------------------------------		

    /// Returns the geometric length of the input vector
    float length() const;

    /// return a new vec4 that is a normalized (unit-length) version of this one
    vec4 normalize() const;

    /// noralize this vector in place
    void norm();
};

///----------------------------------------------------------------------
/// Other Functions (not part of the vec4 class)
///----------------------------------------------------------------------		

/// Dot Product
float dot(const vec4 &v1, const vec4 &v2);

/// Cross Product
vec4 cross(const vec4 &v1, const vec4 &v2);     //Compute the result of v1 x v2 using only their X, Y, and Z elements.
                                                //In other words, treat v1 and v2 as 3D vectors, not 4D vectors.
                                                //The fourth element of the resultant vector should be 0.

/// Scalar Multiplication (c * v)
vec4 operator*(float c, const vec4 &v);

/// Prints the vector to a stream in a nice format for integration with cout
std::ostream &operator<<(std::ostream &o, const vec4 &v);

#endif /* VEC4_H */
