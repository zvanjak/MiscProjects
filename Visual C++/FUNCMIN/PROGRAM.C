#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define GS_CONST 0.61803399

double	func( double x );
void	FindUnimodal( double dStartPoint, double *A, double *B, double (*f) (double) );
double	GoldenSection( double A, double B, double Eps, double (*f) (double) );
double	Fibonacci( double A, double B, double Eps, double (*f) (double) );
double	QuadInterp( double A, double B, double Eps, double (*f) (double) );

void main( void )
{
	double	dRes, a, b;

	FindUnimodal(0.0, &a, &b, (double (*) (double))func );
	printf("\nGranice unimodalnog intervala su : %f - %f", a, b );

	dRes = GoldenSection(a,b, 1e-6, (double (*) (double))func );
	printf("\n\n Minimum (Zlatni rez)   je u x = %f", dRes );
	dRes = Fibonacci(a,b, 1e-6, (double (*) (double))func );
	printf("\n\n Minimum (Fibonacci)    je u x = %f", dRes );
	dRes = QuadInterp(a,b, 1e-6, (double (*) (double))func );
	printf("\n\n Minimum (Kvad.interp.) je u x = %f", dRes );

	getch();
}

double func( double x )
{
	return cos(x*x)*exp(-x/2);
}

void FindUnimodal( double dStart, double *A, double *B, double (*f) (double) )
{
	double	x0, F0, F_next, h, dDir;

	h = 0.1;
	x0= dStart;			// krenuti cemo od ishodista
	
	F0 = (*f)(x0);
	
	if( (*f)(x0+h) < F0 )
		dDir = 1;
	else if( (*f)(x0-h) < F0 )
		dDir = -1;
	else		// znaci da je u x0 lokalni minimum, jer je vrijednost funkcije s obe strane veca nego u x0
	{
		*A = x0 - h;
		*B = x0 + h;
		goto end;
	}

	do
	{
		F0 = (*f)(x0 + dDir * h);
		F_next = (*f)(x0 + dDir * (h*2));
		h *=2;
	} while( F_next < F0 );
	
	*A = x0 + dDir*h/4;
	*B = x0 + dDir*h;

end:
	;
}

double GoldenSection( double A, double B, double Eps, double (*f) (double) )
{
	double	C, D, Fc, Fd, dHelp;

	if( A > B )
	{
		dHelp = A;
		A = B;
		B = dHelp;
	}

	C = B - GS_CONST * ( B - A );
	D = A + GS_CONST * ( B - A );
	Fc = (*f)(C);
	Fd = (*f)(D);

	do
	{
		if( Fd > Fc )
		{
			B = D;
			D = C;
			C = B - GS_CONST * ( B - A );
			Fd = Fc;
			Fc = (*f)(C);
		}
		else
		{
			A = C;
			C = D;
			D = A + GS_CONST * ( B - A );
			Fc = Fd;
			Fd = (*f)(D);
		}
	} while( (B-A) > Eps );

	return ((A+B)/2);
}

double Fibonacci( double A, double B, double Eps, double (*f) (double) )
{
	double	dFib1, dFib2, dHelp, Delta;
	double	C, D, Fc, Fd;
	int		nStep, i;
	
	if( A > B )
	{
		dHelp = A;
		A = B;
		B = dHelp;
	}

	/* odredjivanje broja koraka */
	dFib1 = 1; dFib2 = 2; 
	nStep=0;
	do
	{
		dHelp = dFib2;
		dFib2 = dFib1 + dFib2;
		dFib1 = dHelp;
		nStep++;
	} while( (B - A) / dFib2 > Eps );

	Delta = dFib1 / dFib2 * (B - A);
	D = A + Delta;
	C = B - Delta;
	Fc = (*f)(C);
	Fd = (*f)(D);
	
	for( i=1; i<nStep; i++ )
	{
		dHelp = dFib1;
		dFib1 = dFib2 - dFib1;
		dFib2 = dHelp;

		if( Fd > Fc )
		{
			B = D;
			D = C;
			C = B - dFib1 / dFib2 * ( B - A );
			Fd = Fc;
			Fc = (*f)(C);
		}
		else
		{
			A = C;
			C = D;
			D = A + dFib1 / dFib2 * ( B - A );
			Fc = Fd;
			Fd = (*f)(D);
		}
	}
	
	return( (A+B)/2 );
}

double QuadInterp( double A, double B, double Eps, double (*f) (double) )
{
	double	C, D, Fa, Fb, Fc, Fd;
	double	dDown, dUp;

	if( A > B )
	{
		dUp = A;
		A = B;
		B = dUp;
	}

	C = ( A + B ) / 2;			// uzecemo trecu tocku, za pocetak, na sredini intervala

	Fa = (*f)(A);
	Fb = (*f)(B);
	Fc = (*f)(C);

	do
	{
		dUp = (C*C - B*B)*Fa + (A*A - C*C)*Fb + (B*B - A*A)*Fc;
		dDown = (C - B)*Fa + (A - C)*Fb + (B - A)*Fc;

		D = 0.5 * dUp / dDown;
		Fd = (*f)(D);

		if( D < C )
		{
			if( Fd < Fc )
			{
				B = C;	Fb = Fc;
				C = D;	Fc = Fd;
			}
			else
			{
				A = D;	Fa = Fd;
			}
		}
		else
		{
			if( Fd < Fc )
			{
				A = C;	Fa = Fc;
				C = D;	Fc = Fd;
			}
			else
			{
				B = D;	Fb = Fd;
			}
		}
	} while( (B-A) > Eps );

	return( (A+B)/2 );
}

