#include "stdafx.h"
#include "DrawLine.h"

#include "math.h"
//#include "struct.h"

#include "DrawLineDoc.h"
#include "DrawLineView.h"

//#include "matrix.h"

Matrix	GetProjectionMatrix( VERTEX O, VERTEX G )
{
	double		x1, y1, z1, SinAlpha, CosAlpha, x2, y2, z2, SinBeta, CosBeta, h;
	Matrix		T(4,4), T1(4,4), T2(4,4);

	T1.MakeUnitMatrix();
	T2.MakeUnitMatrix();

// 1. transformacija - pomak ishodista u tocku ocista
	T1.SetElem(3, 0, -O.x );
	T1.SetElem(3, 1, -O.y );
	T1.SetElem(3, 2, -O.z );

	x1 = G.x - O.x;
	y1 = G.y - O.y;
	z1 = G.z - O.z;
	
	SinAlpha = y1 / sqrt(x1*x1 + y1*y1);
	CosAlpha = x1 / sqrt(x1*x1 + y1*y1);

// 2. transformacija - rotacija oko osi z za kut alpha
	T2.SetElem(0, 0, CosAlpha);
	T2.SetElem(0, 1, -SinAlpha);
	T2.SetElem(1, 0, SinAlpha);
	T2.SetElem(1, 1, CosAlpha);

	T = T1 * T2;
	T1 = T;
	T2.Clear();

	x2 = sqrt(x1*x1 + y1*y1);
	y2 = 0;
	z2 = z1;

	SinBeta = x2 / sqrt(x2*x2 + z2*z2);
	CosBeta = z2 / sqrt(x2*x2 + z2*z2);

// 3. transformacija - rotacija oko osi y za kut beta
	T2.SetElem(0, 0, CosBeta);
	T2.SetElem(0, 2, SinBeta);
	T2.SetElem(1, 1, 1);
	T2.SetElem(2, 0, -SinBeta);
	T2.SetElem(2, 2, CosBeta);
	T2.SetElem(3, 3, 1);

	T = T1 * T2;
	T1 = T;
	T2.Clear();

// 4. transformacija - rotacija oko osi z za 90 stupnjeva
	T2.SetElem(0, 1, -1);
	T2.SetElem(1, 0, 1);
	T2.SetElem(2, 2, 1);
	T2.SetElem(3, 3, 1);

	T = T1 * T2;
	T1 = T;
	T2.Clear();

// 5. transformacija - promjena predznaka na x osi
	T2.SetElem(0, 0, -1);
	T2.SetElem(1, 1, 1);
	T2.SetElem(2, 2, 1);
	T2.SetElem(3, 3, 1);

	T = T1 * T2;
	T1 = T;

// perspektivna projekcija
	h = sqrt(x1*x1 + y1*y1 + z1*z1);

	T2.MakeUnitMatrix();
	T2.SetElem(2, 3, 1 / h );
	T2.SetElem(3, 3, 0);

	T = T1 * T2;

	return T;
}

void CDrawLineView::DrawLine( CDC* pDC, int x1, int y1, int x2, int y2, COLORREF Color )
{
	int		x, y, i;
	double	d, x0, y0;

	if( x2 < x1 )
	{
		i = x1;	x1 = x2; x2 = i;
		i = y1; y1 = y2; y2 = i;
	}

	x = x1; y = y1;
	
	x0 = (double) (x2 - x1);
	y0 = (double) (y2 - y1);

	if( fabs(x0) > fabs(y0) )
	{
		d = fabs(y0 / x0) - 0.5;

		for( i=1; i<fabs(x0); i++ )
		{
			pDC->SetPixelV(x,y, Color );
			
			if( d>0 ) 
			{
				if( y0 > 0 )
					y++;
				else
					y--;
				d -= 1;
			}
			
			if( x0 > 0 )
				x++;
			else
				x--;
			d += fabs(y0/x0);
		}
	}
	else
	{
		d = fabs(x0 / y0) - 0.5;

		for( i=1; i<fabs(y0); i++ )
		{
			pDC->SetPixelV(x,y, Color );
			
			if( d>0 ) 
			{
				x++;
				d -= 1;
			}
			
			if( y0 > 0 )
				y++;
			else
				y--;
			d += fabs(x0/y0);
		}
	}
}

void CDrawLineView::DrawConvexPoly( CDC *pDC, int N, struct VERTEX *V )
{
	int			i, y0, y0Min, y0Max;
	double		D, L, x1;
	
	struct COEF		Coef[20];
	struct VERTEX	HelpV;

	if( CheckDirection(N,V) == CLOCKWISE )
	{
//		AfxMessageBox("U smjeru kazaljke na satu ");
		// treba zamijeniti redoslijed vrhova
		for( i=0; i<=N/2; i++ )
		{
			memcpy(&HelpV, &V[i], sizeof(struct VERTEX) );
			memcpy(&V[i], &V[N-i], sizeof(struct VERTEX) );
			memcpy(&V[N-i], &HelpV, sizeof(struct VERTEX) );
		}
	}

	pDC->MoveTo( (int) V[0].x, (int) V[0].y );
	for( i=1; i<=N; i++ )
		pDC->LineTo( (int) V[i].x, (int) V[i].y );

	y0Min = 0;
	y0Max = 1000;
	for( i=0; i<N; i++ )
	{
		Coef[i].A = V[i].y - V[i+1].y;

		if( Coef[i].A == 0 )
		{
			if( i>0 )
			{
				if( V[i-1].y < V[i].y )
					y0Max = (int) V[i].y;
				else
					y0Min = (int) V[i].y;
			}
			else
			{
				if( V[2].y < V[i].y )
					y0Max = (int) V[0].y;
				else
					y0Min = (int) V[0].y;
			}
		}

		Coef[i].B = -V[i].x + V[i+1].x;
		Coef[i].C = V[i].x * V[i+1].y - V[i+1].x * V[i].y;
	}

/* provjera da li je ona toèka unutar poligona */
	if( CheckPointInPoly(m_CheckPoint, Coef, N) > 0 )
		AfxMessageBox("Toèka je izvan poligona !!!");
	else
		AfxMessageBox("Toèka je UNUTAR poligona ");

/* a sada æemo bojati poligon */
	for( y0=y0Min; y0<y0Max; y0++)
	{
		L = -10e5;
		D = 10e6;

		for( i=0; i<N; i++ )
		{
			if( Coef[i].A != 0 )
			{
				x1 = -Coef[i].B * y0 / Coef[i].A - Coef[i].C / Coef[i].A;
				
				if( V[i].y < V[i+1].y && x1 > L )
					L = x1;
				if( V[i].y >= V[i+1].y && x1 < D )
					D = x1;
			}
		}
		if( L < D )
		{
			pDC->MoveTo((int) L,y0);
			pDC->LineTo((int) D,y0);
		}
	}
}

void CDrawLineView::DrawPolygon( CDC *pDC, int N, struct VERTEX *V )
{
	int			i, y0, y0Min, y0Max, N0;
	double		Z, T, S[20];
	
	struct COEF		Coef[20], LineCoef;
	struct VERTEX	HelpV, v0;

	V[N+1].x = V[1].x;
	V[N+1].y = V[1].y;
	V[N+1].h = V[1].h;

	v0.x = m_CheckPoint.x;
	v0.y = m_CheckPoint.y;

	if( CheckDirection(N,V) == COUNTER_CLOCKWISE )
	{
		// treba ih poredati u smjeru kazaljke na satu
		for( i=0; i<=N/2; i++ )
		{
			memcpy(&HelpV, &V[i], sizeof(struct VERTEX) );
			memcpy(&V[i], &V[N-i], sizeof(struct VERTEX) );
			memcpy(&V[N-i], &HelpV, sizeof(struct VERTEX) );
		}
	}

	pDC->MoveTo( (int) V[0].x, (int) V[0].y );
	for( i=1; i<=N; i++ )
		pDC->LineTo( (int) V[i].x, (int) V[i].y );

	y0Min = 0;
	y0Max = 1000;
	for( i=0; i<N; i++ )
	{
		Coef[i].A = V[i].y - V[i+1].y;
		Coef[i].B = -V[i].x + V[i+1].x;
		Coef[i].C = V[i].x * V[i+1].y - V[i+1].x * V[i].y;
	}

	LineCoef.A = 0;
	LineCoef.B = 1;
	LineCoef.C = -m_CheckPoint.y;

	N0 = LineWithEdgeIntersection(N, v0, Coef, LineCoef, V, S );
	
	if( N0 % 2 == 0 )
		AfxMessageBox("Toèka je izvan poligona !!!!");
	else
		AfxMessageBox( "Toèka je unutar poligona !!!");

	for( y0=0; y0<1000; y0++)
	{
		LineCoef.A = 0;
		LineCoef.B = 1;
		LineCoef.C = -y0;
		v0.x = 0;
		v0.y = y0;

		N0 = LineWithEdgeIntersection(N, v0, Coef, LineCoef, V, S);
		if( N0 >= 2 )
		{
			do
			{
				Z=0;
				for( i=0; i<N0-1; i++ )
				{
					if( S[i] > S[i+1] )
					{
						T = S[i];
						S[i] = S[i+1];
						S[i+1] = T;
						Z = 1;
					}
				}
			} while( Z==1 );
			for( i=0; i<N0-1; i+=2 )
			{
				pDC->MoveTo((int) S[i], y0 );
				pDC->LineTo((int) S[i+1], y0);
			}
		}
	}
}

int LineWithEdgeIntersection( int N, struct VERTEX v0, struct COEF *Coef, struct COEF LineCoef, struct VERTEX *V, double *S )
{
	int		i, N0=0, a=0;
	double	T, T1, D1, D2;
	struct	VERTEX	v1, v2, v3;

	for( i=0; i<N; i++ )
	{
		v3.x = Coef[i].B * LineCoef.C - Coef[i].C * LineCoef.B;
		v3.y = -Coef[i].A * LineCoef.C + Coef[i].C * LineCoef.A;
		v3.h = Coef[i].A * LineCoef.B - Coef[i].B * LineCoef.A;
	
		if( v3.h != 0 )		// za w3=0 radi se o paralelnim pravcima
		{
			v3.x /= v3.h;
			v3.y /= v3.h;

			v1.x = v0.x;
			v1.y = v0.y;

			v2.x = v0.x + 1;
			v2.y = v0.y;
			T = V32(v1, v2, v3);

			if( T >= 0 )
			{
				T1 = T;

				v1.x = V[i].x;
				v1.y = V[i].y;
				v2.x = V[i+1].x;
				v2.y = V[i+1].y;
				
				T = V32(v1, v2, v3);

				if( !( T <= 0 || T > 1 ) )
				{
					if( T < 1 )
						goto skip12;
	
					// korak 12.
//					AfxMessageBox("T=1");
					
					v2.x = V[i+2].x;
					v2.y = V[i+2].y;
					D1 = LineCoef.A * v1.x + LineCoef.B * v1.y + LineCoef.C;
					D2 = LineCoef.A * v2.x + LineCoef.B * v2.y + LineCoef.C;

					if( (D1>0 && D2>0) || (D1<0 && D2<0) )
					{
						a = a+1;
						goto skip13;
					}
skip12:
					S[N0++] = T1;
skip13:	
					;
				}
			}
		}
	}
	return N0;
}

double	V32( struct VERTEX V1, struct VERTEX V2, struct VERTEX V3 )
{
	double	D1, D2;

	D1 = V2.x - V1.x;
	D2 = V2.y - V1.y;

	if( D1 != 0 )
		return ((V3.x - V1.x)/D1);
	if( D2 != 0 )
		return ((V3.y - V1.y)/D2);
	else
	{
		AfxMessageBox( "Evo i D1=0 i D2=0");
		return 1;
	}
}

int	CheckDirection( int N, struct VERTEX *V )
{
	int		i, j;
	int		ret = COUNTER_CLOCKWISE;
	struct VERTEX	B;
	
	for( i=0; i<N; i++ )
	{
		if( i == N-1 )
			B = VectProd(V[i], V[0] );
		else
			B = VectProd(V[i], V[i+1]);

		if( i <= N - 2 )
			j = i + 2;
		else
			j = i + 2 - N;

		if( ScalProd(V[j], B) > 0 )
			ret = CLOCKWISE;
	}
	
	return	ret;
}

double	ScalProd( struct VERTEX a, struct VERTEX b )
{
	return (a.x*b.x + a.y*b.y + a.z*b.z + a.h*b.h);
}

struct VERTEX	VectProd( struct VERTEX a, struct VERTEX b )
{
	struct	VERTEX ret;

	ret.x = a.y * b.h - b.y * a.h;
	ret.y = -a.x * b.h + b.x * a.h;
	ret.h = a.x * b.y - b.x * a.y;

	return ret;

}

int	CheckPointInPoly( CPoint p, struct COEF *Coef, int N )
{
	int		i, ret = -1;
	
	for( i=0; i<N; i++ )
	{
		if( p.x * Coef[i].A + p.y * Coef[i].B + Coef[i].C > 0 )
			ret = 1;
	}
	return ret;
}

void CDrawLineView::DrawQuadFunc( CDC *pDC, double t0, double t2, double t3, struct VERTEX *V )
{
	Matrix	T(3,3), T1(3,3), P(3,4), A(3,4), parT(1,3), pointT(1,4);
	double	t4, x, y;
	int		i;

	T.SetElem(0,0,t0*t0);
	T.SetElem(0,1,t0);
	T.SetElem(0,2,1);
	T.SetElem(1,0,t2*t2);
	T.SetElem(1,1,t2);
	T.SetElem(1,2,1);
	T.SetElem(2,0,t3*t3);
	T.SetElem(2,1,t3);
	T.SetElem(2,2,1);

	T1 = Invert(T);

	// odredjivanje karkteristiène matrice krivulje
	for( i=0; i<3; i++ )
	{
		P.SetElem(i,0, V[i].x );
		P.SetElem(i,1, V[i].y );
		P.SetElem(i,2, 0 );
		P.SetElem(i,3, 1 );
	}

	A = T1 * P;

	// prikaz krivulje

	for( t4=0; t4<=1; t4+=0.02 )
	{
		parT.SetElem(0,0, t4*t4);
		parT.SetElem(0,1, t4);
		parT.SetElem(0,2, 1);
		pointT = parT * A;

		x = pointT.GetElem(0,0) / pointT.GetElem(0,3);
		y = pointT.GetElem(0,1) / pointT.GetElem(0,3);
	
		if( t4 == 0 )
			pDC->MoveTo( (int) x, (int) y );
		else
			pDC->LineTo((int) x, (int) y );
	}
}

CPoint	TransfToPoint( double *point, Matrix *T )
{
	int		i, j;
	double	Transf[4];
	CPoint	ret; 

	for( i=0; i<4; i++ )
	{
		Transf[i] = 0;
		for( j=0; j<4; j++ )
			Transf[i] += point[j] * T->GetElem(j,i);
	}
	
	ret.x = (long) (Transf[0] / Transf[3]);
	ret.y = (long) (Transf[1] / Transf[3]);

	return	ret;
}

CPoint	TransfVertexToPoint( VERTEX point, Matrix *T )
{
	int		i;
	double	Transf[4];
	CPoint	ret; 

	for( i=0; i<4; i++ )
	{
		Transf[i] = 0;
		Transf[i] += point.x * T->GetElem(0,i);
		Transf[i] += point.y * T->GetElem(1,i);
		Transf[i] += point.z * T->GetElem(2,i);
		Transf[i] += point.h * T->GetElem(3,i);
	}
	
	ret.x = (long) (Transf[0] / Transf[3]);
	ret.y = (long) (Transf[1] / Transf[3]);

	return	ret;
}
