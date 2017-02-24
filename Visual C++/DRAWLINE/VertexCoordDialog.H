// VertexCoordDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VertexCoordDialog dialog

class VertexCoordDialog : public CDialog
{
// Construction
public:
	VertexCoordDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(VertexCoordDialog)
	enum { IDD = IDD_DIALOG2 };
	int		m_nVertNum;
	double	m_dXCoord;
	double	m_dYCoord;
	double	m_dZCoord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VertexCoordDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VertexCoordDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
