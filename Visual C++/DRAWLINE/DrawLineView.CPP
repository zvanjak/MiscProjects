// DrawLineView.cpp : implementation of the CDrawLineView class
//

#include "stdafx.h"
#include "DrawLine.h"

#include "math.h"
//#include "struct.h"

#include "DrawLineDoc.h"
#include "DrawLineView.h"

#include "MandelbrotDialog.h"
#include "JuliaDlg.h"
#include "AdditPointCoord.h"
#include "NewCoord.h"
#include "WhichPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView

IMPLEMENT_DYNCREATE(CDrawLineView, CView)

BEGIN_MESSAGE_MAP(CDrawLineView, CView)
	//{{AFX_MSG_MAP(CDrawLineView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_HIDDEN_LINES, OnUpdateHiddenLines)
	ON_COMMAND(ID_HIDDEN_LINES, OnHiddenLines)
	ON_COMMAND(ID_JULIA, OnDrawJuliaSet)
	ON_COMMAND(ID_MANDELBROT, OnDrawMandelbrtoSet)
	ON_COMMAND(ID_CUBIC_FUNC, OnCubicFunc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView construction/destruction

CDrawLineView::CDrawLineView()
{
	// TODO: add construction code here
	m_bSettingLines = FALSE;
	m_bFirstMouseClick = TRUE;
	m_bCheckPointInPolygon = FALSE;
	m_bHiddenLines = FALSE;

	Alpha = 45;
	Theta = 45;
	Rho = 500;

	EyeX = Rho * cos(Theta * 3.141/180) * cos(Alpha * 3.141/180);
	EyeY = Rho * cos(Theta * 3.141/180) * sin(Alpha * 3.141/180);
	EyeZ = Rho * sin(Theta * 3.141/180);

}

CDrawLineView::~CDrawLineView()
{
}

BOOL CDrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView drawing

void CDrawLineView::OnDraw(CDC* pDC)
{
	int		i, j, k, N;
	CPoint	p0, p1;
	struct	VERTEX	*V = (struct VERTEX *) calloc( 1, 20 * sizeof(struct VERTEX) );

	CPoint		points[10][10], CoordAxis[4];
	double		p[4];

	CPen	*prevPen, *myWhitePen, *myBlackPen;
	CDrawLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	myBlackPen = (CPen *) pDC->SelectStockObject( BLACK_PEN );
	myWhitePen = (CPen *) pDC->SelectStockObject( WHITE_PEN );

	pDC->SetROP2( R2_COPYPEN );

	// Preserve aspect ratio
  
/*	CRect rect;
	GetClientRect(&rect);  // Get size of viewport
   
	// Make y negative to increase y
	// in an upwards direction.
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(300, 200);*/

	// TODO: add draw code for native data here
	switch( pDoc->GetExerciseNum() )
	{
	case 1:
		if( m_bSettingLines == TRUE )
		{
			/*  najprije treba izbrisati liniju sa starom pozicijom */
			p0 = pDoc->GetVertexCoord(0);
			p1 = m_PrevMousePos;

			prevPen = (CPen *) pDC->SelectObject(myWhitePen);
		
			pDC->MoveTo(p0.x, p0.y-10);
			pDC->LineTo(p1.x, p1.y-10);

			DrawLine(pDC, p0.x, p0.y, p1.x, p1.y, RGB(255,255,255) );

			/* a nakon toga nacrtati na novoj */
			p0 = pDoc->GetVertexCoord(0);
			p1 = m_CurrentMousePos;

			pDC->SelectObject(myBlackPen);
			pDC->MoveTo(p0.x, p0.y-10);
			pDC->LineTo(p1.x, p1.y-10);

			DrawLine(pDC, p0.x, p0.y, p1.x, p1.y, RGB(120,100,100) );

			pDC->SelectObject(prevPen);
		}
		else
		{
			p0 = pDoc->GetVertexCoord(0);
			p1 = pDoc->GetVertexCoord(1);
			DrawLine(pDC, p0.x, p0.y, p1.x, p1.y, RGB(120,100,100) );

			prevPen = (CPen *) pDC->SelectObject(myBlackPen);
			pDC->MoveTo(p0.x, p0.y-10);
			pDC->LineTo(p1.x, p1.y-10);
			pDC->SelectObject(prevPen);
		}
		break;
	case 2:
		if( m_bSettingLines == TRUE )
		{
			N = pDoc->GetVertexNum();
			for( i=0; i<N; i++ )
			{
				V[i].x = (pDoc->GetVertexCoord(i)).x;
				V[i].y = (pDoc->GetVertexCoord(i)).y;
			}
			V[N].x = m_PrevMousePos.x;
			V[N].y = m_PrevMousePos.y;

			V[N+1].x = V[0].x;
			V[N+1].y = V[0].y;
			
			/* najprije izbrisi stari poligon */
			for( i=0; i<N+1; i++ )
				DrawLine(pDC, (int) V[i].x, (int) V[i].y, (int) V[i+1].x, (int) V[i+1].y, RGB(255,255,255) );

			/* a zatim nacrtaj novi */
			V[N].x = m_CurrentMousePos.x;
			V[N].y = m_CurrentMousePos.y;
			
			for( i=0; i<N+1; i++ )
				DrawLine(pDC, (int) V[i].x, (int) V[i].y, (int) V[i+1].x, (int) V[i+1].y, RGB(0,0,0) );
		}
		else
		{
			N = pDoc->GetVertexNum();			/* koliko ima vrhova u poligonu */
			for( i=0; i<=N; i++ )
			{
				V[i].x = (pDoc->GetVertexCoord(i)).x;
				V[i].y = (pDoc->GetVertexCoord(i)).y;
				V[i].z = 0;
				V[i].h = 1;
			}
			prevPen = (CPen *) pDC->SelectObject(myBlackPen);
			DrawConvexPoly(pDC, N, V);
			pDC->SelectObject(prevPen);
		}
		break;
	case 3:
		if( m_bSettingLines == TRUE )
		{
			N = pDoc->GetVertexNum();
			for( i=0; i<N; i++ )
			{
				V[i].x = (pDoc->GetVertexCoord(i)).x;
				V[i].y = (pDoc->GetVertexCoord(i)).y;
			}
			V[N].x = m_PrevMousePos.x;
			V[N].y = m_PrevMousePos.y;

			V[N+1].x = V[0].x;
			V[N+1].y = V[0].y;
			
			/* najprije izbrisi stari poligon */
			for( i=0; i<N+1; i++ )
				DrawLine(pDC, (int) V[i].x, (int) V[i].y, (int) V[i+1].x, (int) V[i+1].y, RGB(255,255,255) );

			/* a zatim nacrtaj novi */
			V[N].x = m_CurrentMousePos.x;
			V[N].y = m_CurrentMousePos.y;
			
			for( i=0; i<N+1; i++ )
				DrawLine(pDC, (int) V[i].x, (int) V[i].y, (int) V[i+1].x, (int) V[i+1].y, RGB(0,0,0) );
		}
		else
		{
			N = pDoc->GetVertexNum();			/* koliko ima vrhova u poligonu */
			for( i=0; i<=N; i++ )
			{
				V[i].x = (pDoc->GetVertexCoord(i)).x;
				V[i].y = (pDoc->GetVertexCoord(i)).y;
				V[i].z = 0;
				V[i].h = 1;
			}
			prevPen = (CPen *) pDC->SelectObject(myBlackPen);
			DrawPolygon(pDC, N, V);
			pDC->SelectObject(prevPen);
		}
		break;
	case 4:
		if( m_bSettingLines == TRUE )
		{
			N = pDoc->GetVertexNum();
			for( i=0; i<N; i++ )
			{
				V[i].x = (pDoc->GetVertexCoord(i)).x;
				V[i].y = (pDoc->GetVertexCoord(i)).y;
			}
			V[N].x = m_PrevMousePos.x;
			V[N].y = m_PrevMousePos.y;

			V[N+1].x = V[0].x;
			V[N+1].y = V[0].y;
			
			/* najprije izbrisi stari poligon */
			for( i=0; i<N+1; i++ )
				DrawLine(pDC, (int) V[i].x, (int) V[i].y, (int) V[i+1].x, (int) V[i+1].y, RGB(255,255,255) );

			/* a zatim nacrtaj novi */
			V[N].x = m_CurrentMousePos.x;
			V[N].y = m_CurrentMousePos.y;
			
			for( i=0; i<N+1; i++ )
				DrawLine(pDC, (int) V[i].x, (int) V[i].y, (int) V[i+1].x, (int) V[i+1].y, RGB(0,0,0) );
		}
		else
		{
			pDC->SetMapMode(MM_ISOTROPIC);
			pDC->SetWindowExt(800, 600);

			CRect rect;
			GetClientRect(&rect);  // Get size of viewport
   
			// Make y negative to increase y
			// in an upwards direction.
			pDC->SetViewportExt(rect.Width(), -rect.Height());

			pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2 );
			
			// TODO: add draw code for native data here

			prevPen = (CPen *) pDC->SelectObject(myBlackPen);

			Matrix	T(4,4);
			Point	pointEye(EyeX,EyeY,EyeZ), pointView(0,0,0);

			T = GetProjectionMatrix(pointEye, pointView);

			p[0]=0; p[1]=0; p[2]=0; p[3]=1;
			CoordAxis[0] = TransfToPoint( p, &T );
			
			p[0]=100; p[1]=0; p[2]=0; p[3]=1;
			CoordAxis[1] = TransfToPoint( p, &T );
			
			p[0]=0; p[1]=100; p[2]=0; p[3]=1;
			CoordAxis[2] = TransfToPoint( p, &T );

			p[0]=0; p[1]=0; p[2]=100; p[3]=1;
			CoordAxis[3] = TransfToPoint( p, &T );

			for( i=1; i<4; i++ )
			{
				pDC->MoveTo( CoordAxis[0] );
				pDC->LineTo( CoordAxis[i] );
			}
			pDC->TextOut(CoordAxis[1].x, CoordAxis[1].y, "x" );
			pDC->TextOut(CoordAxis[2].x, CoordAxis[2].y, "y" );
			pDC->TextOut(CoordAxis[3].x, CoordAxis[3].y, "z" );

			// svaki od N+2 poligona treba nacrtati
			BODY_EDGE		edge;
			BODY_POLY		poly;
			VERTEX			vert;
			int				l1, l2;
			double			x1, y1, x2, y2, d1, d2, s;

			COEF			R[ 6 * 20 ];
			CPoint			Q[ 2 * 20 ];
			CPoint			transf1, transf2;

			// postavi da su svi poligoni vidljivi
			for( i=0; i<pDoc->GetBodyVertNum()+2; i++ )
				pDoc->SetPolyVisibility(i,1);

			// transformirati æemo sve vrhove u sustav slike
			for( i=0; i<2*pDoc->GetBodyVertNum(); i++ )
			{
				vert = pDoc->GetVert(i);
				Q[i] = TransfVertexToPoint(vert, &T);
			}

			if( m_bHiddenLines == FALSE )
			{
				// znaèi da ne skrivamo linije
				// prikaz ŽIÈANA forma
				for( i=0; i<pDoc->GetBodyVertNum()+2; i++ )
				{
					poly = pDoc->GetPoly(i);
					for( j=poly.m_nFirstEdge; j<=poly.m_nSecEdge; j++ )
					{
						edge = pDoc->GetEdge(j);
						
						pDC->MoveTo(Q[edge.m_nFirstVert]);
						pDC->LineTo(Q[edge.m_nSecVert]);
					}
				}
			}
			else
			{
				// ovdje æemo skrivati nevidljive linije
				for( i=0; i<6*pDoc->GetBodyVertNum(); i++ )
				{
					edge = pDoc->GetEdge(i);
					
					l1 = edge.m_nFirstVert;
					l2 = edge.m_nSecVert;

					x1 = Q[l1].x;	y1 = Q[l1].y;
					x2 = Q[l2].x;	y2 = Q[l2].y;

					R[i].A = y1 - y2;
					R[i].B = -x1 + x2;
					R[i].C = x1 * y2 - x2 * y1;
				}

				for( i=0; i<pDoc->GetBodyVertNum()+2; i++ )
				{
					poly = pDoc->GetPoly(i);
					for( j=poly.m_nFirstEdge; j<=poly.m_nSecEdge; j++ )
					{
						d1 = 0;	d2 = 0;
						
						for( k=poly.m_nFirstEdge; k<=poly.m_nSecEdge; k++ )
						{
							edge = pDoc->GetEdge(k);
							l1 = edge.m_nFirstVert;

							x1 = Q[l1].x;
							y1 = Q[l1].y;
							
							s = -x1 * R[j].A - y1 * R[j].B - R[j].C;
							if( s >= 0 )
								d1 = 1;
							if( s < 0 )
								d2 = 1;

							if( d1 == 0 && d2 == 1 )
								// znaèi da se radi o stražnjem poligonu
								pDoc->SetPolyVisibility(i,0);
						}
					}
				}
				
				// iscrtavanje vidljivih poligona
				for( i=0; i<pDoc->GetBodyVertNum()+2; i++ )
				{
					poly = pDoc->GetPoly(i);
					if( poly.m_nVisible == 1 )
					{
						for( j=poly.m_nFirstEdge; j<=poly.m_nSecEdge; j++ )
						{
							edge = pDoc->GetEdge(j);
							
							pDC->MoveTo( Q[edge.m_nFirstVert] );
							pDC->LineTo( Q[edge.m_nSecVert] );
						}
					}
				}
			}
			pDC->SelectObject(prevPen);
		}
		break;
	case 5:
		{
			double	dex, dey, cre, cim, z0re, z0im, z1re, z1im,r, u0, v0;
			int		k, rez_x, rez_y, nColor, m, n;

			pDC->SetMapMode(MM_ISOTROPIC);

			CRect rect;
			GetClientRect(&rect);  // Get size of viewport
   
			// Make y negative to increase y
			// in an upwards direction.
			pDC->SetViewportExt(rect.Width(), -rect.Height());
			pDC->SetViewportOrg(0, rect.Height());

			pDC->SetWindowExt(rect.Width(), rect.Height() );
			rez_x = rect.Width();
			rez_y = rect.Height();

			dex = (m_Fract.dUmax - m_Fract.dUmin) / rez_x;
			dey = (m_Fract.dVmax - m_Fract.dVmin) / rez_y;

			for( i=0; i<rez_x-m_Fract.nDx; i+=m_Fract.nDx )
			{
				u0 = m_Fract.dUmin + dex * i;
				
				for( j=0; j<rez_y-m_Fract.nDy; j+=m_Fract.nDy )
				{
					v0 = m_Fract.dVmin + dey * j;
					k = -1;
					cre = u0;	cim = v0;	z0re = 0; z0im = 0;
					do
					{
						k++;
						z1re = z0re*z0re - z0im*z0im + cre;
						z1im = 2 * z0re*z0im + cim;

						z0re = z1re;
						z0im = z1im;

						r = sqrt(z0re*z0re + z0im*z0im);
					} while( r < m_Fract.dEps & k<m_Fract.nMaxIter );

					nColor = 255/m_Fract.nMaxIter * k;

					for( m=0; m<m_Fract.nDx; m++ )
						for( n=0; n<m_Fract.nDy; n++ )
							pDC->SetPixel(i+n,j+m, RGB(nColor,0,0) );
				}
			}
		}
		break;
	case 6:
		{
			double	dex, dey, cre, cim, z0re, z0im, z1re, z1im,r, u0, v0;
			int		k, rez_x, rez_y, nColor, m, n;

			pDC->SetMapMode(MM_ISOTROPIC);

			CRect rect;
			GetClientRect(&rect);  // Get size of viewport
   
			// Make y negative to increase y
			// in an upwards direction.
			pDC->SetViewportExt(rect.Width(), -rect.Height());
			pDC->SetViewportOrg(0, rect.Height());

			pDC->SetWindowExt(rect.Width(), rect.Height() );
			rez_x = rect.Width();
			rez_y = rect.Height();

			dex = (m_Fract.dUmax - m_Fract.dUmin) / rez_x;
			dey = (m_Fract.dVmax - m_Fract.dVmin) / rez_y;

			for( i=0; i<rez_x-m_Fract.nDx; i+=m_Fract.nDx )
			{
				u0 = m_Fract.dUmin + dex * i;
				
				for( j=0; j<rez_y-m_Fract.nDy; j+=m_Fract.nDy )
				{
					v0 = m_Fract.dVmin + dey * j;
					k = -1;
					cre = m_Fract.dCre;	cim = m_Fract.dCim;	
					z0re = u0; z0im = v0;
					do
					{
						k++;
						z1re = z0re*z0re - z0im*z0im + cre;
						z1im = 2 * z0re*z0im + cim;

						z0re = z1re;
						z0im = z1im;

						r = sqrt(z0re*z0re + z0im*z0im);
					} while( r < m_Fract.dEps & k<m_Fract.nMaxIter );

					nColor = 255/m_Fract.nMaxIter * k;

					for( m=0; m<m_Fract.nDx; m++ )
						for( n=0; n<m_Fract.nDy; n++ )
							pDC->SetPixel(i+n,j+m, RGB(nColor,0,0) );
				}
			}
		}
		break;
		// kvadratna funkcija
	case 7:
		{
		struct VERTEX	V[3];
		double			t0, t2, t3;

		for( i=0; i<3; i++ )
		{
			p0 = pDoc->GetVertexCoord(i);
			V[i].x = p0.x;
			V[i].y = p0.y;
			V[i].z = 0;
			V[i].h = 1;
		}

		prevPen = (CPen *) pDC->SelectObject(myBlackPen);

		t0 = 0;	t2 = 0.5;	t3 = 1;
		DrawQuadFunc(pDC, t0,t2,t3, V);

		t0 = 0;	t2 = 1.0/3;	t3 = 1;
		DrawQuadFunc(pDC, t0,t2,t3, V);

		t0 = 0;	t2 = 1.0/4;	t3 = 1;
		DrawQuadFunc(pDC, t0,t2,t3, V);

		pDC->SelectObject(prevPen);
		}
		break;
		// kubna funkcija
	case 8:
		{
			double	t, t0, t1, t2, r, x, y;
			int		nx, ny;
			VERTEX	p;

			pDC->SetMapMode(MM_ISOTROPIC);

			CRect rect;
			GetClientRect(&rect);  // Get size of viewport
   
			// Make y negative to increase y
			// in an upwards direction.
			pDC->SetViewportExt(rect.Width(), -rect.Height());
			pDC->SetViewportOrg(rect.Width()/4, rect.Height()/2);

			pDC->SetWindowExt(rect.Width(), rect.Height() );

			p = m_AdditPoint;
			t0 = m_dAdditPointT;;

			t2 = -pow(t0,3) + 3*t0*t0 - 2*t0;
			
			prevPen = (CPen *) pDC->SelectObject(myBlackPen);

			pDC->MoveTo(-rect.Width()/4, 0);
			pDC->LineTo(rect.Width()*3/4, 0);
			pDC->MoveTo(0, rect.Height()/2 );
			pDC->LineTo(0, -rect.Height()/2 );

			nx = (int) (0 * rect.Width() / 4);
			ny = (int) (1 * rect.Height() / 4);
			pDC->MoveTo(nx, ny);

			for( t=0; t<=2; t+=0.01 )
			{
				t1 = -pow(t,3) + 3*t*t - 2* t;
				r = t1 * (t0 - p.x) + t2 * (p.x - 1);

				x = 1 + t2 * (t - 1) * (p.x - 1)/r;
				y = t2 * (pow(t,3) - 2*t*t - t + 2) * (p.x - 1) / (2*r);

				nx = (int) (x * rect.Width() / 4);
				ny = (int) (y * rect.Height() / 4);
				pDC->LineTo( nx, ny );
			}
			pDC->SelectObject(prevPen);
		}
		break;
		// Bezierova funkcija
	case 9:
		{
			int		nNum;
			CWhichPoint	myD1;
			CNewCoord	myD2;

			if( m_bSettingLines == TRUE )
			{
				N = pDoc->GetVertexNum();
				for( i=0; i<N; i++ )
				{
					V[i].x = (pDoc->GetVertexCoord(i)).x;
					V[i].y = (pDoc->GetVertexCoord(i)).y;
				}
				V[N].x = m_PrevMousePos.x;
				V[N].y = m_PrevMousePos.y;

				/* najprije izbrisi stari poligon */
				for( i=0; i<N; i++ )
					DrawLine(pDC, (int) V[i].x, (int) V[i].y, (int) V[i+1].x, (int) V[i+1].y, RGB(255,255,255) );

				/* a zatim nacrtaj novi */
				V[N].x = m_CurrentMousePos.x;
				V[N].y = m_CurrentMousePos.y;
				
				for( i=0; i<N; i++ )
					DrawLine(pDC, (int) V[i].x, (int) V[i].y, (int) V[i+1].x, (int) V[i+1].y, RGB(0,0,0) );
			}
			else
			{
				prevPen = (CPen *) pDC->SelectObject(myBlackPen);

				N = pDoc->GetVertexNum() - 1;

				for( i=0; i<=N; i++ )
				{
					V[i].x = (pDoc->GetVertexCoord(i)).x;
					V[i].y = (pDoc->GetVertexCoord(i)).y;
					V[i].z = 0;
					V[i].h = 1;

					if( i == 0 )
						pDC->MoveTo( (int) V[0].x, (int) V[0].y );
					else
						pDC->LineTo( (int) V[i].x, (int) V[i].y );
				}

				DrawBezier( pDC, N, V );

				myD1.DoModal();
				nNum = myD1.m_nVertNum;

				myD2.m_dX = V[nNum-1].x;
				myD2.m_dY = V[nNum-1].y;
				myD2.DoModal();
				V[nNum-1].x = myD2.m_dX;
				V[nNum-1].y = myD2.m_dY;

				for( i=0; i<=N; i++ )
				{
					if( i == 0 )
						pDC->MoveTo( (int) V[0].x, (int) V[0].y );
					else
						pDC->LineTo( (int) V[i].x, (int) V[i].y );
				}

				DrawBezier( pDC, N, V );
				
				pDC->SelectObject(prevPen);
			}
		}
		break;
	default:
		break;
	}
}

void CDrawLineView::DrawBezier( CDC *pDC, int N,  struct VERTEX *V )
{
	double	t, x, y, n1, i1, F, G;
	int		i;

	pDC->MoveTo( (int) V[0].x, (int) V[0].y );

	for( t=0; t<=1; t+=0.01 )
	{
		x = 0;
		y = 0;
		for( i=0; i<=N; i++ )
		{
			n1 = Fact(N);
			i1 = Fact(i);
			F = Fact(N-i);
			G = n1 * pow(t,i) * pow( (1-t), N-i ) / ( i1 * F );

			x += V[i].x * G;
			y += V[i].y * G;
		}
		pDC->LineTo( (int) x, (int) y );
	}

}

double	Fact( int n )
{
	double	ret;
	int		i;
	
	ret = 1;
	for( i=1; i<=n; i++ )
		ret *= i;

	return ret;
}
/////////////////////////////////////////////////////////////////////////////
// CDrawLineView diagnostics

#ifdef _DEBUG
void CDrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawLineDoc* CDrawLineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawLineDoc)));
	return (CDrawLineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView message handlers

void CDrawLineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT	nNum=0;

	CDrawLineDoc *pDoc = GetDocument();
	// TODO: Add your message handler code here and/or call default

	/* ako je ovo pocetak crtanja, za svaki slucaj inicijaliziraj polje koordinata */
	if( m_bFirstMouseClick == TRUE )
	{
		pDoc->ResetVertexCoord();
		m_bFirstMouseClick = FALSE;
	}

	if( m_bCheckPointInPolygon == TRUE && (pDoc->GetExerciseNum()==2 || pDoc->GetExerciseNum() == 3) )
	{
		m_CheckPoint = point;
		
		Invalidate();
		
		m_bFirstMouseClick = TRUE;
		m_bCheckPointInPolygon = FALSE;
	}
	else
	{
		nNum = pDoc->GetExerciseNum();
		if( (nNum == 1 && pDoc->GetVertexNum() == 0)|| nNum == 2 || nNum == 3 || nNum == 4 || nNum == 9 )
		{
			pDoc->AddMouseCoord(point);
			m_bSettingLines = TRUE;
		}
		else if( nNum == 7 )
			pDoc->AddMouseCoord(point);
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CDrawLineView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CDrawLineDoc *pDoc = GetDocument();
	// TODO: Add your message handler code here and/or call default

	pDoc->LastMouseCoord(point);
	m_bSettingLines = FALSE;

	if( pDoc->GetExerciseNum() == 2 || pDoc->GetExerciseNum() == 3 )
	{
		AfxMessageBox("Sada klikni mišem na neku poziciju da provjerimo da li je unutar poligona !!!");
		m_bCheckPointInPolygon = TRUE;
	}

	if( pDoc->GetExerciseNum() == 4)
	{
		m_bFirstMouseClick = TRUE;

		pDoc->SetZCoords();
		pDoc->SetBodyData();
		pDoc->CheckPoint();
	}
	if( pDoc->GetExerciseNum() == 7 || pDoc->GetExerciseNum() == 9 )
	{
		m_bFirstMouseClick = TRUE;
	}

	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}

void CDrawLineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_PrevMousePos = m_CurrentMousePos;
	m_CurrentMousePos = point;

	if( m_bSettingLines == TRUE )
		Invalidate();

	CView::OnMouseMove(nFlags, point);
}


void CDrawLineView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case 'J' :
		Alpha -= 5;
		if( Alpha < 0 )
			Alpha = 360;
//		AfxMessageBox("j");
		break;
	case 'L':
		Alpha += 5;
		if( Alpha >= 360 )
			Alpha = 0;
//		AfxMessageBox("l");
		break;
	case 'I':
		Theta += 5;
		if( Theta >= 360 )
			Theta = 0;
//		AfxMessageBox("i");
		break;
	case 'K':
		Theta -= 5;
		if( Theta < 0 )
			Theta = 360;
//		AfxMessageBox("k");
		break;
	case 'Q':
		if( Rho > 10 )
			Rho -= 2;
		break;
	case 'A':
		Rho += 2;
		break;
	}

	EyeX = Rho * cos(Theta * 3.141/180) * cos(Alpha * 3.141/180);
	EyeY = Rho * cos(Theta * 3.141/180) * sin(Alpha * 3.141/180);
	EyeZ = Rho * sin(Theta * 3.141/180);

	Invalidate();
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDrawLineView::OnUpdateHiddenLines(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if( m_bHiddenLines == TRUE )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CDrawLineView::OnHiddenLines() 
{
	// TODO: Add your command handler code here
	if( m_bHiddenLines == TRUE )
		m_bHiddenLines = FALSE;
	else
		m_bHiddenLines = TRUE;

	Invalidate();
}

void CDrawLineView::OnDrawJuliaSet() 
{
	CDrawLineDoc *pDoc = GetDocument();
	// TODO: Add your command handler code here
	CJuliaDlg		myD;
	int			ret;

	ret = myD.DoModal();

	if( ret == IDOK )
	{
		pDoc->SetExercise(6);

		m_Fract.dEps = myD.m_dEps;
		m_Fract.nMaxIter = myD.m_nMaxIterNum;
		m_Fract.nDx = myD.m_nRectWidth;
		m_Fract.nDy = myD.m_nRectHeight;
		m_Fract.dUmin = myD.m_dX1;
		m_Fract.dUmax = myD.m_dX2;
		m_Fract.dVmin = myD.m_dY1;
		m_Fract.dVmax = myD.m_dY2;
		m_Fract.dCre = myD.m_dCre;
		m_Fract.dCim = myD.m_dCim;

		Invalidate();
	}
}

void CDrawLineView::OnDrawMandelbrtoSet() 
{
	CDrawLineDoc *pDoc = GetDocument();
	// TODO: Add your command handler code here
	MandelbrotDialog	myD;
	int			ret;

	ret = myD.DoModal();

	if( ret == IDOK )
	{
		pDoc->SetExercise(5);

		m_Fract.dEps = myD.m_dEps;
		m_Fract.nMaxIter = myD.m_nMaxIterNum;
		m_Fract.nDx = myD.m_nRectWidth;
		m_Fract.nDy = myD.m_nRectHeight;
		m_Fract.dUmin = myD.m_dX1;
		m_Fract.dUmax = myD.m_dX2;
		m_Fract.dVmin = myD.m_dY1;
		m_Fract.dVmax = myD.m_dY2;

		Invalidate();
	}
}

void CDrawLineView::OnCubicFunc() 
{
	// TODO: Add your command handler code here
	CDrawLineDoc *pDoc = GetDocument();
	CAdditPointCoord	myD;
	int			ret;

	ret = myD.DoModal();

	if( ret == IDOK )
	{
		pDoc->SetExercise(8);
		m_AdditPoint.x = myD.m_dX;
		m_dAdditPointT = myD.m_dT;

		Invalidate();
	}
	
}
