// PointCoordDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointCoordDialog dialog

class CPointCoordDialog : public CDialog
{
// Construction
public:
	CPointCoordDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPointCoordDialog)
	enum { IDD = IDD_DIALOG6 };
	double	m_dXCoord;
	double	m_dYCoord;
	double	m_dZCoord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointCoordDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointCoordDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
