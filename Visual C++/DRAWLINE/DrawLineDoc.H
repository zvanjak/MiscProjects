// DrawLineDoc.h : interface of the CDrawLineDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CDrawLineDoc : public CDocument
{
private:
	UINT	m_nExerciseNum;
	
	CPoint	m_VertexPos[20];
	double	m_dUpperZ, m_dLowerZ;
	int		m_nVertexNum;

	struct BODY		m_Body;
	
	BOOL	m_bWaitMouseClick;
	BOOL	m_bDrawOK;

protected: // create from serialization only
	CDrawLineDoc();
	DECLARE_DYNCREATE(CDrawLineDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawLineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawLineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void	AddMouseCoord( CPoint point );
	void	LastMouseCoord( CPoint point );
	void	CheckPoint( CPoint point );
	
	CPoint	GetVertexCoord( UINT nNum );
	void	ResetVertexCoord( void );
	UINT	GetVertexNum( void );

	UINT	GetExerciseNum( void );
	void	SetExercise( int i );
	BOOL	ReadyToDraw( void );

	void	SetZCoords( void );
	void	SetBodyData( void );
	void	CheckPoint( void );

	int			GetBodyVertNum( void );
	BODY_POLY	GetPoly( int i );
	BODY_EDGE	GetEdge( int i );
	VERTEX		GetVert( int i );

	void		SetPolyVisibility( int poly, int vis );
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawLineDoc)
	afx_msg void OnExercDrawline();
	afx_msg void OnExercDrawConvexPoly();
	afx_msg void OnExercDrawPoly();
	afx_msg void OnCheckPointBody();
	afx_msg void OnBezierFunc();
	afx_msg void OnQuadFunc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
