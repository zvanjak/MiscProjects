#if !defined(AFX_ENTERCOEF_H__5CE220D3_4A56_11D2_9D9A_00C0DFE53E4F__INCLUDED_)
#define AFX_ENTERCOEF_H__5CE220D3_4A56_11D2_9D9A_00C0DFE53E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnterCoef.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnterCoef dialog

class CEnterCoef : public CDialog
{
// Construction
public:
	CEnterCoef(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnterCoef)
	enum { IDD = IDD_DIALOG1 };
	double	m_dA0;
	double	m_dA1;
	double	m_dA2;
	double	m_dA3;
	double	m_dA4;
	double	m_dA5;
	double	m_dA6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterCoef)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnterCoef)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTERCOEF_H__5CE220D3_4A56_11D2_9D9A_00C0DFE53E4F__INCLUDED_)
