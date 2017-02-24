// AntNizDoc.h : interface of the CAntNizDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANTNIZDOC_H__337029BF_4A43_11D2_9D99_00C0DFE53E4F__INCLUDED_)
#define AFX_ANTNIZDOC_H__337029BF_4A43_11D2_9D99_00C0DFE53E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	MAX_COEF	7
#define	MAX_ANTENS	50


class CAntNizDoc : public CDocument
{
protected: // create from serialization only
	CAntNizDoc();
	DECLARE_DYNCREATE(CAntNizDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntNizDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAntNizDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAntNizDoc)
	afx_msg void OnZadajFunkciju();
	afx_msg void OnIspisiKoeficijente();
	afx_msg void OnPromijeniBrojAntena();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	double	FuncCoef( double x);
	double	FuncInterpolated( double x );

	void		CalculateFourierCoef( void );

	double	FuncCos( double x );
	double	FuncSin( double x );
	double	CalcFourierSum( double phi );
	double	trapzd( double (CAntNizDoc::*func) (double), double a, double b, int n );
	double  qromb( double (CAntNizDoc::*func)(double), double a, double b );
	double	qsimp( double (CAntNizDoc::*func)(double), double a, double b );

public:
	BOOL		m_bIsFuncDefined;
	enum		{ FUNC_COEF, FUNC_INTERPOLATED } m_eFuncType;
	int			m_nAnthensNum;
	int			m_nSteps;
	double	m_dIntPrecision;

private:
	double	*m_adFuncInterpolatedVal;
	double	*m_adFuncInterpolatedX;
	int			m_nFuncInterpolatedPointsNum;
	
	int			m_nM;		// oznaèava koji se koeficijent trenutno izraèunava
	
	double	m_adFuncCoef[MAX_COEF];
	double	m_adCoefB[MAX_ANTENS];
	double	m_adCoefA[MAX_ANTENS];
};


#define M_PI	3.141593

void polint( double xa[], double ya[], int n, double x, double *y, double *dy );

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTNIZDOC_H__337029BF_4A43_11D2_9D99_00C0DFE53E4F__INCLUDED_)

