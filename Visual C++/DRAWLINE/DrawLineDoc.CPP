// DrawLineDoc.cpp : implementation of the CDrawLineDoc class
//

#include "stdafx.h"
#include "DrawLine.h"

#include "DrawLineDoc.h"
#include "BaseZCoord.h"
#include "PointCoordDialog.h"
#include "AdditPointCoord.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawLineDoc

IMPLEMENT_DYNCREATE(CDrawLineDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawLineDoc, CDocument)
	//{{AFX_MSG_MAP(CDrawLineDoc)
	ON_COMMAND(ID_EXERC_DRAWLINE, OnExercDrawline)
	ON_COMMAND(ID_EXERC_DRAW_CONVEX_POLY, OnExercDrawConvexPoly)
	ON_COMMAND(ID_EXERC_DRAW_POLY, OnExercDrawPoly)
	ON_COMMAND(ID_CHECK_POINT_BODY, OnCheckPointBody)
	ON_COMMAND(ID_BEZIER_FUNC, OnBezierFunc)
	ON_COMMAND(ID_QUAD_FUNC, OnQuadFunc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawLineDoc construction/destruction

CDrawLineDoc::CDrawLineDoc()
{
	// TODO: add one-time construction code here
	m_nExerciseNum = 1;
	m_nVertexNum = 0;
	m_bWaitMouseClick = FALSE;

	m_Body.N = 0;
	m_Body.P = NULL;
	m_Body.B = NULL;
	m_Body.V = NULL;
}

CDrawLineDoc::~CDrawLineDoc()
{
}

BOOL CDrawLineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDrawLineDoc serialization

void CDrawLineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDrawLineDoc diagnostics

#ifdef _DEBUG
void CDrawLineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawLineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawLineDoc commands

void CDrawLineDoc::OnExercDrawline() 
{
	// TODO: Add your command handler code here
	m_nExerciseNum = 1;
	m_nVertexNum = 0;

	m_bWaitMouseClick = TRUE;
	m_bDrawOK = FALSE;
}

void CDrawLineDoc::OnExercDrawConvexPoly() 
{
	// TODO: Add your command handler code here
	m_nExerciseNum = 2;
	m_nVertexNum = 0;

	m_bWaitMouseClick = TRUE;
	m_bDrawOK = FALSE;
}

void CDrawLineDoc::OnExercDrawPoly() 
{
	// TODO: Add your command handler code here

	m_nExerciseNum = 3;
	m_nVertexNum = 0;
}

//////////////////////////////////////////////////////////////////

void CDrawLineDoc::AddMouseCoord( CPoint point )
{
	m_VertexPos[m_nVertexNum++] = point;	
}

void CDrawLineDoc::LastMouseCoord( CPoint point )
{
	m_VertexPos[m_nVertexNum++] = point;
	
	if( m_nExerciseNum == 2 || m_nExerciseNum == 3 )
	{
		m_VertexPos[m_nVertexNum] = m_VertexPos[0];
	}
	
	m_bDrawOK = TRUE;
}

CPoint CDrawLineDoc::GetVertexCoord( UINT nNum )
{
	return m_VertexPos[nNum];
}

void	CDrawLineDoc::ResetVertexCoord( void )
{
	int	i;

	for(i=0; i<20; i++ )
		m_VertexPos[i].x = m_VertexPos[i].y = 0;
	m_nVertexNum = 0;
}

UINT	CDrawLineDoc::GetExerciseNum( void )
{
	return	m_nExerciseNum;
}

void	CDrawLineDoc::SetExercise( int i )
{
	m_nExerciseNum = i;
}

BOOL	CDrawLineDoc::ReadyToDraw( void )
{
	return	m_bDrawOK;
}

UINT	CDrawLineDoc::GetVertexNum( void )
{
	return m_nVertexNum;
}


void CDrawLineDoc::OnCheckPointBody() 
{
	// TODO: Add your command handler code here

	m_nExerciseNum = 4;
	AfxMessageBox("Nacrtaj poligon koji æe predstavljati bazu prizme !");
	m_nVertexNum = 0;
}

void CDrawLineDoc::SetZCoords( void )
{
	BaseZCoord	myD;

	myD.DoModal();

	m_dUpperZ = myD.m_dUpperZCoord;
	m_dLowerZ = myD.m_dLowerZCoord;
}

void CDrawLineDoc::SetBodyData( void )
{
	int		i, p0,p1, b0, b1, n_v0, n_v1;
	int		k, k1, k2,k3, k4, l1, l2, l3;
	
	struct VERTEX	v1, v2, v3;

	p0 = -1;
	b0 = -1;
	n_v0 = -1;

	if( m_Body.N != 0 )
	{
		delete m_Body.P;
		delete m_Body.B;
		delete m_Body.V;

		m_Body.N = 0;
	}
	m_Body.N = m_nVertexNum;

	m_Body.P = new BODY_POLY[m_Body.N+2];
	m_Body.B = new BODY_EDGE[m_Body.N*6];
	m_Body.V = new VERTEX[m_Body.N*2];
	m_Body.R = new PLANE_COEF[m_Body.N+2];


	// spremanje DONJE baze u popise

	p1=p0;	b1=b0;	n_v1=n_v0;
	for( i=0; i<m_nVertexNum; i++ )
	{
		n_v0++;
		m_Body.V[n_v0].x = m_VertexPos[i].x;
		m_Body.V[n_v0].y = m_VertexPos[i].y;
		m_Body.V[n_v0].z = m_dLowerZ;
		m_Body.V[n_v0].h = 1;

		b0++;
		m_Body.B[b0].m_nFirstVert = n_v0;
		m_Body.B[b0].m_nSecVert = n_v0+1;
	}
	m_Body.B[b0].m_nSecVert = n_v1+1;

	p0++;
	m_Body.P[p0].m_nFirstEdge = b1+1;
	m_Body.P[p0].m_nSecEdge = b0;

	
	// spremanje GORNJE baze u popise
	p1=p0;	b1=b0;	n_v1=n_v0;

	n_v0++;
	m_Body.V[n_v0].x = m_VertexPos[0].x;
	m_Body.V[n_v0].y = m_VertexPos[0].y;
	m_Body.V[n_v0].z = m_dUpperZ;
	m_Body.V[n_v0].h = 1;

	b0++;
	m_Body.B[b0].m_nFirstVert = n_v0;
	m_Body.B[b0].m_nSecVert = n_v0+1;

	for( i=m_nVertexNum-1; i>0; i-- )
	{
		n_v0++;
		m_Body.V[n_v0].x = m_VertexPos[i].x;
		m_Body.V[n_v0].y = m_VertexPos[i].y;
		m_Body.V[n_v0].z = m_dUpperZ;
		m_Body.V[n_v0].h = 1;

		b0++;
		m_Body.B[b0].m_nFirstVert = n_v0;
		m_Body.B[b0].m_nSecVert = n_v0+1;
	}
	m_Body.B[b0].m_nSecVert = n_v1+1;

	p0++;
	m_Body.P[p0].m_nFirstEdge = b1+1;
	m_Body.P[p0].m_nSecEdge = b0;

	// spremanje boènih èetverokuta u popise
	k3 = m_nVertexNum;
	
	for( i=0; i<m_nVertexNum;i++ )
	{
		p1 = p0;	b1 = b0;
		k1 = i;		k4 = k1 + 1;
		k3 = k3 - 1;	k2 = k3 + 1;

		if( k2 >= m_nVertexNum )
			k2 = 0;
		if( k4 >= m_nVertexNum )
			k4 = 0;

		k1 += m_nVertexNum;
		k4 += m_nVertexNum;

		b0++;	m_Body.B[b0].m_nFirstVert = k1;	m_Body.B[b0].m_nSecVert = k2;
		b0++;	m_Body.B[b0].m_nFirstVert = k2;	m_Body.B[b0].m_nSecVert = k3;
		b0++;	m_Body.B[b0].m_nFirstVert = k3;	m_Body.B[b0].m_nSecVert = k4;
		b0++;	m_Body.B[b0].m_nFirstVert = k4;	m_Body.B[b0].m_nSecVert = k1;

		p0++;
		m_Body.P[p0].m_nFirstEdge = b1 + 1;
		m_Body.P[p0].m_nSecEdge = b0;
	}

	for( i=0; i<=p0; i++ )
	{
		k = m_Body.P[i].m_nFirstEdge;
		l1 = m_Body.B[k].m_nFirstVert;
		l2 = m_Body.B[k+1].m_nFirstVert;
		l3 = m_Body.B[k+2].m_nFirstVert;

		v1.x = m_Body.V[l1].x;
		v1.y = m_Body.V[l1].y;
		v1.z = m_Body.V[l1].z;

		v2.x = m_Body.V[l2].x;
		v2.y = m_Body.V[l2].y;
		v2.z = m_Body.V[l2].z;
		
		v3.x = m_Body.V[l3].x;
		v3.y = m_Body.V[l3].y;
		v3.z = m_Body.V[l3].z;

		v2.x -= v1.x;
		v3.x -= v1.x;

		v2.y -= v1.y;
		v3.y -= v1.y;
		
		v2.z -= v1.z;
		v3.z -= v1.z;

		m_Body.R[i].A = v2.y * v3.z - v3.y * v2.z;
		m_Body.R[i].B = -v2.x * v3.z + v3.x * v2.z;
		m_Body.R[i].C = v2.x * v3.y - v3.x * v2.y;
		m_Body.R[i].D = -v1.x * m_Body.R[i].A - v1.y * m_Body.R[i].B - v1.z * m_Body.R[i].C;

	}
}

void CDrawLineDoc::CheckPoint( void )
{
	CPointCoordDialog	myD;
	struct VERTEX		v0;
	double		d0=0;
	int			i, bimbo=0;

	myD.DoModal();

	v0.x = myD.m_dXCoord;
	v0.y = myD.m_dYCoord;
	v0.z = myD.m_dZCoord;

	for( i=0; i<m_nVertexNum+2; i++ )
	{
		d0 = v0.x * m_Body.R[i].A + v0.y * m_Body.R[i].B + v0.z * m_Body.R[i].C + m_Body.R[i].D;
		if( d0 < 0 )
		{
			AfxMessageBox("Toèka je IZVAN prizme !!!");
			bimbo = 1;
			break;
		}
	}

	if( bimbo != 1 )
		AfxMessageBox("Toèka je UNUTAR prizme !!!");
}

int CDrawLineDoc::GetBodyVertNum( void )
{
	return m_Body.N;
}

BODY_POLY	CDrawLineDoc::GetPoly( int i )
{
		return m_Body.P[i];
}

BODY_EDGE	CDrawLineDoc::GetEdge( int i )
{
		return m_Body.B[i];
}

VERTEX	CDrawLineDoc::GetVert( int i )
{
		return m_Body.V[i];
}

void	CDrawLineDoc::SetPolyVisibility( int i, int nVis )
{
	if( m_Body.N > 0 )
		m_Body.P[i].m_nVisible = nVis;
}

void CDrawLineDoc::OnBezierFunc() 
{
	// TODO: Add your command handler code here
	m_nExerciseNum = 9;
	m_nVertexNum = 0;

	AfxMessageBox("   Pomoæu miša odredi poligona pomoæu \n     kojeg æe se generirati krivulje. \n Za odreðivanje zadnje toèke, koristi desni botun. ");
}


void CDrawLineDoc::OnQuadFunc() 
{
	// TODO: Add your command handler code here
	m_nExerciseNum = 7;
	AfxMessageBox("  Mišem odredi tri toèke pomoæu kojih \n     æe se odrediti krivulja");
}

