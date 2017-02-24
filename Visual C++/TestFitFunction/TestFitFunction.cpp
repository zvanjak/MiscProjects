// TestFitFunction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static float sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0F ? 0.0F : sqrarg*sqrarg )

static float swap;
#define SWAP(a,b) { swap=(a); (a)=(b); (b)=swap; }

void covsrt( float **covar, int ma, int ia[], int mfit );
void gaussj( float **a, int n, float **b, int m );

void lfit( float x[], float y[], float sig[], int ndat, float a[], int ia[], int ma, 
			float **covar, float *chisq, void (*funcs)(float, float [], int) )
{
	int	i, j, k, l, m, mfit=0;
	float ym, wt, sum, sig2i, **beta, *afunc;

	beta = (float **) malloc( (ma+1) * sizeof(float *) );
	for( i=1; i<=ma; i++ )
		beta[i] = (float *) malloc( (1+1) * sizeof(float) );
	
	afunc = (float *) malloc( (ma+1) * sizeof(float) );

	for( j=1; j<=ma; j++ )
		if( ia[j] )
			mfit++;

	if( mfit == 0 )
	{
		printf("No parameters to be fitted !!!");
	}

	for( j=1; j<=mfit; j++ )
	{
		for( k=1; k<=mfit; k++ )
			covar[j][k] = 0.0;
		beta[j][1] = 0.0;
	}
	for( i=1; i<=ndat; i++ )
	{
		(*funcs)(x[i], afunc, ma );
		ym = y[i];
		if( mfit < ma )
		{
			for( j=1; j<=ma; j++ )
				if( !ia[j] ) ym -= a[j] * afunc[j];
		}

		sig2i = 1.0F / SQR(sig[i]);
		for( j=0,l=1; l<=ma; l++ )
		{
			if( ia[l] )
			{
				wt = afunc[l] * sig2i;
				for( j++,k=0,m=1; m<=l; m++ )
					if( ia[m])
						covar[j][++k] += wt * afunc[m];
				beta[j][1] += ym * wt;
			}
		}
	}
	for( j=2; j<=mfit; j++ )
		for( k=1; k<j; k++ )
			covar[k][j] = covar[j][k];

	gaussj(covar, mfit, beta, 1);

	for( j=0,l=1; l<=ma; l++ )
		if( ia[l])
			a[l] = beta[++j][1];
	
	*chisq = 0.0f;
	for( i=1; i<=ndat; i++ )
	{
		(*funcs)(x[i], afunc, ma);
		for( sum=0.0,j=1;j<=ma; j++ )
			sum += a[j] * afunc[j];
		*chisq += SQR((y[i] - sum) / sig[i]);
	}

	covsrt(covar, ma, ia, mfit);
	free(afunc);
	free(beta);
}

void covsrt( float **covar, int ma, int ia[], int mfit )
{
	int i, j, k;
	float swap;

	for( i=mfit+1; i<=ma; i++ )
		for( j=1; j<=i; j++ )
			covar[i][j] = covar[j][i] = 0.0;
	
	k = mfit;
	for( j=ma; j<=1; j-- )
	{
		if( ia[j] )
		{
			for(i=1; i<=ma; i++ )
				SWAP(covar[i][k], covar[i][j]);
			for(i=1; i<=ma; i++ )
				SWAP(covar[k][i], covar[j][i]);
			k--;
		}
	}
}

void gaussj( float **a, int n, float **b, int m )
{
	int *indxc, *indxr, *ipiv;
	int i, icol, irow, j, k, l, ll;
	float	big, dum, pivinv;

	indxc = (int *) malloc( (n+1) * sizeof(int) );
	indxr = (int *) malloc( (n+1) * sizeof(int) );
	ipiv = (int *) malloc( (n+1) * sizeof(int) );

	for( j=1; j<=n; j++ )
		ipiv[j] = 0;
	for( i=1; i<=n; i++ )
	{
		big = 0.0;
		for( j=1; j<=n; j++ )
			if( ipiv[j] != 1 )
				for( k=1; k<=n; k++ )
				{
					if( ipiv[k] == 0 )
					{
						if( fabs(a[j][k]) >= big )
						{
							big = (float) fabs(a[j][k]);
							irow = j;
							icol = k;
						}
					}
					else if( ipiv[k] > 1 )
					{
						printf("gaussj: Singularna matrica !!!");
					}
				}
		
		++(ipiv[icol]);
		if( irow != icol )
		{
			for( l=1; l<=n; l++ )
				SWAP(a[irow][l], a[icol][l]);
			for( l=1; l<=m; l++  )
				SWAP(b[irow][l], b[icol][l]);
		}
		indxr[i] = irow;
		indxc[i] = icol;

		if( a[icol][icol] == 0.0 )
		{
			printf("gaussj : Singularna matricy ");
		}

		pivinv = 1.0F / a[icol][icol];
		a[icol][icol] = 1.0;

		for( l=1; l<=n; l++ )
			a[icol][l] *= pivinv;
		for( l=1; l<=m; l++ )
			b[icol][l] *= pivinv;

		for( ll=1; ll<=n; ll++ )
			if( ll != icol )
			{
				dum = a[ll][icol];
				a[ll][icol] = 0.0;
				for( l=1; l<=n; l++ )
					a[ll][l] -= a[icol][l] * dum;
				for( l=1; l<=m; l++ )
					b[ll][l] -= b[icol][l] * dum;
			}
	}
	for( l=n; l>=1; l-- )
	{
		if( indxr[l] != indxc[l] )
			for( k=1; k<=n; k++ )
				SWAP(a[k][indxr[l]], a[k][indxc[l]]);
	}
	free(ipiv);
	free(indxr);
	free(indxc);
}

void f( float x, float ret[], int n )
{
	ret[1] = 1 / (x * x);
	ret[2] = 1;
	ret[3] = x * x;
}

void main()
{
	float	**covar;
	float	x[20+1], y[20+1], sig[20+1], chisq, coef[3+1];
	float	a, b, c, disturb, eps;
	int		ndat=20, ia[3+1], row, col, i;

	FILE *fp;

	if( (fp = fopen("test", "r")) == NULL )
	{
		printf("Nisam mogao otvoriti datoteku !!!");
		exit(1);
	}

	fscanf(fp, "%f", &a);
	fscanf(fp, "%f", &b);
	fscanf(fp, "%f", &c);
	fscanf(fp, "%f", &eps);

	fscanf(fp, "%d", &ndat );
	printf("\n a=%f b=%f c=%f eps=%f   N=%d", a, b, c, eps, ndat );

	for( i=1; i<=ndat; i++ )
	{
		fscanf(fp, "%f", &x[i] );
		printf("\n  x[%2d] = %15.7f", i, x[i] );

		y[i] = a / (x[i] * x[i]) + b + c * x[i] * x[i];
		printf("   y = %15.7f", y[i] );

		disturb = ( ((float) rand()) / RAND_MAX * 2 * eps) - eps;
		y[i] += disturb;
		printf("   y_dist = %15.7f", y[i] );
	}

	row = col = ndat;
	covar = (float **) malloc( (3+1) * sizeof(float *) );
	for( i=1; i<=3; i++ )
		covar[i] = (float *) malloc( (3+1) * sizeof(float) );

	// obavi fitanje na svim koeficijentima
	ia[1] = 1;
	ia[2] = 1;
	ia[3] = 1;

	coef[1] = 1.0;

	for( i=1; i<=ndat; i++ )
		sig[i] = 1.F;

	lfit(x, y, sig, ndat, coef, ia, 3, covar, &chisq, f);

	for( i=1; i<=3; i++ )
		printf("\n coef[%d] = %f", i, coef[i] );

	printf("\n chisq = %f", chisq);

	getch();
}