#include <stdio.h>
#include <math.h>
#include <stdlib.h>

CVertex	FuncMinN( CVertex StartPoint, int nDim, double (*func) (double *) );


CVertex	FuncMinN( CVertex StartPoint, int nDim, double (*func) (double *) )
{
	int				bLower, IterNum=0;
	double			FuncVal, TempFuncVal, sum;
	unsigned int	i, j, h, l;
	CVertex			*Simplex[N+1], Xc(2), Xr(2), Xe(2), Xk(2);
	
	char			strFunc[100], DaNe;

	var1 = Mth.DefineVar( "x" );
	var2 = Mth.DefineVar( "y" );

start:
	printf("\n Unesi funkciju : "); scanf("%s", strFunc );
	FuncHandle = Mth.DefineFunction(strFunc);

	for( i=0; i<N+1; i++ )
		Simplex[i] = new CVertex(2);

	Simplex[0]->InitValues(0.0, 0.0);		// poèetni pokušaj rješenja
	Simplex[1]->InitValues(1.0, 0.0);
	Simplex[2]->InitValues(0.0, 1.0);

	do
	{
		// odredjivanje tocke u kojoj je funkcija najveca
		h=0;
		FuncVal = func(Simplex[h]);
		for( i=1; i<N+1; i++ )
			if( (TempFuncVal=func( Simplex[i] )) > FuncVal )
			{
				h=i;
				FuncVal = TempFuncVal;
			}

		// odredjivanje tocke u kojoj je funkcija najmanja
		l=0;
		FuncVal = func(Simplex[l]);
		for( i=1; i<N+1; i++ )
			if( (TempFuncVal=func( Simplex[i] )) < FuncVal )
			{
				l=i;
				FuncVal = TempFuncVal;
			}

 		// odredjivanje centroida
		Xc.InitValues(0.0, 0.0);
		for( i=0; i<N+1; i++ )
			if( i != h )
				Xc = *Simplex[i] + Xc;
		Xc =  (1/ (double) N) * Xc;

		// refleksija
		Xr = (1 + ALPHA) * Xc - ALPHA * (*Simplex[h]);

		if( func(&Xr) < func(Simplex[l]) )
		{
			// ekspanzija
			Xe = (1 - GAMA) * Xc + GAMA * Xr;
			if( func(&Xe) < func(Simplex[l]) )
			{
				*Simplex[h] = Xe;
			}
			else
			{
				*Simplex[h] = Xr;
			}
		}
		else
		{
			bLower = 1;
			for( j=0; j<N+1; j++ )
				if( j!= h )
					if( func(&Xr) < func(Simplex[j]) )
						bLower = 0;
			
			if( bLower == 1 )
			{
				if( func(&Xr) < func(Simplex[h]) )
				{
					*Simplex[h] = Xr;
				}
				// kontrakcija
				Xk = (1 - BETA) * Xc + BETA * (*Simplex[h]);
				if( func(&Xk) > func(Simplex[h]) )
				{
					for( j=0; j<N+1; j++ )
						if( j != l )
							*Simplex[j] = 0.5 * (*Simplex[j] + *Simplex[l]);
				}
				else
				{
					*Simplex[h] = Xk;
				}
			}
			else
			{
				*Simplex[h] = Xr;
			}
		}
		
		// da li rješenje zadovoljava
		sum = 0;
		for( j=0; j<N+1; j++ )
			sum += pow( (func(Simplex[j]) - func(&Xc)), 2 );

		sum /= N;
		sum = sqrt(sum);
		IterNum++;
	} while( sum > EPS );
	printf( "\nrjesenje je :  x = %f,  y=%f\n", Xc.Get(0), Xc.Get(1) );
	printf( "vrijednost funkcije f(x,y) = %f\n", func(&Xc) );
	printf( "broj iteracija = %d\n", IterNum );
	
	getch();
}