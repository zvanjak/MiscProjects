#ifndef __STRUCT
#define __STRUCT

#define	CLOCKWISE	1
#define	COUNTER_CLOCKWISE	2

struct VERTEX
{
	double	x;
	double	y;
	double	z;
	double	h;
};

struct VERTEX2D
{
	int		x;
	int		y;
};

struct COEF
{
	double	A, B, C;
};

struct PLANE_COEF
{
	double	A, B, C, D;
};

struct BODY_POLY
{
	int		m_nFirstEdge;
	int		m_nSecEdge;

	int		m_nVisible;
};

struct BODY_EDGE
{
	int		m_nFirstVert;
	int		m_nSecVert;
};

struct	BODY
{
	int		N;		// broj vrhova baze
	
	struct	BODY_POLY	*P;
	struct	BODY_EDGE	*B;
	struct	VERTEX		*V;
	struct	PLANE_COEF	*R;	
};

int	CheckDirection( int N, struct VERTEX *V );
double	ScalProd( struct VERTEX a, struct VERTEX b );
struct VERTEX	VectProd( struct VERTEX a, struct VERTEX b );
int	CheckPointInPoly( CPoint p, struct COEF *Coef, int N );

int LineWithEdgeIntersection( int N, struct VERTEX V0, struct COEF *Coef, struct COEF Line, struct VERTEX *V, double *S );
double	V32( struct VERTEX V1, struct VERTEX V2, struct VERTEX V3 );

//Matrix	GetProjectionMatrix( VERTEX vertEye, VERTEX vertView );

struct FRACTAL
{
	double		dEps;
	int			nMaxIter;
	int			nDx, nDy;
	double		dUmin, dUmax, dVmin, dVmax;		// podruèje kompleksne ravnine koje se promatra
	double		dCre, dCim;						// kompleksna konstanta (samo za Julia skup)
};

#endif // __STRUCT