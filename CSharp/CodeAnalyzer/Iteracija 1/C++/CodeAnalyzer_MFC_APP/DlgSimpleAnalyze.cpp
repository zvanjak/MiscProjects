// DlgSimpleAnalyze.cpp : implementation file
//

#include "stdafx.h"
#include "CodeAnalyzer_MFC_APP.h"
#include "DlgSimpleAnalyze.h"


// CDlgSimpleAnalyze dialog

IMPLEMENT_DYNAMIC(CDlgSimpleAnalyze, CDialog)

CDlgSimpleAnalyze::CDlgSimpleAnalyze(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSimpleAnalyze::IDD, pParent)
{

}

CDlgSimpleAnalyze::~CDlgSimpleAnalyze()
{
}

void CDlgSimpleAnalyze::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSimpleAnalyze, CDialog)
	ON_BN_CLICKED(IDC_CMD_BROWSE_DIR, &CDlgSimpleAnalyze::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CMD_ANALYZE, &CDlgSimpleAnalyze::OnBnClickedCmdAnalyze)
END_MESSAGE_MAP()


// CDlgSimpleAnalyze message handlers

void CDlgSimpleAnalyze::OnBnClickedButton1()
{
}

void CDlgSimpleAnalyze::OnBnClickedCmdAnalyze()
{
}
