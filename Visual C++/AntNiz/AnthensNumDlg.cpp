// AnthensNumDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AntNiz.h"
#include "AnthensNumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnthensNumDlg dialog


CAnthensNumDlg::CAnthensNumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnthensNumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnthensNumDlg)
	m_nAntNum = 0;
	m_nStepsNum = 0;
	m_dIntPrecision = 0.0;
	//}}AFX_DATA_INIT
}


void CAnthensNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnthensNumDlg)
	DDX_Text(pDX, IDC_ANTHENS_NUM, m_nAntNum);
	DDV_MinMaxInt(pDX, m_nAntNum, 1, 50);
	DDX_Text(pDX, IDC_BROJ_KORAKA, m_nStepsNum);
	DDV_MinMaxInt(pDX, m_nStepsNum, 50, 2000);
	DDX_Text(pDX, IDC_TOC_INTEGRACIJE, m_dIntPrecision);
	DDV_MinMaxDouble(pDX, m_dIntPrecision, 1.e-006, 1.e-002);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnthensNumDlg, CDialog)
	//{{AFX_MSG_MAP(CAnthensNumDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnthensNumDlg message handlers
