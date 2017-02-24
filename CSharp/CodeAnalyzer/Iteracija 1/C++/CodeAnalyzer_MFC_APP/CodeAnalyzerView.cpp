// CodeAnalyzerView.cpp : implementation of the CCodeAnalyzerView class
//

#include "stdafx.h"
#include "CodeAnalyzer_MFC_APP.h"

#include "CodeAnalyzerDoc.h"
#include "CodeAnalyzerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCodeAnalyzerView

IMPLEMENT_DYNCREATE(CCodeAnalyzerView, CView)

BEGIN_MESSAGE_MAP(CCodeAnalyzerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCodeAnalyzerView construction/destruction

CCodeAnalyzerView::CCodeAnalyzerView()
{
	// TODO: add construction code here

}

CCodeAnalyzerView::~CCodeAnalyzerView()
{
}

BOOL CCodeAnalyzerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCodeAnalyzerView drawing

void CCodeAnalyzerView::OnDraw(CDC* /*pDC*/)
{
	CCodeAnalyzerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCodeAnalyzerView printing

BOOL CCodeAnalyzerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCodeAnalyzerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCodeAnalyzerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCodeAnalyzerView diagnostics

#ifdef _DEBUG
void CCodeAnalyzerView::AssertValid() const
{
	CView::AssertValid();
}

void CCodeAnalyzerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCodeAnalyzerDoc* CCodeAnalyzerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCodeAnalyzerDoc)));
	return (CCodeAnalyzerDoc*)m_pDocument;
}
#endif //_DEBUG


// CCodeAnalyzerView message handlers
