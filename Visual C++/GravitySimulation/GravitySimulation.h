// GravitySimulation.h : main header file for the GRAVITYSIMULATION application
//

#if !defined(AFX_GRAVITYSIMULATION_H__7C20DA13_0C94_437F_BEB5_DD5AF254FC73__INCLUDED_)
#define AFX_GRAVITYSIMULATION_H__7C20DA13_0C94_437F_BEB5_DD5AF254FC73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGravSimApp:
// See GravitySimulation.cpp for the implementation of this class
//

class CGravSimApp : public CWinApp
{
public:
	CGravSimApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGravSimApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CGravSimApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAVITYSIMULATION_H__7C20DA13_0C94_437F_BEB5_DD5AF254FC73__INCLUDED_)
