// AntNizView.cpp : implementation of the CAntNizView class
//

#include "stdafx.h"
#include "AntNiz.h"

#include "AntNizDoc.h"
#include "AntNizView.h"

#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAntNizView

IMPLEMENT_DYNCREATE(CAntNizView, CView)

BEGIN_MESSAGE_MAP(CAntNizView, CView)
	//{{AFX_MSG_MAP(CAntNizView)
	ON_COMMAND(ID_POLAR_LOG, OnPolarLog)
	ON_UPDATE_COMMAND_UI(ID_POLAR_LOG, OnUpdatePolarLog)
	ON_COMMAND(ID_POLAR_NORM, OnPolarNorm)
	ON_UPDATE_COMMAND_UI(ID_POLAR_NORM, OnUpdatePolarNorm)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntNizView construction/destruction

CAntNizView::CAntNizView()
{
	// TODO: add construction code here
	m_ePlotType = POLAR_LOG;
}

CAntNizView::~CAntNizView()
{
}

BOOL CAntNizView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAntNizView drawing

void CAntNizView::OnDraw(CDC* pDC)
{
	CAntNizDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	pDC->SetMapMode(MM_ISOTROPIC);

	CRect rect;
	GetClientRect(&rect);  // Get size of viewport
	pDC->SetWindowExt( rect.Width(), -rect.Height() );
	pDC->SetViewportExt( rect.Width(), rect.Height() );
	
	pDC->SetWindowOrg(-rect.Width()/2, rect.Height()/2);

	int	nMax = rect.Width() > rect.Height() ? rect.Height()/2 : rect.Width()/2;
	
	CPen	tmpPenEll( PS_DOT, 1, RGB(0,0,0) );
	pDC->SelectObject(&tmpPenEll);
	pDC->Ellipse( -nMax, -nMax, nMax, nMax );

	pDC->MoveTo(0,-nMax);
	pDC->LineTo(0, nMax);
	pDC->MoveTo(-nMax, 0);
	pDC->LineTo(nMax, 0);

	if( pDoc->m_bIsFuncDefined == TRUE )
	{
		int			i = 0;
		double	theta, dMaxAmpl, dMaxFunc, dAmp, dMul, dMulDB, dPrintDB;
		double	*dAmplitude = new double[pDoc->m_nSteps];
		double	*dAmpDB = new double[pDoc->m_nSteps];
		double	*dFunc = new double[pDoc->m_nSteps];
		double	*dFuncDB = new double[pDoc->m_nSteps];

		// najprije æemo izraèunati amplitude
		for( theta=-M_PI, i=0; i<pDoc->m_nSteps; theta += 2*M_PI/pDoc->m_nSteps, i++ )
		{
			dAmplitude[i] = pDoc->CalcFourierSum(theta);
		
			if( pDoc->m_eFuncType == CAntNizDoc::FUNC_COEF )
				dFunc[i] = pDoc->FuncCoef(M_PI*cos(theta));
			else
				dFunc[i] = pDoc->FuncInterpolated(M_PI*cos(theta));
		}

		// zatim naæi najveæu meðu njima
		dMaxAmpl = dAmplitude[0];
		dMaxFunc = dFunc[0];
		for( i=1; i<pDoc->m_nSteps; i++ )
		{
			if( fabs(dAmplitude[i]) > dMaxAmpl )
				dMaxAmpl = fabs(dAmplitude[i]);
			if( dFunc[i] > dMaxFunc )
				dMaxFunc = dFunc[i];
		}

		for( i=0; i<pDoc->m_nSteps; i++ )
		{
			dAmpDB[i] = 20 * log10( fabs(dAmplitude[i]) / dMaxAmpl );
			dFuncDB[i] = 20 * log10( fabs(dFunc[i]) / dMaxFunc );
		}

		if( m_ePlotType == POLAR_LOG )
		{
			// i na kraju ih iscrtati
			dMul = dAmpDB[0];
			dMulDB = dFuncDB[0];
			for( i=1; i<pDoc->m_nSteps; i++ )
			{
				if( dAmpDB[i] < dMul )
					dMul = dAmpDB[i];
				if( dFuncDB[i] < dMulDB )
					dMulDB = dFuncDB[i];
			}

			dPrintDB = dMul;
			dMul = nMax / dMul;
			dMulDB = nMax / dMulDB;

			CPen	tmpPen( PS_SOLID, 1, RGB(0,0,0) );
			pDC->SelectObject(&tmpPen);

			// crtamo dijagram amplitude izraèunate pomoæu F. koeficijenata
			dAmp = nMax - dAmpDB[0] * dMul;
			pDC->MoveTo((int) (dAmp * cos(theta-M_PI/2)), (int) (dAmp * sin(theta-M_PI/2)) );
			for( theta=-M_PI+M_PI/pDoc->m_nSteps, i=1; i<pDoc->m_nSteps; theta+=2*M_PI/pDoc->m_nSteps, i++ )
			{
				dAmp = nMax - dAmpDB[i] * dMul;
				pDC->LineTo((int) (dAmp * cos(theta-M_PI/2)), (int) (dAmp * sin(theta-M_PI/2)) );
			}

			// sada treba još ispisati koliko je to decibela
			char		str[30];
			sprintf(str, "0.0 dB");
			pDC->TextOut(nMax-16,-10, str);

			sprintf(str, "%5.2f dB", ((float) dPrintDB/2) );
			pDC->MoveTo(nMax/2, -5);
			pDC->LineTo(nMax/2, 5);
			pDC->TextOut(nMax/2-strlen(str)*3, -10, str);

			// crtamo stvarni dijagram zraèenja
			CPen	tmpPen2( PS_DASH, 1, RGB(255,0,0) );
			pDC->SelectObject(&tmpPen2);

			dAmp = nMax - dFuncDB[0] * dMulDB;
			pDC->MoveTo((int) (dAmp * cos(theta-M_PI/2)), (int) (dAmp * sin(theta-M_PI/2)) );
			for( theta=-M_PI+M_PI/pDoc->m_nSteps, i=1; i<pDoc->m_nSteps; theta+=2*M_PI/pDoc->m_nSteps, i++ )
			{
				dAmp = nMax - dFuncDB[i] * dMulDB;
				pDC->LineTo((int) (dAmp * cos(theta-M_PI/2)), (int) (dAmp * sin(theta-M_PI/2)) );
			}

		}
		else if( m_ePlotType == POLAR_NORM )
		{
			CPen	tmpPen( PS_SOLID, 1, RGB(0,0,0) );
			pDC->SelectObject(&tmpPen);

			dAmp = dAmplitude[0]/dMaxAmpl * nMax;
			pDC->MoveTo((int) (dAmp * cos(theta-M_PI/2)), (int) (dAmp * sin(theta-M_PI/2)) );
			for( theta=-M_PI+M_PI/pDoc->m_nSteps, i=1; theta<M_PI; theta+=2*M_PI/pDoc->m_nSteps, i++ )
			{
				dAmp = dAmplitude[i]/dMaxAmpl * nMax;
				pDC->LineTo((int) (dAmp * cos(theta-M_PI/2)), (int) (dAmp * sin(theta-M_PI/2)) );
			}

			CPen	tmpPen2( PS_DASH, 1, RGB(255,0,0) );
			pDC->SelectObject(&tmpPen2);

			dAmp = dFunc[i]/dMaxFunc * nMax;
			pDC->MoveTo((int) (dAmp * cos(theta-M_PI/2)), (int) (dAmp * sin(theta-M_PI/2)) );
			for( theta=-M_PI+M_PI/pDoc->m_nSteps, i=1; theta<M_PI; theta+=2*M_PI/pDoc->m_nSteps, i++ )
			{
				dAmp = dFunc[i]/dMaxFunc * nMax;
				pDC->LineTo((int) (dAmp * cos(theta-M_PI/2)), (int) (dAmp * sin(theta-M_PI/2)) );
			}
		}
	}
	else
		pDC->TextOut(0,0,"Nije definirana funkcija !!!");
}

/////////////////////////////////////////////////////////////////////////////
// CAntNizView printing

BOOL CAntNizView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAntNizView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAntNizView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAntNizView diagnostics

#ifdef _DEBUG
void CAntNizView::AssertValid() const
{
	CView::AssertValid();
}

void CAntNizView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAntNizDoc* CAntNizView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAntNizDoc)));
	return (CAntNizDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAntNizView message handlers

void CAntNizView::OnPolarLog() 
{
	m_ePlotType = POLAR_LOG;

	Invalidate();
}

void CAntNizView::OnUpdatePolarLog(CCmdUI* pCmdUI) 
{
	if( m_ePlotType == POLAR_LOG )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CAntNizView::OnPolarNorm() 
{
	m_ePlotType = POLAR_NORM;	
	Invalidate();
}

void CAntNizView::OnUpdatePolarNorm(CCmdUI* pCmdUI) 
{
	if( m_ePlotType == POLAR_NORM )
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}
