
// ChildView.h : interface of the CChildView class
//


#pragma once

//#include "BSpline.h"

#include "../BSpline/BSplineControl.h"
#include "../BSpline/Vector3Array.h"
// CChildView window


class CChildView : public CWnd
{
	Vector3Array pointsArray;
	BSplineControl bsplineControl;

	void CChildView::pointEdit(Vector3Array &array);

	void CChildView::createBSpline(Vector3Array &array);
	void DrawEditLine(Gdiplus::Graphics* g);
	void DrawBSplineAndControlPoints(Gdiplus::Graphics* g);
	void DrawControlPointInfo(Gdiplus::Graphics* g, int n, int x, int y);
	//bool SetControlPointActive(CPoint point);
	

// Construction
public:
	CChildView();

	

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

