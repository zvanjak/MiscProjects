// GravSimDoc.cpp : implementation of the CGravSimDoc class
//

#include "stdafx.h"
#include "GravitySimulation.h"

#include "GravSimDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGravSimDoc

IMPLEMENT_DYNCREATE(CGravSimDoc, CDocument)

BEGIN_MESSAGE_MAP(CGravSimDoc, CDocument)
	//{{AFX_MSG_MAP(CGravSimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGravSimDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CGravSimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IGravitySimulation to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {4BB2307F-4C0F-4EE4-AA6C-AD43469D70A8}
static const IID IID_IGravitySimulation =
{ 0x4bb2307f, 0x4c0f, 0x4ee4, { 0xaa, 0x6c, 0xad, 0x43, 0x46, 0x9d, 0x70, 0xa8 } };

BEGIN_INTERFACE_MAP(CGravSimDoc, CDocument)
	INTERFACE_PART(CGravSimDoc, IID_IGravitySimulation, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGravSimDoc construction/destruction

CGravSimDoc::CGravSimDoc()
{
	// TODO: add one-time construction code here
	int			i;
	float		x, y, vx, vy;

	for( i=0; i<10; i++ )
	{
		B[i].Mass		 = (float) (rand() % 1000 + 100) / 10;
		B[i].Density = (float) (rand() % 10000 + 100) / 1000;
		B[i].Radius  = (float) pow(3.f/4 * B[i].Mass / B[i].Density / 3.14159F, 1.f/3 );

		x = (float) (rand() % 1000);
		y = (float) (rand() % 700);
		B[i].Pos = Vector(x,y);

		vx = (float) (rand() % 100) / 1500;
		vy = (float) (rand() % 100) / 1500;
		B[i].Speed = Vector(vx,vx);
	}

	EnableAutomation();

	AfxOleLockApp();
}

CGravSimDoc::~CGravSimDoc()
{
	AfxOleUnlockApp();
}

BOOL CGravSimDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGravSimDoc serialization

void CGravSimDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CGravSimDoc diagnostics

#ifdef _DEBUG
void CGravSimDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGravSimDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGravSimDoc commands

Vector CGravSimDoc::CalcForceOnBody( int i )
{
	int			j;
	Vector	force(0,0);

	if( i>=0 && i<10 ) {
		for( j=0; j<10; j++ ) {
			if( i!=j ) {
				force += CalcGravForce(B[i],B[j]);
			}
		}
			return force;
	}
	else
		return force;
}

/////////////////////////////////////////////////////////////////////////////
float	Modul( Vector &a )
{
	return (float) sqrt(fabs(a.x*a.x + a.y*a.y));
}

float ModulSqr( Vector &a )
{
	return (float) fabs(a.x*a.x + a.y*a.y);
}

Vector CalcGravForce( Body &b1, Body &b2 )
{
	float	d;

	d = Modul(b1.Pos-b2.Pos);			// izraèunamo udaljenost meðu tijelima

	return (b1.Pos-b2.Pos) * (-1) * b1.Mass*b2.Mass * (1 / (d*d*d));
}

/////////////////////////////////////////////////////////////////////////////

void	CGravSimDoc::Deriv( double t, double x[], double dxdt[] )
{
	int			i;
	Vector	force;

	// postavi sve pozicije tijela na nove vrijednosti
	for( i=0; i<10; i++ ) {
		B[i].Pos.x = x[i*4+2];
		B[i].Pos.y = x[i*4+3];
	}
	for( i=0; i<10; i++ ) {
		B[i].Speed.x = x[i*4];
		B[i].Speed.y = x[i*4+1];
	}

	for( i=0; i<10; i++ ) {
		force = CalcForceOnBody(i);
		
		dxdt[i*4]		= 1 / B[i].Mass * force.X();
		dxdt[i*4+1] = 1 / B[i].Mass * force.Y();
		dxdt[i*4+2] = x[i*4];
		dxdt[i*4+3] = x[i*4+1];
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************/
//							Simple ODE integration
/****************************************************************/

int CGravSimDoc::rkqs( double y[], double dydx[], int n, double *x, double htry, 
					 double eps, double yscal[], double *hdid, double *hnext,
					 void (CGravSimDoc::*derivs)(double, double[], double[]) )
/*	RK 5-og reda sa pracenjem lokalne greske zaokruzivanja da bi se osigurala tocnost i 
	prilagodila duljina koraka.
	ULAZ:
		vektor zavisnih varijabli  -  y[1..n]
		i njegove derivacije   -  dydx[1..n],   i to u pocetnoj tocki nezavisne varijable x
		duljina koraka(pocetna za probu)  -  htry
		zahtijevana tocnost	 -  eps
		i vektor sa kojim se skalira greska  -  yscal[1..n]
	IZLAZ:
		y i x -  zamijenjeni sa novim vrijednostima
		hdid  -  postignuta duljina koraka
		hnext -  predvidjena duljina koraka u slijedecem koraku

	(*derivs) - korisnicka rutina koja racuna derivacije (desne strane sistema jednadzbi)
	
	Primjer za derivs:

	dy1/dx = f1(x,y1,y2)
	dy2/dx = f2(x,y1,y2)

	void System(double x, double *y, double *dxdy )
	{
		dxdy[0] = f1(x, y[0], y[1] );
		dxdy[1] = f2(x, y[0], y[1] );
	}
*/
{
	int			i;
	double	errmax, h, htemp, xnew;
	double	*yerr, *ytemp;

	yerr = new double[n];
	ytemp = new double[n];
	h = htry;

	for(;;)
	{
		rkck(y,dydx,n,*x,h,ytemp,yerr,derivs);
		errmax = 0.0;
		for( i=0; i<n; i++ )
			errmax = DMAX(errmax, fabs(yerr[i]/yscal[i]));
		errmax /= eps;

		if( errmax <= 1.0 )
			break;

		htemp = SAFETY * h * pow(errmax,PSHRNK);
		h = (h >= 0.0 ? DMAX(htemp, 0.1*h) : DMIN(htemp, 0.1*h));

		xnew = (*x) + h;
		if( xnew == *x )
		{
			fprintf(stderr, "\n stepsize underflow in rkqs!!!");

			return STEPSIZE_UNDERFLOW;
		}
	}
	if( errmax > ERRCON )
		*hnext = SAFETY * h * pow(errmax, PGROW);
	else
		*hnext = 5.0 * h;

	*x += (*hdid=h);
	for( i=0; i<n; i++ )
		y[i] = ytemp[i];
	
	delete [] ytemp;
	delete []yerr;

	return INT_OK;
}

//	Algoritam rutina na RK-metodu
//	implementira osnovnu formulu metodu i pocinjuci od zavisnih varijabli y[i] u x
//	racuna y u x+h
void CGravSimDoc::rkck( double y[], double dydx[], int n, double x, double h, double yout[],
		   double yerr[], void (CGravSimDoc::*derivs)(double, double[], double[]) )
/*
	Dobivsi vrijednosti za n varijabli y[1..n] i njihovih derivacija 
	dydx[1..n] poznatih u x, koristi cash-Karpovu RK metodu da napreduje 
	s rijesenjem preko intervala h i vraca varijable u yout[1..n]
	Takodjer vraca lokalnu gresku zaokruzivanja u yerr
*/
{
	int		i;
	static double a2=0.2, a3=0.3, a4=0.6, a5=1, a6=0.875, 
		b21=0.2, b31=3.0/40.0, b32=9.0/40.0, b41=0.3, b42=-0.9, b43=1.2,
		b51=-11.0/54.0, b52=2.5, b53=-70.0/27.0, b54=35.0/27.0,
		b61=1631.0/55296.0, b62=175.0/512.0, b63=575.0/13824.0,
		b64=44275.0/110592.0, b65=253.0/4096.0, 
		c1=37.0/378.0, c3=250.0/621.0, c4=125.0/594.0, c6=512.0/1771.0,
		dc5=-277.00/14336.0;
	double	dc1=c1-2825.0/27648.0, dc3=c3-18575.0/48384.0,
		dc4=c4-13525.0/55296.0, dc6=c6-0.25;

	double	*ak2, *ak3, *ak4, *ak5, *ak6, *ytemp;
	
	ak2 = new double[n];
	ak3 = new double[n];
	ak4 = new double[n];
	ak5 = new double[n];
	ak6 = new double[n];
	ytemp = new double[n];

	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + b21*h*dydx[i];

	(this->*derivs)(x+a2*h, ytemp, ak2);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b31*dydx[i] + b32*ak2[i]);

	(this->*derivs)(x+a3*h, ytemp, ak3);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b41*dydx[i] + b42*ak2[i] + b43*ak3[i]);

	(this->*derivs)(x+a4*h, ytemp, ak4);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b51*dydx[i] + b52*ak2[i] + b53*ak3[i] + b54*ak4[i]);

	(this->*derivs)(x+a5*h, ytemp, ak5);
	for( i=0; i<n; i++ )
		ytemp[i] = y[i] + h*(b61*dydx[i] + b62*ak2[i] + b63*ak3[i] + b64*ak4[i] + b65*ak5[i]);

	(this->*derivs)(x+a6*h, ytemp, ak6);
	for( i=0; i<n; i++ )
		yout[i] = y[i] + h*(c1*dydx[i] + c3*ak3[i] + c4*ak4[i] + c6*ak6[i]);

	for( i=0; i<n; i++ )
		yerr[i] = h*(dc1*dydx[i] + dc3*ak3[i] + dc4*ak4[i] + dc5*ak5[i] + dc6*ak6[i]);

	delete []ak2;
	delete []ak3;
	delete []ak4;
	delete []ak5;
	delete []ak6;
	delete []ytemp;
}

int CGravSimDoc::odeint( double ystart[], int nvar, double x1, double x2, 
						double eps, double h1, double hmin, int *nok, int *nbad,
						void (CGravSimDoc::*derivs)(double, double[], double[]),
	 
						int (CGravSimDoc::*rkqs)( double y[], double dydx[], int n, double *x, double htry, 
											double eps, double yscal[], double *hdid, double *hnext,
											void (CGravSimDoc::*derivs)(double, double[], double[]) ),
	 
						int kmax, int *kount, double *xp, double **yp, double dxsav)
//	ystart[] - vektor poèetnih vrijednosti
//  nvar  - koliko ima dif. jednadžbi
//  nok, nbad - broj dobrih i loših poduzetih koraka
//  h1 - poèetna duljina koraka
//  hmin - minimalna dozvoljena duljina koraka ( može biti 0 )
//  derivs - korisnikova rutina koja raèuna derivacije u danoj toèki
//  rkqs - stepper rutina
//  kmax - koliko maksimalno izraèunatih vrijednosti y da se zapatmi
//  dxsav - razmak izmeðu dvije vrijednosti koje su zapamæene
//		POVRATNE VRIJEDNOSTI
//  xp[1..kmax] - u kojim toèkama su izraèunate vrijednosti y
//  yp[1..nvar][1..kmax] - vrijednosti varijabli
{
	int		nstp, i;
	double	xsav, x, hnext, hdid, h;
	double	*yscal, *y, *dydx;

	yscal = new double[nvar];
	y = new double[nvar];
	dydx = new double[nvar];
	
	x=x1;
	h = SIGN(h1, x2-x1);
	*nok = (*nbad) = *kount = 0;
	for( i=0; i<nvar; i++ )
		y[i] = ystart[i];
	if( kmax > 0 ) xsav = x - dxsav*2.0;

	for( nstp=1; nstp<=MAXSTP; nstp++ )
	{
		(this->*derivs)(x,y,dydx);
		for( i=0; i<nvar; i++ )
		{
			yscal[i] = fabs(y[i]) + fabs(dydx[i]*h) + TINY;
			if( yscal[i] < 1 )
				yscal[i] = 1;
		}

		if( kmax > 0 && *kount < kmax-1 && fabs(x-xsav) > fabs(dxsav) )
		{
			xp[(*kount)] = x;
			for( i=0; i<nvar; i++ )
				yp[i][*kount] = y[i];
			(*kount)++;
			xsav = x;
		}
		if( (x+h-x2)*(x+h-x1) > 0.0 ) 
			h=x2 - x;

		(this->*rkqs)(y,dydx,nvar,&x,h,eps,yscal,&hdid,&hnext,derivs);
		if( hdid == h)
			++(*nok);
		else
			++(*nbad);

		if( (x-x2)*(x2-x1) >= 0.0 )
		{
			for( i=0; i<nvar; i++ )
				ystart[i] = y[i];
			if( kmax )
			{
				xp[(*kount)++] = x;
				for( i=0; i<nvar; i++ )
					yp[i][*kount] = y[i];
			}

			delete [] dydx;
			delete []y;
			delete []yscal;
			return INT_OK;
		}
		if( fabs(hnext) <= hmin )
		{
//			fprintf(stdout, "\n Step size too small in odeint!!!");
//			printf("\n trenutni x = %12.8f", x );

			return STEPSIZE_UNDERFLOW;
		}
		h = hnext;
	}
//	fprintf(stdout, "\nToo many steps in odeint!!!");
//	printf("\n trenutni x = %12.8f", x );

	delete [] dydx;
	delete []y;
	delete []yscal;
	
	return TO_MANY_STEPS;
}


int CGravSimDoc::simple_integrate( double pdYStart[], int nVar, double dX1, double dX2, 
			double	dStep, double dXSave, double *pdX, double **pdY, int *nKount,
			void (CGravSimDoc::*derivs)(double, double [], double []) )
{
	int			i, kount, nStepPerSave, num;
	long		nstep,k;
	double	x, xsav;
	double	*v, *vout, *dv, *verr;

	v = new double[nVar];
	dv = new double[nVar];
	vout = new double[nVar];
	verr = new double[nVar];

	for( i=0; i<nVar; i++ )
	{
		v[i] = pdYStart[i];
		pdY[i][0] = v[i];
	}

	pdX[0] = dX1;
	x = dX1;
	nstep = (long) ((dX2-dX1) / dStep);
	nStepPerSave = (int) (dXSave / dStep);
	if( nStepPerSave == 0 )
		nStepPerSave = 1;

	num = 0;
	kount = 0;
	xsav = x;
	
	for( k=0; k<nstep; k++ )
	{
		(this->*derivs)(x,v,dv);
		rkck(v,dv,nVar,x,dStep,vout,verr,derivs);

		if( (double)(x+dStep) == x )
		{
			printf("Stepsize too small in RKDumb!!");

			return STEPSIZE_UNDERFLOW;
		}
		num++;

		x += dStep;
		for( i=0; i<nVar; i++ )
			v[i] = vout[i];
	
		if( num == nStepPerSave )
		{
			num = 0;
			pdX[kount+1] = x;
			for( i=0; i<nVar; i++ )
			{
				pdY[i][kount+1] = v[i];
			}
			xsav = x;
			kount++;
		}
	}

	*nKount = kount;

	delete []v;
	delete []dv;
	delete []vout;
	delete []verr;

	return INT_OK;
}

void polint( double xa[], double ya[], int n, double x, double *y, double *dy )
{
/*
		Za dana polja xa[] i ya[] u kojima su tabelirane vrijednosti funkcije, 
		i zadanu vrijednost 'x', funkcija vraæa interpoliranu vrijednost 'y' i 
		procijenjenu grešku 'dy'
*/
	int			i, m, ns = 1;
	double	den, dif, dift, ho, hp, w;
	double *c, *d;

	dif = fabs(x-xa[1]);
	c = new double[n+1];
	d = new double[n+1];

	for( i=1; i<=n; i++ )
	{
		if( (dift = fabs(x-xa[i])) < dif )
		{
			ns = i;
			dif = dift;
		}
		c[i] = ya[i];
		d[i] = ya[i];
	}
	*y = ya[ns--];
	for( m=1; m<n; m++ )
	{
		for( i=1; i<=n-m; i++ )
		{
			ho = xa[i] - x;
			hp = xa[i+m] - x;
			w = c[i+1] - d[i];

			if( (den = ho - hp) == 0.0 )
			{
				printf("Error in routine polint");
				// do ove greške može doæi samo ako su dva ulaza u 'xa' identièna
				assert(0);
			}
			den = w / den;
			d[i] = hp * den;
			c[i] = ho * den;
		}
		*y += (*dy = (2*ns < (n-m) ? c[ns+1] : d[ns--] ));
	}
	delete []d;
	delete []c;
}
