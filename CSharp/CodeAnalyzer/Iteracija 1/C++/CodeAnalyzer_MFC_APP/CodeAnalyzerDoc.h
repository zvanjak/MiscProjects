// CodeAnalyzerDoc.h : interface of the CCodeAnalyzerDoc class
//


#pragma once


class CCodeAnalyzerDoc : public CDocument
{
protected: // create from serialization only
	CCodeAnalyzerDoc();
	DECLARE_DYNCREATE(CCodeAnalyzerDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CCodeAnalyzerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


