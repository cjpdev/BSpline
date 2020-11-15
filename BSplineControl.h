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
* Generate a spline base on a number of control points
* 2 to n points can ne used, class also handle one point
* Date: 23/04/2012
*/

/**
* Manage the control on and editable Bspline
*
* Author: Chay Palton
* Date: 23/04/2012
*/


#include "BSpline.h"
#include "Vector3Array.h"

typedef enum  Vector3ArraySort BSplineControlSort;

class BSplineControl
{

private:

	//int nResolution;						// number spline point output

	Vector3Array controlPoints;
	Vector3Array splinePoints;
	

	// Allow the vector to be accessed even while its being updated, this will allow a morph effect as new controls, and sp point are added or removed.
	// NOTE: We do not handle removel yet
	int nControlPoints;	 // Keep a record of the points, currently we do not resize the vector array if it get smaller. 
	int nSplinePoints;	 // Keep a record of the points, currently we do not resize the vector array if it get smaller. 

	BSpline bspline;					// BSpline creation class

	long activeControlIndex;
	int activeControlState;
public:

	/*
	 * Get the best norm for controlpoints
	 */
	Vector3 ControlPointsNorm();
	
	Vector3 ControlPointGet(long index);
	void ControlPointAdd(Vector3 v);
	void ControlPointAdd(double x, double y, double z);
	bool ControlPointRemove(long index);
	bool ControlPointRemove(double x, double y, double z);

	bool ControlPointSelect(double x, double y, double size );
	bool ControlPointUpdate(long index, double x, double y , double z);

	void ControlPointFinalize(long nItem);

	void ControlPointSetActiveIndex(int n, int state);
	void ControlPointSetActiveState(int state);
	int ControlPointGetActiveState();
	int ControlPointGetActiveIndex();

	long ControlPointGetCount();

	void BSplineCreate(double minDistance = 1.0f);
	void BSplineCreate(int nResolution, double minDistance = 1.0f);
	Vector3 BSplineFindNearestPoint(Vector3 v, bool Online);
	 
	Vector3 BSplineGetPoint(long index);

	long BSplineGetPointCount();

	void ControlPointDeselect();

	void BSplineSort(BSplineControlSort sortmode);
	void ControlPointSort(BSplineControlSort sortmode);

public:
	BSplineControl(void);
	~BSplineControl(void);


};

