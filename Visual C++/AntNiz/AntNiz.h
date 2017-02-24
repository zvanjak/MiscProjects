// AntNiz.h : main header file for the ANTNIZ application
//

#if !defined(AFX_ANTNIZ_H__337029B7_4A43_11D2_9D99_00C0DFE53E4F__INCLUDED_)
#define AFX_ANTNIZ_H__337029B7_4A43_11D2_9D99_00C0DFE53E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAntNizApp:
// See AntNiz.cpp for the implementation of this class
//

class CAntNizApp : public CWinApp
{
public:
	CAntNizApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntNizApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAntNizApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTNIZ_H__337029B7_4A43_11D2_9D99_00C0DFE53E4F__INCLUDED_)
