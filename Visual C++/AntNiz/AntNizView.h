// AntNizView.h : interface of the CAntNizView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANTNIZVIEW_H__337029C1_4A43_11D2_9D99_00C0DFE53E4F__INCLUDED_)
#define AFX_ANTNIZVIEW_H__337029C1_4A43_11D2_9D99_00C0DFE53E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAntNizView : public CView
{
protected: // create from serialization only
	CAntNizView();
	DECLARE_DYNCREATE(CAntNizView)

// Attributes
public:
	CAntNizDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntNizView)
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
	virtual ~CAntNizView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAntNizView)
	afx_msg void OnPolarLog();
	afx_msg void OnUpdatePolarLog(CCmdUI* pCmdUI);
	afx_msg void OnPolarNorm();
	afx_msg void OnUpdatePolarNorm(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	enum		{ POLAR_LOG, POLAR_NORM } m_ePlotType;
};

#ifndef _DEBUG  // debug version in AntNizView.cpp
inline CAntNizDoc* CAntNizView::GetDocument()
   { return (CAntNizDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTNIZVIEW_H__337029C1_4A43_11D2_9D99_00C0DFE53E4F__INCLUDED_)
