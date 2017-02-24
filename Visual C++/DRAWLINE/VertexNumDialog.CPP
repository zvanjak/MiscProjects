// VertexNumDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "VertexNumDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VertexNumDialog dialog


VertexNumDialog::VertexNumDialog(CWnd* pParent /*=NULL*/)
	: CDialog(VertexNumDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(VertexNumDialog)
	m_nVertexNum = 0;
	//}}AFX_DATA_INIT
}


void VertexNumDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VertexNumDialog)
	DDX_Text(pDX, IDC1_VERTEX_NUM, m_nVertexNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VertexNumDialog, CDialog)
	//{{AFX_MSG_MAP(VertexNumDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VertexNumDialog message handlers
