typedef	unsigned int UINT;

class	Matrix
{
	private:
		UINT	m_nRowNum, m_nColNum;
		double	**m_pdElem;

	public:
		Matrix();
		Matrix( UINT rows, UINT cols );
		Matrix( const Matrix &Copy );
		~Matrix();


		Matrix		operator+( const Matrix &b ) const;
		Matrix		operator-( const Matrix &b ) const;
		Matrix		operator*( const Matrix &b ) const;
		Matrix&		operator=( const Matrix &b );

		void		MakeUnitMatrix( void );
		void		Clear( void );
		double		GetElem( int i, int j );
		void		SetElem( int i, int j, double dValue );

		friend	Matrix	operator*( const double a,  const Matrix &b );
		friend	Matrix	operator*( const Matrix &a, const double b );
		
		friend	double	Elem( const Matrix &a, UINT i, UINT j );
		friend	UINT	RowNum( const Matrix &a );
		friend	UINT	ColNum( const Matrix &a );

		friend	Matrix	Transp( const Matrix &a );
		friend	Matrix	Invert( const Matrix &a );
		friend	Matrix	Solve( const Matrix &a );
		friend	void	Print( const Matrix &a );

		friend	Matrix	ToUpperTriang( const Matrix &a );
		friend	Matrix	ToLowerTriang( const Matrix &a );
};