// DrawLineView.h : interface of the CDrawLineView class
//
/////////////////////////////////////////////////////////////////////////////

CPoint	TransfToPoint( double *point, Matrix *T );
CPoint	TransfVertexToPoint( VERTEX point, Matrix *T );
double	Fact( int n );

class CDrawLineView : public CView
{
private:
	BOOL	m_bSettingLines;
	BOOL	m_bFirstMouseClick;
	BOOL	m_bCheckPointInPolygon;
	BOOL	m_bHiddenLines;
	
	CPoint	m_PrevMousePos;
	CPoint	m_CurrentMousePos;
	CPoint	m_CheckPoint;
	VERTEX	m_AdditPoint;
	double	m_dAdditPointT;

	double	EyeX, EyeY, EyeZ;
	double	Alpha, Theta, Rho;
	
	Vector	vect;

	struct	FRACTAL		m_Fract;

protected: // create from serialization only
	CDrawLineView();
	DECLARE_DYNCREATE(CDrawLineView)

// Attributes
public:
	CDrawLineDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawLineView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void DrawLine( CDC* pDC, int x1, int y1, int x2, int y2, COLORREF Color );
	void DrawConvexPoly( CDC *pDC, int N, struct VERTEX *V );
	void DrawPolygon( CDC *pDC, int N, struct VERTEX *V );

	void DrawQuadFunc( CDC *pDC, double t0, double t2, double t3, struct VERTEX *V );
	void DrawBezier( CDC *pDC, int nVertexNum, struct VERTEX *V );

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawLineView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateHiddenLines(CCmdUI* pCmdUI);
	afx_msg void OnHiddenLines();
	afx_msg void OnDrawJuliaSet();
	afx_msg void OnDrawMandelbrtoSet();
	afx_msg void OnCubicFunc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DrawLineView.cpp
inline CDrawLineDoc* CDrawLineView::GetDocument()
   { return (CDrawLineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

void DrawQuadFunc( CDC *pDC, double t0, double t2, double t3, struct VERTEX *V );
