// AdditPointCoord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdditPointCoord dialog

class CAdditPointCoord : public CDialog
{
// Construction
public:
	CAdditPointCoord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdditPointCoord)
	enum { IDD = IDD_DIALOG7 };
	double	m_dT;
	double	m_dX;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdditPointCoord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdditPointCoord)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
