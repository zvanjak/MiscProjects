// CodeAnalyzer_MFC_APP.h : main header file for the CodeAnalyzer_MFC_APP application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCodeAnalyzerApp:
// See CodeAnalyzer_MFC_APP.cpp for the implementation of this class
//

class CCodeAnalyzerApp : public CWinApp
{
public:
	CCodeAnalyzerApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCodeAnalyzerApp theApp;