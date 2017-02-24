#include "stdafx.h"
#include "DrawLine.h"

//#include "struct.h"

#include "DrawLineDoc.h"
#include "DrawLineView.h"

#include	<stdio.h>
#include	<math.h>
#include	<string.h>

#include	"matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix( UINT RowNum, UINT ColNum )
	{
		unsigned int     i;

		m_nRowNum = (RowNum > 0) ? RowNum : 0;
		m_nColNum = (ColNum > 0) ? ColNum : 0;

		if( m_nRowNum>0 )
			{
				if( !(m_pdElem = new double  *[m_nRowNum]) )         /* rezerviraj mjesto za 'm' pokazivaüa na 'm' redaka */
					{				// nema memorije
					}
        else
					for( i=0; i<m_nRowNum; i++ )        
						if( m_nColNum > 0 )     
							{
								if( !(m_pdElem[i] = new double[m_nColNum] ) )
									{					// nema memorije
									}
								else
									for( unsigned int j=0; j<m_nColNum; j++ )
										m_pdElem[i][j] = 0;
							}
						else
							m_pdElem[i] = NULL;
			}
		else                         
			{				// krivi broj redaka
			}
    }

Matrix::Matrix(	const Matrix &Copy )
	{
		unsigned int     i;

		if( Copy.m_nRowNum <= 0 )
			{				// krive dmenzije matrice
			}

		if( Copy.m_pdElem != NULL )
     	{
				m_nRowNum = (Copy.m_nRowNum > 0) ? Copy.m_nRowNum : 0;
				m_nColNum = (Copy.m_nColNum > 0) ? Copy.m_nColNum : 0;

				if( !(m_pdElem = new double    *[m_nRowNum]) )         /* rezerviraj mjesto za 'm' pokazivaüa na 'm' redaka */
					{				// nema memorije
					}
				else
					{
						for( i=0; i<m_nRowNum; i++ )
							if( Copy.m_nColNum > 0 )
								{
									if( !(m_pdElem[i] = new double[m_nColNum] ) )
										{				// nema memorije
										}
									else
										memmove( m_pdElem[i], Copy.m_pdElem[i], sizeof(double) * Copy.m_nColNum );
								}
							else
								m_pdElem[i] = NULL;
					}
			}                                                   
	}

Matrix::~Matrix()
	{                       
		unsigned int		i;
    	     
		if( m_pdElem != NULL )
			{                             
				if( m_nColNum != 0 )
					{
						for( i=0; i<m_nRowNum; i++ )        
							if( m_pdElem[i] != NULL )
							{
								delete []m_pdElem[i];
							}
					}
				if ( m_nRowNum != 0 )
					{
						delete []m_pdElem;
						m_pdElem = NULL;
					}                                    
			}
	}

UINT	RowNum( const Matrix &a )
{
	return	a.m_nRowNum;
}

UINT	ColNum( const Matrix &a )
{
	return	a.m_nColNum;
}

double	Elem( const Matrix &a, UINT i, UINT j )
	{
		if( i>=0 && i<RowNum(a) && j>=0 && j<ColNum(a) )
			return ( a.m_pdElem[i][j] );
		else
			return	a.m_pdElem[0][0];
	}

/********************************************************************************************/

Matrix  Matrix::operator+( const Matrix &b ) const
	{
		Matrix  ret(m_nRowNum,m_nColNum);

		if( m_nRowNum == b.m_nRowNum && m_nColNum==b.m_nColNum )
			{
				for( unsigned int i=0; i<m_nRowNum; i++ )
					for( unsigned int j=0; j<m_nColNum; j++ )
						ret.m_pdElem[i][j] = m_pdElem[i][j] + b.m_pdElem[i][j];
			}
		else
			{			// kriva dimenzija matrice
			}

		return ret;
	}

Matrix  Matrix::operator-( const Matrix &b ) const
	{
		Matrix  ret(m_nRowNum,m_nColNum);

		if( m_nRowNum == b.m_nRowNum && m_nColNum==b.m_nColNum )
			{
				for( unsigned int i=0; i<m_nRowNum; i++ )
					for( unsigned int j=0; j<m_nColNum; j++ )
						ret.m_pdElem[i][j] = m_pdElem[i][j] - b.m_pdElem[i][j];
			}
		else
			{			// kriva dimenzija matrice
			}

		return ret;
	}

Matrix  Matrix::operator*( const	Matrix &b ) const
	{
		Matrix	ret(m_nRowNum, b.m_nColNum);

		if( m_nColNum==b.m_nRowNum )
			{
				for( unsigned int i=0; i<ret.m_nRowNum; i++ )
					for( unsigned int j=0; j<ret.m_nColNum; j++ )
						{
							ret.m_pdElem[i][j] = 0;
							for(unsigned int k=0; k<m_nColNum; k++ )
								ret.m_pdElem[i][j] += m_pdElem[i][k] * b.m_pdElem[k][j];
						}
			}
		else
			{				// krive dimenzije matrice
			}

		return	ret;
	}

Matrix	operator*( const double a, const Matrix &b ) 
	{   
		Matrix	ret(b.m_nRowNum, b.m_nColNum);
		unsigned int		i,j;

		for( i=0; i<b.m_nRowNum; i++ )
			for( j=0; j<b.m_nColNum; j++ )
				ret.m_pdElem[i][j] = b.m_pdElem[i][j] * a;

		return	ret;
	}

Matrix	operator*( const Matrix &a, const double b )
	{   
		Matrix	ret(a.m_nRowNum, a.m_nColNum);
		unsigned int		i,j;

		for( i=0; i<a.m_nRowNum; i++ )
			for( j=0; j<a.m_nColNum; j++ )
				ret.m_pdElem[i][j] = a.m_pdElem[i][j] * b;

		return	ret;
	}
	
/*Matrix  Matrix::operator/( const Matrix &b ) const
	{
		Matrix	Ret(m,m,"Div");
		
		if( m==n && b.m==m && b.n==n )
			Ret = *this * b.Inv();
		else
			Error(_MATRIX_DIMENSION_WRONG);
		
		return	Ret;
    }*/

Matrix& Matrix::operator=( const	Matrix &b )
	{
		unsigned int		i;

		if( m_pdElem != NULL && b.m_pdElem != NULL )
			{
				if( m_nRowNum != b.m_nRowNum || m_nColNum != b.m_nColNum )       	/* ako matrice koje se pridruûuju nisu iste dimenzije */
					{
						for( i=0; i < m_nRowNum; i++ )		/* stare dimenzije izbriöi i ustanovi nove */
							if( m_pdElem[i] != NULL )
								delete m_pdElem[i];
						if( m_pdElem != NULL )
							delete m_pdElem;
						
						m_nRowNum = b.m_nRowNum;
						m_nColNum = b.m_nColNum;
						
						if( !(m_pdElem= new double   *[m_nRowNum]) )
							for( i=0; i < m_nRowNum; i++ )
								if( (m_pdElem[i] = new double[m_nColNum]) == NULL)
									{				// nema memorije
										for( unsigned int j=0; j < i; j++ )
											delete m_pdElem[j];
										delete m_pdElem;
									}
						else
							{				// nema memorije
							}
					}
				for(i=0; i<m_nRowNum; i++ )
					memmove(m_pdElem[i], b.m_pdElem[i], sizeof(double) * b.m_nColNum );
			}

		return *this;
	}

double	Matrix::GetElem( int i, int j )
{
	return m_pdElem[i][j];
}

void	Matrix::SetElem( int i, int j, double dValue )
{
	m_pdElem[i][j] = dValue;
}

void	Matrix::MakeUnitMatrix( void )
{
	if( m_nRowNum == m_nColNum )
	{
		for( unsigned int i=0; i<m_nRowNum; i++ )
			for( unsigned int j=0; j<m_nColNum; j++ )
				if( i == j )
					m_pdElem[i][j] = 1;
				else
					m_pdElem[i][j] = 0;
	}
}

void	Matrix::Clear( void )
{
	for( unsigned int i=0; i<m_nRowNum; i++ )
		for( unsigned int j=0; j<m_nColNum; j++ )
			m_pdElem[i][j] = 0;
}