/**
* GDI Test application 
*
* Author: Chay Palton
* Date: 23/04/2012
* Copyright: Chay Palton 2012-2012
*/

// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "BSTest.h"
#include "ChildView.h"

//////////////////////////////////////////////////////////////////////////////
// GDI+
using namespace Gdiplus;

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	/*
	* Create an inital test line with some control points.
	*/

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	/*
	 * This 2D application is use as quick unit test.
	 * 
	 * Setup some initial control points in 2D space, as 
	 * this test application is only on a 2D plane.
	 * 
	 * Code added to my 3D application code,
	 * and the spline will curves along X,Y,Z
 	 */

	pointsArray.ItemAdd(100,400, 0);
	pointsArray.ItemAdd(150,400, 0);
	pointsArray.ItemAdd(460,400, 0);

	createBSpline(pointsArray);
}

/**
** Create the editing bspline based on the line with points we can editing.
**
*/
void CChildView::createBSpline(Vector3Array &array)
{
	int maxControlPoints = 1;
	int nControlPoints = 0;
	double yOffset = 0;

	Vector3 first = array.ItemGet(0);
	Vector3 last = array.ItemGet(array.Length()-1);

	double dist = Vector3::distance(first, last);
	double interval = dist/ (maxControlPoints);
	double inc = 0;
	
	first.y -= yOffset;

	bsplineControl.ControlPointAdd(first);

	for(int n = 0; n < maxControlPoints; n++)
	{
		inc += interval;
		bsplineControl.ControlPointAdd( inc, first.y, 0);
	}

	last.y -= yOffset;

	bsplineControl.ControlPointAdd(last);

	bsplineControl.BSplineCreate(); // Auto resolution

	pointEdit(array);
}


void CChildView::pointEdit(Vector3Array &array)
{
	for(int n =1; n <array.Length() - 2; n++)
	{
		array.ItemGet(n);
	}
}


CChildView::~CChildView()
{

	GdiplusShutdown(gdiplusToken);
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
//	ON_WM_MBUTTONDOWN()
//	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

//	createBSpline();

	return TRUE;
}


void CChildView::DrawControlPointInfo(Gdiplus::Graphics* g, int n, int x, int y)
{
	CString msg= L"";
	msg.Format(L"<%d>(%d,%d,%d)",n+1,x,y,0);
	
	Gdiplus::Font myFont(L"Arial", 14);
	PointF origin((Gdiplus::REAL)x - (msg.GetLength() * 14)/2, (Gdiplus::REAL)y -60);
	SolidBrush blackBrush(Color(255, 0, 0, 0));

	g->DrawString(
		msg,
		msg.GetLength(),
		&myFont,
		origin,
		&blackBrush);
}

void CChildView::DrawEditLine(Gdiplus::Graphics* g)
{
	for (int i=0; i < pointsArray.Length(); i++)
	{
		Gdiplus::Pen penRes( Gdiplus::Color(255, 0, 0, 0), (REAL)1);

		g->DrawEllipse(&penRes,
			(INT)pointsArray.ItemGet(i).x-3,
			(INT)pointsArray.ItemGet(i).y-3,
			6, 6);

		Gdiplus::Pen penLine( Gdiplus::Color(255, 0, 0, 255), (REAL)1);

		g->DrawLine(&penLine,(INT)(i>0)?pointsArray.ItemGet(i-1).x:pointsArray.ItemGet(i).x,
											(INT)(i>0)?pointsArray.ItemGet(i-1).y:pointsArray.ItemGet(i).y,
											(INT)pointsArray.ItemGet(i).x,
											(INT)pointsArray.ItemGet(i).y);
	}
}

void CChildView::DrawBSplineAndControlPoints(Gdiplus::Graphics* g)
{
	for (int j =0; j < bsplineControl.BSplineGetPointCount(); j++)
	{
		
		Gdiplus::Pen penRes( Gdiplus::Color(255, 0, 0, 0), (REAL)1);

		g->DrawEllipse(&penRes,
			(INT)bsplineControl.BSplineGetPoint(j).x-3,
			(INT)bsplineControl.BSplineGetPoint(j).y-3,
			6,  6);

		Gdiplus::Pen penLine( Gdiplus::Color(255, 0, 0, 255), (REAL)1);

		g->DrawLine(&penLine,(INT)(j>0)?bsplineControl.BSplineGetPoint(j-1).x:bsplineControl.BSplineGetPoint(j).x,
											(INT)(j>0)?bsplineControl.BSplineGetPoint(j-1).y:bsplineControl.BSplineGetPoint(j).y,
											(INT)bsplineControl.BSplineGetPoint(j).x,
											(INT)bsplineControl.BSplineGetPoint(j).y);
	}	

	for (int i=0; i < bsplineControl.ControlPointGetCount(); i++)
	{
		/// Draw control points
		Gdiplus::Pen penControl( Gdiplus::Color(255, 255, 0, 0), (REAL)1);
		 
		if(bsplineControl.ControlPointGetActiveIndex() == i)
		{
			DrawControlPointInfo(g, i, bsplineControl.ControlPointGet(i).x,(int)bsplineControl.ControlPointGet(i).y);

			switch( bsplineControl.ControlPointGetActiveState())
			{
				case 1:
					penControl.SetColor(Gdiplus::Color(255, 0, 0, 255));
					penControl.SetWidth(1);
					break;
				case 2:
					penControl.SetColor(Gdiplus::Color(255, 255, 0, 0));
					penControl.SetWidth(1);
					break;
			} 
		
			g->DrawEllipse(&penControl,(INT)bsplineControl.ControlPointGet(i).x-20,(int)bsplineControl.ControlPointGet(i).y-20, 40,  40);

		} else {
			penControl.SetColor(Gdiplus::Color(170, 0, 255, 0));
			penControl.SetWidth(8);
		}
	     
		g->DrawEllipse(&penControl,(INT)bsplineControl.ControlPointGet(i).x-8,
												(INT)bsplineControl.ControlPointGet(i).y-8, 16,  16);
	}
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	HDC hDC = dc.m_hDC;
	RECT rc;
	GetClientRect(&rc);

	static int value = 0;

	Graphics graphics(hDC);

	Gdiplus::Bitmap bmp(rc.right - rc.left, rc.bottom - rc.top);
	Gdiplus::Graphics* pBufferGraphics = Graphics::FromImage(&bmp); 
	
	pBufferGraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	pBufferGraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

	SolidBrush colorBackground( Color(255,255,255));
	pBufferGraphics->FillRectangle(&colorBackground, 0, 0, rc.right, rc.bottom );
	
	CString msg = L"BSPLINE 2D TEST APPLICATION\n\n";

	CString msgInstr = L""\
		" - Double click [Left] mouse button to add control point.\n" \
		" - Single click [Right] mouse button on control point to remove.\n" \
		" - Hold down [Left] mouse button and drag to move control point.";
	
	// Initialize arguments.
	Gdiplus::Font font(L"Arial", 16);
	PointF origin(40.0f, 30.0f);
	SolidBrush blackBrush(Color(255, 0, 0, 0));

	// Draw string.
	pBufferGraphics->DrawString(
		msg,
		msg.GetLength(),
		&font,
		origin,
		&blackBrush);

	Gdiplus::Font fontInstr(L"Arial", 12);
	PointF originInstr(40.0f, 120.0f);
	SolidBrush blackBrushInstr(Color(255, 0, 0, 0));

	// Draw string.
	pBufferGraphics->DrawString(
		msgInstr,
		msgInstr.GetLength(),
		&fontInstr,
		originInstr,
		&blackBrushInstr);

	DrawBSplineAndControlPoints(pBufferGraphics);
	graphics.DrawImage(&bmp, rc.left, rc.top);

	delete pBufferGraphics;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( bsplineControl.ControlPointSelect(point.x, point.y , 20) )
	{
		bsplineControl.ControlPointSetActiveState(1);
		Invalidate(FALSE);
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	if( bsplineControl.ControlPointGetActiveIndex() != -1 )
	{
		bsplineControl.ControlPointDeselect(); 
		Invalidate(FALSE);
	}

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if( bsplineControl.ControlPointGetActiveIndex() != -1 )
	{
		if ( bsplineControl.ControlPointUpdate(bsplineControl.ControlPointGetActiveIndex(), point.x, point.y , 0 ))
		{
			bsplineControl.BSplineCreate(); // Auto resolution
			Invalidate(FALSE);
		}

	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if( bsplineControl.ControlPointSelect(point.x, point.y , 20) )
	{
		bsplineControl.ControlPointSetActiveState(2);
		Invalidate(FALSE);
	}

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if( bsplineControl.ControlPointGetActiveIndex() != -1 )
	{
		bsplineControl.ControlPointRemove(bsplineControl.ControlPointGetActiveIndex());
		bsplineControl.BSplineCreate(); // Auto resolution
		bsplineControl.ControlPointDeselect(); 
		Invalidate(FALSE);
	}

	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	bsplineControl.ControlPointAdd(point.x,point.y,0);
	bsplineControl.BSplineCreate(); // Auto resolution
	//bsplineControl.ControlPointSort(VECTOR3_SORT_DISTANCE);
	Invalidate(FALSE);
	CWnd::OnLButtonDblClk(nFlags, point);
}
