#pragma once
/**
*
	Copyright (c) 2009-2012 Chay Palton

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the Software
	is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
*  Vector3 class support lost of the most common method that are needed for doing Vector maths
*
* Author: Chay Palton
* Date: 23/04/2012
*/

#ifndef __VECTOR3__
#define __VECTOR3__


#define EPSILON_MIN    0.001			// epsilon value
#define EPSILON_MAX    1.401298E-45			// epsilon value
/**
* Add support for unity 3d
*/
#define sqrMagnitude lengthSquared

class Vector3
{
private:
	char* vectorStrC;

public:
	double x;
	double y;
	double z;

	~Vector3();
	Vector3();
	Vector3(double zero);
	Vector3(double a, double b, double c);

	static Vector3 zero();
	static Vector3 unitX();
	static Vector3 unitY();
	static Vector3 unitZ();
	static Vector3 negativeUnitX();
	static Vector3 negativeUnitY();
	static Vector3 negativeUnitZ();
	static Vector3 unitVector();

	bool operator< (Vector3 &v) const;
    bool operator> (Vector3 &v) const;
	bool operator<=( Vector3 const &v ) const;
	bool operator>=( Vector3 const &v ) const;    
	bool operator==(Vector3 &v) const;
    bool operator!=(Vector3 &v) const;

	Vector3    operator%  ( Vector3 const &v ) const;

	friend const Vector3 operator-(double &s, const Vector3 &v) {return Vector3(v.x - s, v.y - s, v.z - s);}
	friend const Vector3 operator-(const Vector3 &v, double &s) {return Vector3(v.x - s, v.y - s, v.z - s);}	
	Vector3    operator-  ( Vector3 const &v ) const;
	Vector3    operator-  ( ) const;
	Vector3 &  operator-= (  double &d );
	Vector3 &  operator-= ( Vector3 &v );

	friend const Vector3 operator + (double s, const Vector3 &v) {return Vector3(v.x + s, v.y + s, v.z + s);}
	friend const Vector3 operator + (const Vector3 &v, double s) {return Vector3(v.x + s, v.y + s, v.z + s);}
	Vector3    operator+  ( Vector3 const &v ) const;
	Vector3 &  operator+= ( double &d );
	Vector3 &  operator+= ( Vector3 &v );
	
	
	friend const Vector3 operator * (double s, const Vector3 &v) { return Vector3(v.x*s, v.y*s, v.z*s);}
	friend const Vector3 operator * (const Vector3 &v, double s) { return Vector3(v.x*s, v.y*s, v.z*s);}
	double	   operator*  ( Vector3 const &v ) const;
	Vector3 &  operator*= ( double &s );

	friend const Vector3 operator / (const Vector3 &v, double s) { if(s) { s = 1.0/s; return Vector3(v.x*s, v.y*s, v.z*s); } return Vector3(0,0,0);}
	Vector3 &  operator/= ( double &s );
	
	void clear();

	///
	///Returns the dot product of vector v1 and vector v2.
	/// @param v1 the vector
	/// @param v2 the other vector
	/// @return the dot product
	///
	static double dot( Vector3 &v1, Vector3 &v2 );

	///
	/// Returns the dot product of vector v1 and vector v2.
	/// @param v1 the vector
	/// @param v2 the other vector
	/// @return the dot product
	///
	double Vector3::dot( Vector3 &v1 );

	///
	/// Returns the squared length of this vector.
	/// @return the squared length of this vector
	///
	double lengthSquared();
	///
	/// Returns the length of this vector.
	/// @return the length of this vector
	///
	static double length(Vector3&v);
	double Vector3::length();

	/// Return the cross product of vectors v1 and v2.
	/// @param v1 the first vector
	/// @param v2 the second vector
	static Vector3 cross( Vector3 &v1, Vector3  &v2 );

	Vector3 normalized();
	void normalize();


	static double distance(Vector3 const &v1, Vector3 const &v2);

	static Vector3 sgn( Vector3 const &v );

	/// Get the mid vector, middle of a line
	Vector3 mid(Vector3 vector);

	/// Get the nth segment vector, of a line
	Vector3 nth(Vector3 vector, double nth);

	///  Returns the angle in radians between this vector and the vector
	///  parameter; the return value is constrained to the range [0,PI]. 
	///  @param v1    the other vector 
	///  @return   the angle in radians in the range [0,PI]  
	static double angle( Vector3 &v1, Vector3 &v2 );
	double angle( Vector3 &v1 );

	/////////////////
	//Feed it a line and a point, and it will give you the nearest point on the line to the target point
	//p1 and p2 are two points which define the line, pX is "the point."
	static Vector3 lineNearestPointTo(Vector3 p1, Vector3 p2, Vector3 pX);

	static Vector3 GetClosestPointOnLineSegment(Vector3 A, Vector3 B, Vector3 C);

	static double GetLinePointDist(Vector3 A, Vector3 B, Vector3 C, bool isSegment);

	///  Linearly interpolates between this vector and a given vector v1.
	///  @param v1 - The vector 
	///  @param alpha - The alpha interpolation parameter   
	void interpolate(Vector3 &v1, double alpha);

    /// Calculates a reflection vector to the plane with the given normal.
    /// Assumes this vector is pointing AWAY from the plane, invert if not.
    /// @param normal - Normal vector on which this vector will be reflected.
	//  @return - Vector
    Vector3 Reflect(Vector3 normal);


	/// returns -1 when to the left, 1 to the right, and 0 for forward/backward
	static double angleDir(Vector3 fwd,  Vector3 targetDir, Vector3 up);

	/// Get also the final vector, transform own collisions.
	static Vector3 Vector3::finalVector( Vector3 position, Vector3 fwd,  Vector3 fwdTarget);

	/// Continuous direction of rotation
	static Vector3 continuousAngle(Vector3 fwd, Vector3 targetDir, Vector3 upDir);


	static bool collisionCircleLine(Vector3 centre, double radius, Vector3 lineV1, Vector3 lineV2);


	static Vector3 interpolateWithinLine(Vector3 v1, Vector3 v2, double aplha);
	///
	/// Convert Vector3 to a char string for displaying using 
	/// printf
	///
	char* toString();

	Vector3 perpendicular();
};



#endif
