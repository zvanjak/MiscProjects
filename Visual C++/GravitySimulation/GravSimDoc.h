// GravSimDoc.h : interface of the CGravSimDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAVSIMDOC_H__8DC1CF7F_8DF1_4063_818C_0DBB0857B2F8__INCLUDED_)
#define AFX_GRAVSIMDOC_H__8DC1CF7F_8DF1_4063_818C_0DBB0857B2F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define SAFETY	0.9
#define PGROW	-0.2
#define PSHRNK	-0.25
#define ERRCON	1.89e-4

#define MAXSTP	50000
#define TINY	1e-30

#define SIGN(a,b) ( (b) >= 0.0 ? fabs(a): -fabs(a) )
static double dMaxArg1, dMaxArg2;
#define DMAX(a,b) (dMaxArg1=(a),dMaxArg2=(b),(dMaxArg1)>(dMaxArg2) ? (dMaxArg1) : (dMaxArg2) )

static double dMinArg1, dMinArg2;
#define DMIN(a,b) (dMinArg1=(a),dMinArg2=(b),(dMinArg1)<(dMinArg2) ? (dMinArg1) : (dMinArg2) )

// Povratne vrijednosti funkcija za integraciju
#define		INT_OK								0
#define		STEPSIZE_UNDERFLOW		-1
#define		TO_MANY_STEPS					-2
#define		NO_ALG_SOLUTION				-3

void polint( double xa[], double ya[], int n, double x, double *y, double *dy );


class Vector {
public:
	float	x, y;

public:
	Vector() { x=0; y=0; }
	Vector( float inX, float inY ) { x=inX; y=inY; }

	Vector	operator+(Vector &b) { return Vector(x+b.x,y+b.y); }
	Vector	operator+=(Vector &b) { x+=b.x; y+=b.y; return *this; }

	Vector	operator-(Vector &b) { return Vector(x-b.x,y-b.y); }
	Vector	operator*(float b) { return Vector(x*b,y*b); }
	Vector	operator/(float b) { return Vector(x/b,y/b); }

	float		X() { return x; }
	float		Y() { return y; }

	friend	float Modul( Vector &a );
	friend	float ModulSqr( Vector &a );
};

class Body {
public:
	Vector	Pos;
	Vector	Speed;

	float		Mass;
	float		Density;
	float		Radius;
};

Vector CalcGravForce( Body &b1, Body &b2 );

class CGravSimDoc : public CDocument
{
protected: // create from serialization only
	CGravSimDoc();
	DECLARE_DYNCREATE(CGravSimDoc)

// Attributes
public:
	Body		B[10];

// Operations
public:
	int simple_integrate( double ystart[], int nvar, double x1, double x2, 
				double h, double dxsave, 	double *xp, double **yp, int *nKount,
				void (CGravSimDoc::*derivs)(double, double [], double[]) );
		
	int	 rkqs(double y[], double dydx[], int n, double *x, double htry, 
						double eps, double yscal[], double *hdid, double *hnext,
						void (CGravSimDoc::*derivs)(double, double[], double[]) );

	void rkck(double y[], double dydx[], int n, double x, double h, double yout[],
						double yerr[], void (CGravSimDoc::*derivs)(double, double[], double[]) );

	int  odeint(double ystart[], int nvar, double x1, double x2, 
							double eps, double h1, double hmin, int *nok, int *nbad,
							void (CGravSimDoc::*derivs)(double, double[], double[]),
							int (CGravSimDoc::*rkqs) ( double y[], double dydx[], int n, double *x, double htry, 
												double eps, double yscal[], double *hdid, double *hnext,
												void (CGravSimDoc::*derivs)(double, double[], double[]) ),
							int kmax, int *kount, double *xp, double **yp, double dxsav);

	Vector CalcForceOnBody( int i );

	void		Deriv( double t, double x[], double dxdy[] );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGravSimDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGravSimDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGravSimDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGravSimDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAVSIMDOC_H__8DC1CF7F_8DF1_4063_818C_0DBB0857B2F8__INCLUDED_)

