#pragma once

#pragma once

/**
*
	Original work
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
* Manage a collection Vector3 class
*/

#ifndef __Vector3Array__
#define __Vector3Array__

#include <stdlib.h>
#include <vector>
#include "Vector3.h"

enum Vector3ArraySort {
	VECTOR3_SORT_X = 100,
	VECTOR3_SORT_Y,
	VECTOR3_SORT_Z,
	VECTOR3_SORT_DISTANCE
};

class Vector3Array
{

private:
	
	Vector3 v3empty;
	std::vector<Vector3> vector3List;
public:

	Vector3Array(void);

	~Vector3Array(void);

	bool Vector3Array::ItemGet(long index, Vector3 &v /** output */);

	Vector3 ItemGet(long index);

	bool ItemAdd(Vector3 v);
	bool ItemAdd(double x, double y, double z);

	bool ItemRemove(Vector3& v);
	bool ItemRemoveAll(Vector3& v);
	bool ItemRemove(long index);
	bool ItemRemove(double x, double y, double z);
	bool ItemRemoveAll(double x, double y, double z, bool);

	void Pop();
	void Clear();

	void Sort(Vector3ArraySort vector3Sorts);

	Vector3 NearestVertexTo(Vector3 v);

	long Length();

	bool ItemUpdate(long index, double x, double y, double z, bool);
	bool ItemUpdate(long index, Vector3 v, bool doAdd = true);

	Vector3 computeBestFitNormal();

	Vector3 FindNearestPoint(Vector3 v);

};

#endif