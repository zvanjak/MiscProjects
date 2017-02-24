// BaseZCoord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BaseZCoord dialog

class BaseZCoord : public CDialog
{
// Construction
public:
	BaseZCoord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BaseZCoord)
	enum { IDD = IDD_DIALOG5 };
	double	m_dLowerZCoord;
	double	m_dUpperZCoord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BaseZCoord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BaseZCoord)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
