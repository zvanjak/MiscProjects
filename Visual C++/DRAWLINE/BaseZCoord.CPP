// BaseZCoord.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "BaseZCoord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BaseZCoord dialog


BaseZCoord::BaseZCoord(CWnd* pParent /*=NULL*/)
	: CDialog(BaseZCoord::IDD, pParent)
{
	//{{AFX_DATA_INIT(BaseZCoord)
	m_dLowerZCoord = 0.0;
	m_dUpperZCoord = 0.0;
	//}}AFX_DATA_INIT
}


void BaseZCoord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BaseZCoord)
	DDX_Text(pDX, IDC5_LOWER_Z_COORD, m_dLowerZCoord);
	DDX_Text(pDX, IDC5_UPPER_Z_COORD, m_dUpperZCoord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BaseZCoord, CDialog)
	//{{AFX_MSG_MAP(BaseZCoord)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BaseZCoord message handlers
