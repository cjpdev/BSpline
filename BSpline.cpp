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


#include "BSpline.h"


BSpline::BSpline(void)
{
}


BSpline::~BSpline(void)
{
}

inline double blend(int k, int t, int *u, double v)  // calculate the blending value
{
  double value;

  if (t==1)			// base case for the recursion
  {
    if ((u[k]<=v) && (v<u[k+1]))
      value=1;
    else
      value=0;
  }
  else
  {
    if ((u[k+t-1]==u[k]) && (u[k+t]==u[k+1]))  // check for divide by zero
      value = 0;
    else
    if (u[k+t-1]==u[k]) // if a term's denominator is zero,use just the other
      value = (u[k+t] - v) / (u[k+t] - u[k+1]) * blend(k+1, t-1, u, v);
    else
    if (u[k+t]==u[k+1])
      value = (v - u[k]) / (u[k+t-1] - u[k]) * blend(k, t-1, u, v);
    else
      value = (v - u[k]) / (u[k+t-1] - u[k]) * blend(k, t-1, u, v) +
	      (u[k+t] - v) / (u[k+t] - u[k+1]) * blend(k+1, t-1, u, v);
  }

  return value;
}

inline void compute_intervals(int *u, int n, int t)   // figure out the knots
{
  int j;

  for (j=0; j<=n+t; j++)
  {
    if (j<t)
      u[j]=0;
    else
    if ((t<=j) && (j<=n))
      u[j]=j-t+1;
    else
    if (j>n)
      u[j]=n-t+2;  // if n-t=-2 then we're screwed, everything goes to 0
  }
}

inline Vector3 getPoint(Vector3Array& controlPoints,int max, int index)
{
	if(index > max)
	{
		return controlPoints.ItemGet(max);
	} else {
		return controlPoints.ItemGet(index);
	}
}

inline void compute_point(int *u, int n, int m, int t, double v, Vector3Array& controlPoints, Vector3 *calcxyz)
{
	int k;
	double temp = 0;

	// initialize the variables that will hold our outputted point
	calcxyz->x=0;
	calcxyz->y=0;
	calcxyz->z=0;

	for (k=0; k<=n; k++)
	{
		temp = blend(k,t,u,v);  // same blend is used for each dimension coordinate
		calcxyz->x = calcxyz->x + getPoint(controlPoints,m,k).x * temp;
		calcxyz->y = calcxyz->y + getPoint(controlPoints,m,k).y * temp;
		calcxyz->z = calcxyz->z + getPoint(controlPoints,m,k).z * temp;
	}
}

int BSpline::create(Vector3Array& controlPoints, Vector3Array& splinePoints, int t , int nResolution, double minDistance)
{
  int *u;
  
 
  int m = controlPoints.Length() -1;
  int n = m;
  double increment = 0;
  double interval = 0;
  int out = 0;

  switch(n)
  {
	case 2: m = 2; n = 3; break;
	case 1: 
		out = 2;
		splinePoints.ItemUpdate(0, controlPoints.ItemGet(0), true);
		splinePoints.ItemUpdate(1, controlPoints.ItemGet(1), true);
		return 2;
	case 0:
		return 0;
  }

  Vector3 calcxyz;
  
  u=new int[n+t+1];

  compute_intervals(u, n, t);

  increment=(double) (n - t + 2) / (nResolution-1);  // how much parameter goes up each time
  
  for (int j=0; j < nResolution-1; j++)
  {
    compute_point(u, n, m, t, interval, controlPoints, &calcxyz);
	
	Vector3 vlimit(calcxyz.x , calcxyz.y , calcxyz.z);

	if(!(j > 0 && Vector3::distance(vlimit, splinePoints.ItemGet(out-1)) < minDistance))
	{
		splinePoints.ItemUpdate(out, calcxyz.x , calcxyz.y , calcxyz.z, true);
		out++;
	}
	
	interval += increment;  // increment our parameter

  }

  splinePoints.ItemUpdate(out, controlPoints.ItemGet(m).x , controlPoints.ItemGet(m).y , controlPoints.ItemGet(m).z, true);
  out++;
  delete u;

  return out;
}
