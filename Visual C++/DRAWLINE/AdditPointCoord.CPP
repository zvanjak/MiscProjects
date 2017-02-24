// AdditPointCoord.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "AdditPointCoord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdditPointCoord dialog


CAdditPointCoord::CAdditPointCoord(CWnd* pParent /*=NULL*/)
	: CDialog(CAdditPointCoord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdditPointCoord)
	m_dT = 0.0;
	m_dX = 0.0;
	//}}AFX_DATA_INIT
}


void CAdditPointCoord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdditPointCoord)
	DDX_Text(pDX, IDC7_T, m_dT);
	DDX_Text(pDX, IDC7_X, m_dX);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdditPointCoord, CDialog)
	//{{AFX_MSG_MAP(CAdditPointCoord)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdditPointCoord message handlers
