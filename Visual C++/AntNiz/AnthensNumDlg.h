#if !defined(AFX_ANTHENSNUMDLG_H__0ADD3176_4D7B_11D2_9DA5_00C0DFE53E4F__INCLUDED_)
#define AFX_ANTHENSNUMDLG_H__0ADD3176_4D7B_11D2_9DA5_00C0DFE53E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnthensNumDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnthensNumDlg dialog

class CAnthensNumDlg : public CDialog
{
// Construction
public:
	CAnthensNumDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnthensNumDlg)
	enum { IDD = IDD_DIALOG3 };
	int		m_nAntNum;
	int		m_nStepsNum;
	double	m_dIntPrecision;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnthensNumDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnthensNumDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTHENSNUMDLG_H__0ADD3176_4D7B_11D2_9DA5_00C0DFE53E4F__INCLUDED_)
