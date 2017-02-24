// CodeAnalyzerDoc.cpp : implementation of the CCodeAnalyzerDoc class
//

#include "stdafx.h"
#include "CodeAnalyzer_MFC_APP.h"

#include "CodeAnalyzerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCodeAnalyzerDoc

IMPLEMENT_DYNCREATE(CCodeAnalyzerDoc, CDocument)

BEGIN_MESSAGE_MAP(CCodeAnalyzerDoc, CDocument)
END_MESSAGE_MAP()


// CCodeAnalyzerDoc construction/destruction

CCodeAnalyzerDoc::CCodeAnalyzerDoc()
{
	// TODO: add one-time construction code here

}

CCodeAnalyzerDoc::~CCodeAnalyzerDoc()
{
}

BOOL CCodeAnalyzerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCodeAnalyzerDoc serialization

void CCodeAnalyzerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CCodeAnalyzerDoc diagnostics

#ifdef _DEBUG
void CCodeAnalyzerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCodeAnalyzerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCodeAnalyzerDoc commands
