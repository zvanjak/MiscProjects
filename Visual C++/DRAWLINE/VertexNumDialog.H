// VertexNumDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VertexNumDialog dialog

class VertexNumDialog : public CDialog
{
// Construction
public:
	VertexNumDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(VertexNumDialog)
	enum { IDD = IDD_DIALOG1 };
	int		m_nVertexNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VertexNumDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VertexNumDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
