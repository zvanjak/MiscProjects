// WhichPoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWhichPoint dialog

class CWhichPoint : public CDialog
{
// Construction
public:
	CWhichPoint(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWhichPoint)
	enum { IDD = IDD_DIALOG8 };
	int		m_nVertNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhichPoint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWhichPoint)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
