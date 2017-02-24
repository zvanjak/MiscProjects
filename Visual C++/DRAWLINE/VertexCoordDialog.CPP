// VertexCoordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "VertexCoordDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VertexCoordDialog dialog


VertexCoordDialog::VertexCoordDialog(CWnd* pParent /*=NULL*/)
	: CDialog(VertexCoordDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(VertexCoordDialog)
	m_nVertNum = 0;
	m_dXCoord = 0.0;
	m_dYCoord = 0.0;
	m_dZCoord = 0.0;
	//}}AFX_DATA_INIT
}


void VertexCoordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VertexCoordDialog)
	DDX_Text(pDX, IDC2_VERTEX_NUM, m_nVertNum);
	DDX_Text(pDX, IDC2_X_COORD, m_dXCoord);
	DDX_Text(pDX, IDC2_Y_COORD, m_dYCoord);
	DDX_Text(pDX, IDC2_Z_COORD, m_dZCoord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VertexCoordDialog, CDialog)
	//{{AFX_MSG_MAP(VertexCoordDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VertexCoordDialog message handlers
