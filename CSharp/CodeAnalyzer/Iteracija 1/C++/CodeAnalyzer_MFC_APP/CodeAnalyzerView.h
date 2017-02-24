// CodeAnalyzerView.h : interface of the CCodeAnalyzerView class
//


#pragma once


class CCodeAnalyzerView : public CView
{
protected: // create from serialization only
	CCodeAnalyzerView();
	DECLARE_DYNCREATE(CCodeAnalyzerView)

// Attributes
public:
	CCodeAnalyzerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCodeAnalyzerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CodeAnalyzerView.cpp
inline CCodeAnalyzerDoc* CCodeAnalyzerView::GetDocument() const
   { return reinterpret_cast<CCodeAnalyzerDoc*>(m_pDocument); }
#endif

