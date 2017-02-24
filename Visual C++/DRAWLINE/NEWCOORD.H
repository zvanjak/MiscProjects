// NewCoord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewCoord dialog

class CNewCoord : public CDialog
{
// Construction
public:
	CNewCoord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewCoord)
	enum { IDD = IDD_DIALOG9 };
	double	m_dX;
	double	m_dY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCoord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewCoord)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
