// CalcFourierCoefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AntNiz.h"
#include "CalcFourierCoefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalcFourierCoefDlg dialog


CCalcFourierCoefDlg::CCalcFourierCoefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalcFourierCoefDlg::IDD, pParent)
{
	Create(IDD_DIALOG2, pParent);
	//{{AFX_DATA_INIT(CCalcFourierCoefDlg)
	//}}AFX_DATA_INIT
}


void CCalcFourierCoefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalcFourierCoefDlg)
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalcFourierCoefDlg, CDialog)
	//{{AFX_MSG_MAP(CCalcFourierCoefDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalcFourierCoefDlg message handlers

void CCalcFourierCoefDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
}

BOOL CCalcFourierCoefDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}
