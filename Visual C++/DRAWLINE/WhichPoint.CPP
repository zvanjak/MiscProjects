// WhichPoint.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "WhichPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWhichPoint dialog


CWhichPoint::CWhichPoint(CWnd* pParent /*=NULL*/)
	: CDialog(CWhichPoint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWhichPoint)
	m_nVertNum = 0;
	//}}AFX_DATA_INIT
}


void CWhichPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWhichPoint)
	DDX_Text(pDX, IDC8_VERT_NUM, m_nVertNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWhichPoint, CDialog)
	//{{AFX_MSG_MAP(CWhichPoint)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWhichPoint message handlers
