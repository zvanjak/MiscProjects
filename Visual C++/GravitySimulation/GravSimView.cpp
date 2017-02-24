// GravSimView.cpp : implementation of the CGravSimView class
//

#include "stdafx.h"
#include "GravitySimulation.h"

#include "GravSimDoc.h"
#include "GraviSimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGravSimView

IMPLEMENT_DYNCREATE(CGravSimView, CView)

BEGIN_MESSAGE_MAP(CGravSimView, CView)
	//{{AFX_MSG_MAP(CGravSimView)
	ON_COMMAND(ID_START_SIM, OnStartSimulation)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGravSimView construction/destruction

CGravSimView::CGravSimView()
{
	// TODO: add construction code here
	bStartSim = false;
}

CGravSimView::~CGravSimView()
{
}

BOOL CGravSimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGravSimView drawing

void CGravSimView::OnDraw(CDC* pDC)
{
	CGravSimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// TODO: add draw code for native data here
	int		i, j;

	DrawAllBodies(pDC);

	if( bStartSim == true ) {
		Vector	force[10] ;
		float		t, dt = 0.003, x, y;
		int			nOK, nBAD, kount;
		double	ystart[40];

		double	*xp = new double[10000];
		double	**yp = new double*[40];
		for( i=0; i<=40; i++ )
			yp[i] = new double[10000];

		for( i=0; i<10; i++ ) {
			ystart[i*4]		= pDoc->B[i].Speed.X();
			ystart[i*4+1] = pDoc->B[i].Speed.Y();
			ystart[i*4+2] = pDoc->B[i].Pos.X();
			ystart[i*4+3] = pDoc->B[i].Pos.Y();
		}

//		int ret = pDoc->simple_integrate(ystart, 4*10, 0, 200, 0.5, 0.1, xp, yp, &kount, pDoc->Deriv );

		int ret = pDoc->odeint(ystart, 4*10, 0, 2000, 1e-4, 0.00001, 0, &nOK, &nBAD,&CGravSimDoc::Deriv, &CGravSimDoc::rkqs, 10000, &kount, xp, yp, 0.0001 );

		if( ret == INT_OK ) 
			AfxMessageBox("Sve OK");
		if( ret == STEPSIZE_UNDERFLOW )
			AfxMessageBox("Stepsize underflow ");
		else if( ret == TO_MANY_STEPS	)
			AfxMessageBox("To many steps");
		
		{
			float	rad;
/*
			for( j=0; j<kount; j++ ) {
				for( i=0; i<10; i++ ) {
					x = yp[i*4+2][j];
					y = yp[i*4+3][j];
					rad = pDoc->B[i].Radius * 10;
					pDC->Ellipse(x, y, x+rad, y+rad);
				}
			}
*/
			double	xh, yh, dx, dy, t1, t2, x1, x2, y1, y2;
			int		last = 0, k;
			for( t=0; t<2000; t+=1 ) {
				for( k=0; k<kount-2; k++ )
					if( xp[k] <= t && t < xp[k+1] )	// intepoliramo x i y izmeðu te dvije toèke
					{
						for( i=0; i<10; i++ ) {
							t1 = xp[k];
							t2 = xp[k+1];
							x1 = yp[i*4+2][k];
							x2 = yp[i*4+2][k+1];
							y1 = yp[i*4+3][k];
							y2 = yp[i*4+3][k+1];

							xh = x1 + (x2-x1)/(t2-t1)*(t-t1);
							yh = y1 + (y2-y1)/(t2-t1)*(t-t1);
		//					polint(xp, yp[i*4+2], kount-3, t, &xh, &dx);
		//					polint(xp, yp[i*4+3], kount-3, t, &yh, &dx);
							rad = pDoc->B[i].Radius * 7;
							pDC->Ellipse(xh, yh, xh+rad, yh+rad);

							int a = 0;
							for(int i=0; i<10000; i++ )
								a += rand();
						}
						for( int lk=0; lk<10000; lk++ )
							lk += rand() % 2;
						break;
					}
			}
		}
/*
		for( t=0; t<1000; t+=dt ) {
			for( i=0; i<10; i++ ) {
				force[i] = pDoc->CalcForceOnBody(i);

				pDoc->B[i].Speed += force[i] / pDoc->B[i].Mass * dt;
				pDoc->B[i].Pos	 += pDoc->B[i].Speed * dt;
			}
			if( ((int)(t*10)) %  10 == 0 )
				DrawAllBodies(pDC);
		}
*/
		bStartSim = false;
/*
	delete []xp;
	for( i=0; i<40; i++ )
		delete  []yp[i];
	delete []yp;
	*/
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGravSimView printing

BOOL CGravSimView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGravSimView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGravSimView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGravSimView diagnostics

#ifdef _DEBUG
void CGravSimView::AssertValid() const
{
	CView::AssertValid();
}

void CGravSimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGravSimDoc* CGravSimView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGravSimDoc)));
	return (CGravSimDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGravSimView message handlers

void	CGravSimView::DrawAllBodies( CDC *pDC )
{
	CGravSimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int		i, rad;

	for( i=0; i<10; i++ )
	{
		rad = pDoc->B[i].Radius * 7;
		pDC->Ellipse(pDoc->B[i].Pos.X(), pDoc->B[i].Pos.Y(), pDoc->B[i].Pos.X()+rad, pDoc->B[i].Pos.Y()+rad);
	}
}

void CGravSimView::OnStartSimulation() 
{
	// TODO: Add your command handler code here
	bStartSim = true;
	Invalidate();
}
