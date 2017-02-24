// AntNizDoc.cpp : implementation of the CAntNizDoc class
//

#include "stdafx.h"
#include "AntNiz.h"

#include "AntNizDoc.h"

#include "EnterCoef.h"
#include "CalcFourierCoefDlg.h"
#include "AnthensNumDlg.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAntNizDoc

IMPLEMENT_DYNCREATE(CAntNizDoc, CDocument)

BEGIN_MESSAGE_MAP(CAntNizDoc, CDocument)
	//{{AFX_MSG_MAP(CAntNizDoc)
	ON_COMMAND(ID_ZADAJ_FUNKCIJU, OnZadajFunkciju)
	ON_COMMAND(ID_ISPISI_KOEFICIJENTE, OnIspisiKoeficijente)
	ON_COMMAND(ID_PROMIJENI_BROJ_ANTENA, OnPromijeniBrojAntena)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntNizDoc construction/destruction

CAntNizDoc::CAntNizDoc()
{
	// TODO: add one-time construction code here
	m_adFuncCoef[0] = 0.6;
	m_adFuncCoef[1] = 0.4;
	m_adFuncCoef[2] = 0.6;
	m_adFuncCoef[3] = 0.4;
	m_adFuncCoef[4] = 0.1;
	m_adFuncCoef[5] = 0.05;
	m_adFuncCoef[6] = 0.01;

	m_eFuncType = FUNC_COEF;

	m_nAnthensNum = 6;
	m_dIntPrecision = 0.5e-3;
	m_nSteps = 500;

	m_bIsFuncDefined = FALSE;
}

CAntNizDoc::~CAntNizDoc()
{
}

BOOL CAntNizDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAntNizDoc serialization

void CAntNizDoc::Serialize(CArchive& ar)
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
// CAntNizDoc diagnostics

#ifdef _DEBUG
void CAntNizDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAntNizDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAntNizDoc commands

void CAntNizDoc::OnZadajFunkciju() 
{
	if( m_eFuncType == FUNC_COEF )
	{
		CEnterCoef		myDlg;

		myDlg.m_dA0 = m_adFuncCoef[0];
		myDlg.m_dA1 = m_adFuncCoef[1];
		myDlg.m_dA2 = m_adFuncCoef[2];
		myDlg.m_dA3 = m_adFuncCoef[3];
		myDlg.m_dA4 = m_adFuncCoef[4];
		myDlg.m_dA5 = m_adFuncCoef[5];
		myDlg.m_dA6 = m_adFuncCoef[6];

		if( myDlg.DoModal() == IDOK )
		{
			m_adFuncCoef[0] = myDlg.m_dA0;
			m_adFuncCoef[1] = myDlg.m_dA1;
			m_adFuncCoef[2] = myDlg.m_dA2;
			m_adFuncCoef[3] = myDlg.m_dA3;
			m_adFuncCoef[4] = myDlg.m_dA4;
			m_adFuncCoef[5] = myDlg.m_dA5;
			m_adFuncCoef[6] = myDlg.m_dA6;

			m_bIsFuncDefined = TRUE;

			CalculateFourierCoef();
			UpdateAllViews(NULL);
		}
	}
}

BOOL CAntNizDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	FILE	*fp;

	if( (fp = fopen(lpszPathName, "r")) != NULL )
	{
		m_adFuncInterpolatedX = new double[500];
		m_adFuncInterpolatedVal = new double[500];

		int			i = 0;
		float		a, b;
		while( fscanf(fp, "%f %f", &a, &b) == 2 )
		{
			m_adFuncInterpolatedX[i] = M_PI * cos(a / 180 * M_PI);
			m_adFuncInterpolatedVal[i] = b;
			i++;
		}

		if( i == 0 )
		{
			AfxMessageBox("Greška u formatu ulazne datoteke !!!");
			return FALSE;
		}

		m_eFuncType = FUNC_INTERPOLATED;
		m_nFuncInterpolatedPointsNum = i;
		fclose(fp);

		m_bIsFuncDefined = TRUE;
		CalculateFourierCoef();
	}
	else
	{
		AfxMessageBox("Nisam uspio otvoriti datoteku !!!");
		return FALSE;
	}
	
	return TRUE;
}

void CAntNizDoc::OnIspisiKoeficijente() 
{
	CCalcFourierCoefDlg		*myDlg;

	myDlg = new CCalcFourierCoefDlg;

	char	str[200];
	for( int i=0; i<m_nAnthensNum; i++ )
	{
		memset(str, 0, 200);

		sprintf(str, "%d.      a[%d] = %15.8f    ------   b[%d] = %15.8f", i, i, m_adCoefA[i], i, m_adCoefB[i] );
		CString		add(str);
		myDlg->m_ctrlList.AddString(add);
	}

	myDlg->UpdateData(FALSE);
}


void CAntNizDoc::OnPromijeniBrojAntena() 
{
	CAnthensNumDlg		myDlg;
	
	myDlg.m_nAntNum = m_nAnthensNum;
	myDlg.m_nStepsNum = m_nSteps;
	myDlg.m_dIntPrecision = m_dIntPrecision;
	
	if( myDlg.DoModal() == IDOK )
	{
		if( myDlg.m_nAntNum != m_nAnthensNum || myDlg.m_dIntPrecision != m_dIntPrecision)
		{
			m_nAnthensNum = myDlg.m_nAntNum;
			m_dIntPrecision = myDlg.m_dIntPrecision;
			
			CalculateFourierCoef();
		}
		m_nSteps = myDlg.m_nStepsNum;
		UpdateAllViews(NULL);
	}
}

/*************************************************************************************/

double	CAntNizDoc::FuncCoef( double x )
{
	double	ret;

	ret = m_adFuncCoef[0];
	for( int i=1; i<MAX_COEF; i++ )
		ret += m_adFuncCoef[i] * pow( acos(x / M_PI), (double) i );

	return ret;
}

double	CAntNizDoc::FuncInterpolated( double x )
{
	double		ret=0, x1, x2, y1, y2;

	for( int i=0; i<m_nFuncInterpolatedPointsNum; i++ )
		if( m_adFuncInterpolatedX[i] == x )
		{
			ret = m_adFuncInterpolatedVal[i];
			break;
		}
		else if( m_adFuncInterpolatedX[i] > x && x > m_adFuncInterpolatedX[i+1] )
		{
			x1 = m_adFuncInterpolatedX[i];
			x2 = m_adFuncInterpolatedX[i+1];
			y1 = m_adFuncInterpolatedVal[i];
			y2 = m_adFuncInterpolatedVal[i+1];

			ret = (y2-y1)/(x2-x1) * (x-x1) + y1;
			break;
		}
		else if( m_adFuncInterpolatedX[i] < x && m_adFuncInterpolatedX[i+1] > x )
		{
			x1 = m_adFuncInterpolatedX[i+1];
			x2 = m_adFuncInterpolatedX[i];
			y1 = m_adFuncInterpolatedVal[i+1];
			y2 = m_adFuncInterpolatedVal[i];

			ret = (y2-y1)/(x2-x1) * (x-x1) + y1;
			break;
		}
	return ret;
}

double CAntNizDoc::FuncCos( double x )
{
	if( m_eFuncType == FUNC_COEF )
		return FuncCoef(x) * cos( m_nM * x );
	else
		return FuncInterpolated(x) * cos( m_nM * x );
}

double CAntNizDoc::FuncSin( double x )
{
	if( m_eFuncType == FUNC_COEF )
		return FuncCoef(x) * sin( m_nM * x );
	else
		return FuncInterpolated(x) * sin( m_nM * x );
}

void CAntNizDoc::CalculateFourierCoef()
{
	int			i;
	double	r=0;

	for( i=0; i<MAX_ANTENS; i++ )
		m_adCoefA[i] = m_adCoefB[i] = 0.0;

	for( i=0; i<m_nAnthensNum; i++ )
	{
		m_nM = i;
		m_adCoefA[i] = qromb(FuncCos, -M_PI, M_PI ) / 2 / M_PI;
		m_adCoefB[i] = qromb(FuncSin, -M_PI, M_PI ) / 2 / M_PI;
	}

	CCalcFourierCoefDlg		*myDlg;

	myDlg = new CCalcFourierCoefDlg;

	char	str[200];
	for( i=0; i<m_nAnthensNum; i++ )
	{
		memset(str, 0, 200);

		sprintf(str, "%d.      a[%d] = %15.8f    ------     b[%d] = %15.8f", i, i, m_adCoefA[i], i, m_adCoefB[i] );
		CString		add(str);
		myDlg->m_ctrlList.AddString(add);
	}

	myDlg->UpdateData(FALSE);
}

double CAntNizDoc::CalcFourierSum(double theta)
{
	double	ret = 0.0;

	for( int m=0; m<m_nAnthensNum; m++ )
	{
		ret += m_adCoefA[m] * cos( m * M_PI * cos(theta) );
		ret += m_adCoefB[m] * sin( m * M_PI * cos(theta) );
	}
	
	return ret;
}

/******************************************************************************************/
/******************************************************************************************/

#define	FUNC_INT(X) ((this->*func)(x))
#define	JMAX					20
#define JMAXP	(JMAX+1)
#define	K 5
#define EPS	1e-4

double	CAntNizDoc::trapzd( double (CAntNizDoc::*func) (double), double a, double b, int n )
{
/*
		Funkcija raèuna n-ti korak proširenog trapezoidalnog pravila
		
		n - broj toèaka koji se koristi kod inteprolacije unutar intervala
*/
	static double	s;
	double		x=0, tnm, sum, del;
	int				it, j;

	if( n == 1 )
		return (s=0.5*(b-a)*(FUNC_INT(a)+FUNC_INT(b)));
	else
	{
		for( it=1,j=1; j<n-1; j++ )
			it <<=1;

		tnm = it;
		del = (b-a)/tnm;
		x = a+0.5*del;
		
		for( sum=0.0, j=1; j<=it; j++, x+=del )
			sum +=FUNC_INT(x);

		s=0.5 * (s+(b-a)*sum/tnm);
		return s;
	}
}

double CAntNizDoc::qsimp( double (CAntNizDoc::*func)(double), double a, double b )
{
	int	j;
	double		s, st, ost, os;

	ost = os = double(-1.0e30);
	for( j=1; j<=JMAX; j++ )
	{
		st = trapzd(func, a, b, j);
		s = ( 4.0 * st - ost) / 3.0;
		if( fabs(s-os) < m_dIntPrecision * fabs(os) )
			return	s;
		if( s == 0.0 && os == 0.0 && j > 6 )
			return s;

		os = s;
		ost = st;
	}

	printf("Previse koraka u qsimp");
	return double(0.0);
}

double CAntNizDoc::qromb( double (CAntNizDoc::*func)(double), double a, double b )
{
	double		ss, dss;
	double		s[JMAXP+1], h[JMAXP+1];
	int				j;
	
	h[1] = double(1.0);
	for( j=1; j<=JMAX; j++ )
	{
		s[j] = trapzd(func, a, b, j);
		if( j >= K )
		{
			polint(&h[j-K], &s[j-K], K, 0.0, &ss, &dss );
			if( fabs(dss) <= m_dIntPrecision * fabs(ss) )
				return ss;
		}

		s[j+1] = s[j];
		h[j+1] = 0.25 * h[j];
	}

	puts("To many steps in qromb");
	return double(0.0);
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
//				assert(0);
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

