// JuliaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "JuliaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJuliaDlg dialog


CJuliaDlg::CJuliaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJuliaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJuliaDlg)
	m_nRectHeight = 0;
	m_nRectWidth = 0;
	m_dCim = 0.0;
	m_dCre = 0.0;
	m_dEps = 0.0;
	m_nMaxIterNum = 0;
	m_dX1 = 0.0;
	m_dX2 = 0.0;
	m_dY1 = 0.0;
	m_dY2 = 0.0;
	//}}AFX_DATA_INIT
}


void CJuliaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJuliaDlg)
	DDX_Text(pDX, IDC4_RECT_HEIGHT, m_nRectHeight);
	DDX_Text(pDX, IDC4_RECT_WIDTH, m_nRectWidth);
	DDX_Text(pDX, IDC4_CIM, m_dCim);
	DDX_Text(pDX, IDC4_CRE, m_dCre);
	DDX_Text(pDX, IDC4_EPS, m_dEps);
	DDX_Text(pDX, IDC4_MAX_ITER_NUM, m_nMaxIterNum);
	DDX_Text(pDX, IDC4_X1, m_dX1);
	DDX_Text(pDX, IDC4_X2, m_dX2);
	DDX_Text(pDX, IDC4_Y1, m_dY1);
	DDX_Text(pDX, IDC4_Y2, m_dY2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJuliaDlg, CDialog)
	//{{AFX_MSG_MAP(CJuliaDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJuliaDlg message handlers
