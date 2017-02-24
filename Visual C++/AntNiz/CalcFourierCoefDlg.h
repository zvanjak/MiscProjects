#if !defined(AFX_CALCFOURIERCOEFDLG_H__73B65ED3_4B1F_11D2_9D9F_00C0DFE53E4F__INCLUDED_)
#define AFX_CALCFOURIERCOEFDLG_H__73B65ED3_4B1F_11D2_9D9F_00C0DFE53E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalcFourierCoefDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalcFourierCoefDlg dialog

class CCalcFourierCoefDlg : public CDialog
{
// Construction
public:
	CCalcFourierCoefDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalcFourierCoefDlg)
	enum { IDD = IDD_DIALOG2 };
	CListBox	m_ctrlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalcFourierCoefDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalcFourierCoefDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCFOURIERCOEFDLG_H__73B65ED3_4B1F_11D2_9D9F_00C0DFE53E4F__INCLUDED_)
