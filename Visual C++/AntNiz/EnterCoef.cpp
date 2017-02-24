// EnterCoef.cpp : implementation file
//

#include "stdafx.h"
#include "AntNiz.h"
#include "EnterCoef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnterCoef dialog


CEnterCoef::CEnterCoef(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterCoef::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnterCoef)
	m_dA0 = 0;
	m_dA1 = 0;
	m_dA2 = 0;
	m_dA3 = 0;
	m_dA4 = 0;
	m_dA5 = 0;
	m_dA6 = 0;
	//}}AFX_DATA_INIT
}


void CEnterCoef::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterCoef)
	DDX_Text(pDX, IDC_A0, m_dA0);
	DDX_Text(pDX, IDC_A1, m_dA1);
	DDX_Text(pDX, IDC_A2, m_dA2);
	DDX_Text(pDX, IDC_A3, m_dA3);
	DDX_Text(pDX, IDC_A4, m_dA4);
	DDX_Text(pDX, IDC_A5, m_dA5);
	DDX_Text(pDX, IDC_A6, m_dA6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnterCoef, CDialog)
	//{{AFX_MSG_MAP(CEnterCoef)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnterCoef message handlers
