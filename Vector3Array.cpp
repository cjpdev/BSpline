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

/**
* Manage a collection Vector3 class
*
*/

#include "Vector3Array.h"
#include <algorithm>
#include <math.h>

using namespace std;

Vector3Array::Vector3Array(void)
{
	/** This is used as a safe return where there is not vector */
	v3empty.x = 0;
	v3empty.y = 0;
	v3empty.z = 0;
}

Vector3Array::~Vector3Array(void)
{
	vector3List.clear();
}

long Vector3Array::Length()
{
	return vector3List.size();
}

bool Vector3Array::ItemRemove(long index)
{
	if(index >=0 && index < (long)vector3List.size())
	{
		vector3List.erase(vector3List.begin( ) + index);
		return true;
	}
	return false;
}


void Vector3Array::Clear()
{
	vector3List.clear();
}

void Vector3Array::Pop()
{
	vector3List.pop_back();
}


bool Vector3Array::ItemRemoveAll(double x, double y, double z, bool removeall = true)
{
	bool bfound = false;

	Vector3 v(x,y,z);

	for(long n = 0; n < (long)vector3List.size(); n++)
	{
		if(v == vector3List[n])
		{
			ItemRemove(n);
			if( removeall == false )
			{
				 return true;
			} 
			bfound = true;
		}
	}

	return bfound;
}

bool Vector3Array::ItemRemove(double x, double y, double z)
{
	return ItemRemoveAll(x, y, z ,false);
}

bool Vector3Array::ItemRemove(Vector3& v)
{
	return ItemRemoveAll(v.x, v.y, v.z ,false);
}

bool Vector3Array::ItemRemoveAll(Vector3& v)
{
	return ItemRemoveAll(v.x, v.y, v.z ,true);
}

bool Vector3Array::ItemAdd(double x, double y, double z)
{
	vector3List.push_back( Vector3(x,y,z) );
	return true;
}

bool Vector3Array::ItemAdd(Vector3 v)
{
	vector3List.push_back( v );
	//vector3List.shrink_to_fit();
	return true;
}

bool Vector3Array::ItemUpdate(long index, double x, double y, double z, bool doAdd)
{
	if(vector3List.empty() == false && index >= 0 && index < (long)vector3List.size() )
	{
		//vector<Vector3>::pointer ptr = &vector3List[index];
		vector3List[index].x = x;
		vector3List[index].y = y;
		vector3List[index].z = z;
		return true;
	} else {
		if(doAdd == true)
		{
			ItemAdd(x, y, z);
			return true;
		}
	}

	return false;
}

void Vector3CopyMem(Vector3 *vFrom, Vector3 *vTo)
{
	//memset(vTo,0,sizeof(Vector3));

	 memcpy(vTo, vFrom, sizeof(Vector3));
}

bool Vector3Array::ItemUpdate(long index, Vector3 v, bool doAdd)
{
	if(vector3List.empty() == false && index >= 0 && index < (long)vector3List.size() )
	{
		//vector<Vector3>::pointer ptr = &
		vector3List[index] = v;
		//Vector3CopyMem(&v, ptr);
		return true;
	} else {
		
		if(doAdd == true)
		{
			ItemAdd(v);
			return true;
		}
	}

	return false;
}


/** not part of class */
/** Just like is this way, could make it a private method */
bool SortXOnly(const Vector3& v1, const Vector3& v2)
{
  return v1.x < v2.x;
}

bool SortYOnly(const Vector3& v1, const Vector3& v2)
{
  return v1.y < v2.y;
}

bool SortZOnly(const Vector3& v1, const Vector3& v2)
{
  return v1.z < v2.z;
}

bool SortDOnly(const Vector3& v1, const Vector3& v2)
{
	bool b = &v1 < &v2;
	return b;
}

void Vector3Array::Sort(Vector3ArraySort vector3Sorts)
{
  // Sort the vector using predicate and std::sort
  switch(vector3Sorts)
  {
	 case VECTOR3_SORT_X:
			sort(vector3List.begin(), vector3List.end(), SortXOnly);
			break;

	case VECTOR3_SORT_Y:
			sort(vector3List.begin(), vector3List.end(), SortYOnly);
			break;

	case VECTOR3_SORT_Z:
			sort(vector3List.begin(), vector3List.end(), SortZOnly);
			break;

	case VECTOR3_SORT_DISTANCE:
			sort(vector3List.begin(), vector3List.end(), SortDOnly);
			break;
  }
}

bool Vector3Array::ItemGet(long index, Vector3 &v /** output */)
{	
	if(vector3List.empty() == false && index >= 0 && index < (long)vector3List.size() )
	{
		v = vector3List[index];
		return true;
	}

	return false;
}


/**
  returns vector at index

  @param index	- is the item to return 
  @return Vector3 - if valid index else empty vector
**/
Vector3 Vector3Array::ItemGet(long index)
{	
	if(vector3List.empty() == false && index >= 0 && index < (long)vector3List.size() )
	{
		return vector3List[index];
	}

	/** Return our dummy vector */
	return v3empty;
}


Vector3 Vector3Array::computeBestFitNormal() 
{
	// Zero out sum
 
	Vector3 result(0,0,0);
	int n = vector3List.size() -1;

	// Start with the "previous" vertex as the last one. 
	// This avoids an if-statement in the loop
 
	Vector3 p = vector3List[n - 1];
 
	// Iterate through vertices
 
	for (int i = 0 ; i < n ; ++i) 
	{
		// Get shortcut to the "current" vertex
		Vector3 c = vector3List[i];

		// Add in edge vector products appropriately
		result.x += (p.z + c.z) * (p.y - c.y); 
		result.y += (p.x + c.x) * (p.z - c.z);
		result.z += (p.y + c.y) * (p.x - c.x);
		// Next vertex, please
		p = c; 
	}

	// Normalize the result and return it
	if( result != Vector3(0,0,0))
	{
		int n = 0;
	}
	//if(result  == 0.0.0)
	//than the vectors, were collinear, i.e the point are in the smae line
	// 
	//
	//
	
	return result.normalized();
} 


Vector3 Vector3Array::FindNearestPoint(Vector3 v)
{
	Vector3 Orig = v;
	Vector3 n(v);
	Vector3 vfound;
	double diff = _I32_MAX;

	// This is the real snaping function 'v' has been moved to the nearest point.
	
	double angle = 0;
	double angleNearest = 7; // Max is 2* PI

	for (int j =0; j < Length(); j++)
	{
		Vector3 v1 = ItemGet(j);
		Vector3 v2 = (j>0)?ItemGet(j-1):ItemGet(j);

		//vfound = Vector3::lineNearestPointTo(v1,v2,v);

		vfound = Vector3::GetClosestPointOnLineSegment(v1,v2,v);
		
		angle = vfound.angle(v);
	
		if(angleNearest > angle && vfound != Vector3(0,0,0))
		{
			angleNearest = angle;
			n = vfound;
		}
	}
	v = n;

	for (int j =0; j < Length(); j++)
	{
		Vector3 v1 = ItemGet(j);
		Vector3 v2 = (j>0)?ItemGet(j-1):ItemGet(j);

		vfound = Vector3::lineNearestPointTo(v1,v2,v);

		//vfound = Vector3::GetClosestPointOnLineSegment(v1,v2,v);
		
		angle = vfound.angle(v);
	
		if(angleNearest > angle && vfound != Vector3(0,0,0))
		{
			angleNearest = angle;
			n = vfound;
		}
	}

	//v = n;


	return Vector3(n);
}

// unit3d version 
/*
public Vector3 NearestVertexTo(Vector3 v)
{
    // convert point to local space
    point = transform.InverseTransformPoint(point);

    Mesh mesh = GetComponent<MeshFilter>().mesh;
    float minDistanceSqr = Mathf.Infinity;
    Vector3 nearestVertex = Vector3.zero;

    // scan all vertices to find nearest
    foreach (Vector3 vertex in mesh.vertices)
    {
        Vector3 diff = point-vertex;
        float distSqr = diff.sqrMagnitude;

        if (distSqr < minDistanceSqr)
        {
            minDistanceSqr = distSqr;
            nearestVertex = vertex;
        }
    }

    // convert nearest vertex back to world space
    return transform.TransformPoint(nearestVertex);

}*/
