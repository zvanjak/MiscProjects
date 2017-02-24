// GraviSimView.h : interface of the CGravSimView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAVISIMVIEW_H__324087EA_FDED_4E93_BE1D_144883DBF8C1__INCLUDED_)
#define AFX_GRAVISIMVIEW_H__324087EA_FDED_4E93_BE1D_144883DBF8C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGravSimView : public CView
{
protected: // create from serialization only
	CGravSimView();
	DECLARE_DYNCREATE(CGravSimView)

// Attributes
public:
	CGravSimDoc* GetDocument();

	bool	bStartSim;

	void	DrawAllBodies( CDC *pDC );

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGravSimView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGravSimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGravSimView)
	afx_msg void OnStartSimulation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GravSimView.cpp
inline CGravSimDoc* CGravSimView::GetDocument()
   { return (CGravSimDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAVISIMVIEW_H__324087EA_FDED_4E93_BE1D_144883DBF8C1__INCLUDED_)
