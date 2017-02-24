// JuliaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJuliaDlg dialog

class CJuliaDlg : public CDialog
{
// Construction
public:
	CJuliaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJuliaDlg)
	enum { IDD = IDD_DIALOG4 };
	int		m_nRectHeight;
	int		m_nRectWidth;
	double	m_dCim;
	double	m_dCre;
	double	m_dEps;
	int		m_nMaxIterNum;
	double	m_dX1;
	double	m_dX2;
	double	m_dY1;
	double	m_dY2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJuliaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJuliaDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
