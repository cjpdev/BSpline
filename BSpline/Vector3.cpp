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

#include <atlstr.h>
#include <math.h>
#include "Vector3.h"

Vector3::~Vector3()
{
	if(vectorStrC)
	{
		delete vectorStrC;
	}
}

Vector3::Vector3()
{
	x = 0;
    y = 0;
    z = 0;

	vectorStrC = NULL;
}

Vector3::Vector3(double zero)
{
	x = zero;
    y = zero;
    z = zero;
	vectorStrC = NULL;
}


Vector3::Vector3(double a, double b, double c)
{
	x = a;
    y = b;
    z = c;
	vectorStrC = NULL;
}

/// Note: A unit vector is a normalized vector, a normalized vector is; <=1
Vector3 Vector3::zero(){ return Vector3(0,0,0); }
Vector3 Vector3::unitX() { return Vector3(1.0f, 0.0f, 0.0f); }
Vector3 Vector3::unitY() { return Vector3(0.0f, 1.0f, 0.0f); }
Vector3 Vector3::unitZ() { return Vector3(0.0f, 0.0f, 1.0f); }
Vector3 Vector3::negativeUnitX() { return  Vector3(-1.0f, 0.0f, 0.0f); } 
Vector3 Vector3::negativeUnitY() { return Vector3(0.0f, -1.0f, 0.0f); }
Vector3 Vector3::negativeUnitZ() { return  Vector3(0.0f, 0.0f, -1.0f); }
Vector3 Vector3::unitVector() { return  Vector3(1.0f, 1.0f, 1.0f); }

bool Vector3::operator< (Vector3 &v) const
{
    if ( x < v.x ) return true;
    if ( x > v.x ) return false;
    if ( y < v.y ) return true;
    if ( y > v.y ) return false;
    return z < v.z;
}

bool Vector3::operator> (Vector3 &v) const
{
    if ( x > v.x ) return true;
    if ( x < v.x ) return false;
    if ( y > v.y ) return true;
    if ( y < v.y ) return false;
    return z > v.z;
}

bool		  Vector3::operator<=( Vector3 const & v ) const {  return x <= v.x && y <= v.y && z <= v.z;}
bool		  Vector3::operator>=( Vector3 const & v ) const {  return x >= v.x && y >= v.y && z >= v.z;}
bool		  Vector3::operator==(Vector3 &v) const  { return x==v.x && y==v.y && z==v.z;}
bool		  Vector3::operator!=(Vector3 &v) const  { return x!=v.x || y!=v.y || z!=v.z;}

Vector3		  Vector3::operator% ( Vector3 const & v ) const {  return Vector3(y*v.z-v.y*z, v.x*z-x*v.z, x*v.y-v.x*y); }

Vector3		  Vector3::operator-( Vector3 const &v ) const {  return Vector3( x-v.x, y-v.y, z-v.z);}
Vector3		  Vector3::operator-() const {  return Vector3(-x,-y,-z);}

Vector3 & Vector3::operator-= (  double &d )
{
	x -= d;
	y -= d;
	z -= d;
	return *this;
}

Vector3 & Vector3::operator-= (  Vector3 &v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3		  Vector3::operator + ( Vector3 const &v ) const {  return Vector3( x+v.x, y+v.y, z+v.z);}

Vector3 &     Vector3::operator+= ( double &d )
{
	x += d;
	y += d;
	z += d;
	return *this;
}

Vector3 & Vector3::operator+= ( Vector3 &v )
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

double		  Vector3::operator * ( Vector3 const & v ) const  { return x*v.x + y*v.y + z*v.z; }

Vector3 & Vector3::operator*=( double &s )
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}


Vector3 & Vector3::operator/=( double &s )
{
	if(s)
	{
		s = 1.0/s;
		x *= s;
		y *= s;
		z *= s;
	} else {
		x = 0;
		y = 0;
		z = 0;
	}
	return *this;
}	  


void Vector3::clear()
{
	x = 0;
	y = 0;
	z = 0;
}

double Vector3::dot( Vector3 &v1, Vector3 &v2 )  
{ 
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

double Vector3::dot( Vector3 &v )  
{ 
	return x*v.x + y*v.y + z*v.z;
}

double Vector3::lengthSquared()
{
	return (x*x + y*y + z*z);
}

double Vector3::length(Vector3 &v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

double Vector3::length()
{
	return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::cross( Vector3 &v1, Vector3  &v2 )
{
	return Vector3( v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x);
}

void Vector3::normalize()
{  
	double norm;
	norm = 1.0/sqrt(x*x + y*y + z*z);
	x *= norm;
	y *= norm;
	z *= norm;
}

Vector3 Vector3::normalized() 
{ 
  Vector3 n = *this;
  n.normalize();
  return Vector3(n);
}


double Vector3::distance(Vector3 const &v1, Vector3 const &v2)
{
	return length(v1-v2);
}


Vector3 Vector3::sgn( Vector3 const &v )
{
	return Vector3( (v.x)<0?-1:1, (v.y)<0?-1:1, (v.z)<0?-1:1);
}

Vector3 Vector3::mid(Vector3 vector)
{
    return Vector3((x + vector.x) / 2.0f, (y + vector.y) / 2.0f, (z + vector.z) / 2.0f);
}

Vector3 Vector3::nth(Vector3 vector, double nth)
{
    return Vector3( (x + vector.x) / nth, (y + vector.y) / nth, (z + vector.z) / nth );
}

double Vector3::angle( Vector3 &v1, Vector3 &v2 )
{
	return v1.angle(v2);
}

/** 
*   Returns the angle in radians between this vector and the vector
*   parameter; the return value is constrained to the range [0,PI]. 
*   @param v1    the other vector 
*   @return   the angle in radians in the range [0,PI] 
*/  
double Vector3::angle(Vector3 &v1) 
{ 
	double vDot = normalized().dot(v1.normalized());
    if( vDot < -1.0) vDot = -1.0;
    if( vDot >  1.0) vDot =  1.0;
    return((double) (acos( vDot )));
} 

Vector3 Vector3::lineNearestPointTo(Vector3 p1, Vector3 p2, Vector3 pX)
{
	double u = ((pX.x - p1.x) * (p2.x - p1.x)) + ((pX.y - p1.y) * (p2.y - p1.y)) + ((pX.z - p1.z) * (p2.z - p1.z));
	
	double dist = Vector3::distance(p1,p2);
	
	u = u / (dist*dist);

	if(u == 0 || dist == 0)
	{
		//*** TODO *** This need to return some else as (0,0,0) could be as real vector 0;
		return Vector3(0,0,0);
	}

	Vector3 t(0,0,0);

	t.x = p1.x + u * (p2.x - p1.x);
	t.y = p1.y + u * (p2.y - p1.y);
	t.z = p1.z + u * (p2.z - p1.z);

	//if( Vector3::distance(t,p1) == 0)
	//{
	//	return Vector3(0,0,0);
	//}

	return Vector3(t);
}

Vector3 Vector3::GetClosestPointOnLineSegment(Vector3 A, Vector3 B, Vector3 C)
{
    Vector3 AC = C - A;       //Vector from A to P   
    Vector3 AB = B - A;       //Vector from A to B  

    float magnitudeAB = AB.lengthSquared();     //Magnitude of AB vector (it's length squared) 

	if( magnitudeAB == 0)
	{
		 return A;
	}

    float ABAPproduct = Vector3::dot(AC, AB);    //The DOT product of a_to_p and a_to_b     
    float distance = ABAPproduct / magnitudeAB; //The normalized "distance" from a to your closest point  

    if (distance < 0)     //Check if P projection is over vectorAB     
    {
        return A;

    }
    else if (distance > 1) {
        return B;
    }
    else
    {
        return A + AB * distance;
    }
}

//Compute the distance from AB to C
//if isSegment is true, AB is a segment, not a line.
double Vector3::GetLinePointDist(Vector3 A, Vector3 B, Vector3 C, bool isSegment)
{
    double dist = Vector3::dot((B-A),(C-A)) / sqrt((B-A)*(B-A));
    
	if(isSegment) 
	{
		int dot1 = (C-B)*(B-A);
		if(dot1 > 0)return sqrt((B-C)*(B-C));
		int dot2 = (C-A)*(A-B);
		if(dot2 > 0)return sqrt((A-C)*(A-C));
    }
    
	return dist;
	//return abs(dist);
}


void  Vector3::interpolate(Vector3 &v1, double alpha) 
{
	x = (1-alpha)*x + alpha*v1.x;
	y = (1-alpha)*y + alpha*v1.y;
	z = (1-alpha)*z + alpha*v1.z;
}  

Vector3 Vector3::Reflect(Vector3 normal)
{
     return *this - (2 * dot(normal) * normal);
}


double Vector3::angleDir(Vector3 fwd,  Vector3 targetDir, Vector3 up)
{
    Vector3 perp = Vector3::cross(fwd, targetDir);
    double dir = Vector3::dot(perp, up);
       
    if (dir > 0.0) {
        return 1.0;
    } else if (dir < 0.0) {
        return -1.0;
    } else {
        return 0.0;
    }
}


Vector3 Vector3::finalVector( Vector3 position, Vector3 fwd,  Vector3 fwdTarget)
{
   Vector3 VectorResult;
	float DotResult = Vector3::dot(fwd, fwdTarget);

    if (DotResult > 0)
    {
        VectorResult = fwd + fwdTarget;
    }
    else
    {
        VectorResult = fwd - fwdTarget;
    }

	return Vector3(VectorResult);
 
}

// Continuous direction of rotation
Vector3 Vector3::continuousAngle(Vector3 fwd, Vector3 targetDir, Vector3 upDir) 
{
        double angle = Vector3::angle(fwd, targetDir);
       
        if (Vector3::angleDir(fwd, targetDir, upDir) == -1) 
		{
            return 360 - angle;
        } else {
            return angle;
        }
}

bool Vector3::collisionCircleLine(Vector3 c, double r, Vector3 v1, Vector3 v2)
{
	double ab2, acab, h2;

    Vector3 ac = c - v1;
    Vector3 ab = v2 - v1;
	ab2 = Vector3::dot(ab,ab);
	acab = Vector3::dot(ac, ab);

    double t = acab / ab2;

    if (t < 0)
        t = 0;
    else if (t > 1)
        t = 1;

	Vector3 n = (ab * t);

    Vector3 h = (n + v1) - c;

    h2 = Vector3::dot(h,h);

    return (h2 <= (r * r));
}


char* Vector3::toString()
{
	CString vector3Str;
	vector3Str.Format(_T("%3.2f,%3.2f,%3.2f"), x,y,z);

	if(vectorStrC)
	{
		delete vectorStrC;
	}

	vectorStrC = new char[vector3Str.GetLength() + 1 ];

	int len = (vector3Str.GetLength()<80)?(vector3Str.GetLength()):80;
		  
	for(int n = 0; n <len;  n++)
	{
		TCHAR t= vector3Str.GetAt(n);
		if(t < 32 || t > 255)
		{
			t =  32;
		}

		char c= (unsigned char)t;
		vectorStrC[n] = c;
	}

	//vectorStrC[len] = '\0';

	return vectorStrC;
}

// Simple line interpolate
Vector3 Vector3::interpolateWithinLine(Vector3 v1, Vector3 v2, double aplha)
{
	Vector3 n = v1 - v2;
	double d = distance(v1,v2);
	
	// This is a linear interpolation, so I simple need to calculate the slop inc
	n = n / d;

	if(aplha <=0)
	{
		return Vector3(v1);

	} else if(aplha >= d )
	{
		return Vector3(v2);
	}
	
	return Vector3(v1 - (aplha*n));
}


///	Finds a vector perpendicular to this one.
Vector3 Vector3::perpendicular()
{
	Vector3 result(0,0,0);

	result = Vector3::cross(*this,Vector3::unitX());

	if (result.lengthSquared() < EPSILON_MAX)
	{
		// This vector is the Y axis multiplied by a scalar, so we have to use another axis
		result = Vector3::cross(*this,Vector3::unitY());
	}

    return result;
}

