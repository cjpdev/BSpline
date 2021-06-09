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
* Generate 2D or 3D spline base on (N) number of control points
* 2 to n points can be used. This class also handle one point
* Date: 23/04/2012
*/

/**
* Manage the control on an editable Bspline
*
* Author: Chay Palton
* Date: 23/04/2012
*/

#include "BSplineControl.h"
#include "limits.h"

BSplineControl::BSplineControl(void)
{
	nSplinePoints = 0;
	nControlPoints = 0;
	activeControlIndex = -1;
	activeControlState = 0;
}

BSplineControl::~BSplineControl(void)
{
}

bool BSplineControl::ControlPointRemove(long index)
{
	bool bResult = controlPoints.ItemRemove(index);
	nControlPoints = controlPoints.Length();
	return bResult;
}

bool BSplineControl::ControlPointRemove(double x, double y, double z)
{
	bool bResult = controlPoints.ItemRemove(x,y,z);
	nControlPoints = controlPoints.Length();
	return bResult;
}

void BSplineControl::ControlPointAdd(Vector3 v)
{
	controlPoints.ItemAdd(v);
	nControlPoints = controlPoints.Length();
}


void BSplineControl::ControlPointAdd(double x, double y, double z)
{
	controlPoints.ItemAdd(x,y,z);
	nControlPoints = controlPoints.Length();
}

long BSplineControl::BSplineGetPointCount()
{
	return nSplinePoints;
}

long BSplineControl::ControlPointGetCount()
{
	return nControlPoints;
}

/***
** Access the generated spline data
**
*/
Vector3 BSplineControl::ControlPointGet(long index)
{
	return controlPoints.ItemGet(index);
}

/***
** Access the generated spline data
**
*/
Vector3 BSplineControl::BSplineGetPoint(long index)
{
	return splinePoints.ItemGet(index);
}

void BSplineControl::BSplineCreate(int nResolution, double minDistance)
{
	nSplinePoints = bspline.create(controlPoints, splinePoints , 4 , nResolution, minDistance);
}

/**
 ** Auto set up resolution
 **
 */
void BSplineControl::BSplineCreate(double minDistance)
{
	double	nResolution = 0;
	int t = 10;

	int len = controlPoints.Length();

	for(int n = 0; n < len; n++)
	{
		double d =  Vector3::distance( controlPoints.ItemGet(n), controlPoints.ItemGet(n+1));
		nResolution += (int)d;
	}

	if( len > 0)
	{
		nResolution = nResolution / t;
	} else {
		nResolution = 0;
	}


	/**
	** ??? When creating a bSpline to render to screen, the resolution and distances will aways make sence, they are always limited to a min of (1), i.e 1 pixel
	** But creating a BSpline to render to 3D editors, the distances can be very small less the zero, eg 0.001;
	**/
	if( nResolution < 20)
	{
		nResolution = 100;
	}

	BSplineCreate((int)nResolution, minDistance);
}

void BSplineControl::ControlPointFinalize(long nItem)
{
	if( nItem <= controlPoints.Length() )
	{
		nControlPoints = nItem;
	}
}

bool BSplineControl::ControlPointUpdate(long index, double x, double y, double z)
{
	if(index >= 0 && index < controlPoints.Length())
	{
		if( controlPoints.ItemGet(index).x != x || controlPoints.ItemGet(index).y != y || controlPoints.ItemGet(index).z != z)
		{
			controlPoints.ItemUpdate(index, x, y , z, false);
			nControlPoints = controlPoints.Length();
			return true;
		}
	} else {
		controlPoints.ItemAdd(x, y , z);
		nControlPoints = controlPoints.Length();
	}
	return false;
}

int BSplineControl::ControlPointGetActiveIndex()
{
	return activeControlIndex;
}

void BSplineControl::ControlPointSetActiveIndex(int n, int state)
{
	activeControlIndex = n;
	activeControlState = state;
}

void BSplineControl::ControlPointDeselect()
{
	activeControlIndex = -1;
	activeControlState = 0;
}

void BSplineControl::ControlPointSetActiveState(int state)
{
	activeControlState = state;
}

int BSplineControl::ControlPointGetActiveState()
{
	return activeControlState;
}

bool BSplineControl::ControlPointSelect(double x, double y, double size)
{
	bool bActive = false;

	for(int n = 0; n < ControlPointGetCount(); n++)
	{
		if( bActive == false)
		{
			if(x > controlPoints.ItemGet(n).x - size  && x < controlPoints.ItemGet(n).x + size)
			{
				if(y > controlPoints.ItemGet(n).y - size && y < controlPoints.ItemGet(n).y + size)
				{
					activeControlIndex = n;
					bActive = true;
					activeControlState = 0;
					return true;
				}
			}
		}
 	}

	ControlPointDeselect();
	return false;
}


void BSplineControl::BSplineSort(BSplineControlSort sortmode)
{
	splinePoints.Sort(sortmode);
}

void BSplineControl::ControlPointSort(BSplineControlSort sortmode)
{
	controlPoints.Sort(sortmode);
}


Vector3 BSplineControl::ControlPointsNorm()
{
	return controlPoints.computeBestFitNormal();
}

Vector3 BSplineControl::BSplineFindNearestPoint(Vector3 v, bool onLine)
{
	return splinePoints.FindNearestPoint(v);
}