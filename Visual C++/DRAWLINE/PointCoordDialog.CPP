// PointCoordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "PointCoordDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointCoordDialog dialog


CPointCoordDialog::CPointCoordDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPointCoordDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointCoordDialog)
	m_dXCoord = 0.0;
	m_dYCoord = 0.0;
	m_dZCoord = 0.0;
	//}}AFX_DATA_INIT
}


void CPointCoordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointCoordDialog)
	DDX_Text(pDX, IDC6_X_COORD, m_dXCoord);
	DDX_Text(pDX, IDC6_Y_COORD, m_dYCoord);
	DDX_Text(pDX, IDC6_Z_COORD, m_dZCoord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointCoordDialog, CDialog)
	//{{AFX_MSG_MAP(CPointCoordDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointCoordDialog message handlers
