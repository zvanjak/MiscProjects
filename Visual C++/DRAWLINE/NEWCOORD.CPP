// NewCoord.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "NewCoord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewCoord dialog


CNewCoord::CNewCoord(CWnd* pParent /*=NULL*/)
	: CDialog(CNewCoord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewCoord)
	m_dX = 0.0;
	m_dY = 0.0;
	//}}AFX_DATA_INIT
}


void CNewCoord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewCoord)
	DDX_Text(pDX, IDC9_X, m_dX);
	DDX_Text(pDX, IDC9_Y, m_dY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewCoord, CDialog)
	//{{AFX_MSG_MAP(CNewCoord)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCoord message handlers
