
// BSTest.h : main header file for the BSTest application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBSTestApp:
// See BSTest.cpp for the implementation of this class
//

class CBSTestApp : public CWinApp
{
public:
	CBSTestApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBSTestApp theApp;
