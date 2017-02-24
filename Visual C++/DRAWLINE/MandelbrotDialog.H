// MandelbrotDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MandelbrotDialog dialog

class MandelbrotDialog : public CDialog
{
// Construction
public:
	MandelbrotDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MandelbrotDialog)
	enum { IDD = IDD_DIALOG3 };
	double	m_dEps;
	int		m_nMaxIterNum;
	double	m_dX1;
	double	m_dX2;
	double	m_dY1;
	double	m_dY2;
	int		m_nRectHeight;
	int		m_nRectWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MandelbrotDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MandelbrotDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
