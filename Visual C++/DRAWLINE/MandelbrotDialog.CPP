// MandelbrotDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "MandelbrotDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MandelbrotDialog dialog


MandelbrotDialog::MandelbrotDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MandelbrotDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(MandelbrotDialog)
	m_dEps = 0.0;
	m_nMaxIterNum = 0;
	m_dX1 = 0.0;
	m_dX2 = 0.0;
	m_dY1 = 0.0;
	m_dY2 = 0.0;
	m_nRectHeight = 0;
	m_nRectWidth = 0;
	//}}AFX_DATA_INIT
}


void MandelbrotDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MandelbrotDialog)
	DDX_Text(pDX, IDC3_EPS, m_dEps);
	DDX_Text(pDX, IDC3_MAX_ITER_NUM, m_nMaxIterNum);
	DDX_Text(pDX, IDC3_X1, m_dX1);
	DDX_Text(pDX, IDC3_X2, m_dX2);
	DDX_Text(pDX, IDC3_Y1, m_dY1);
	DDX_Text(pDX, IDC3_Y2, m_dY2);
	DDX_Text(pDX, IDC3_RECT_HEIGHT, m_nRectHeight);
	DDX_Text(pDX, IDC3_RECT_WIDTH, m_nRectWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MandelbrotDialog, CDialog)
	//{{AFX_MSG_MAP(MandelbrotDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MandelbrotDialog message handlers
