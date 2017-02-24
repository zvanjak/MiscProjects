#include <windows.h>
#include <wincon.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>


#define RP	3
#define BR_PRED			8
#define BR_ROK			3
#define BR_TERMINA	20

#define BR_ITER			3
#define	EXPONENT		0.3
#define PRINT_CONFIG_AFTER_TEMP_CHANGES	1000

int			X[BR_PRED][BR_ROK];
HANDLE	hConsOut;
double	dAcceptHigherProb;
double	E, T;

int			HelpX[BR_PRED][BR_ROK];

double	adAccept[4] = { 0.5, 0.7, 0.9, 0.95 };
double	adTempChange[5] = { 0.9, 0.92, 0.95, 0.98, 0.99 };
int			anPermNum[5] = { 30, 50, 70, 100, 150 };

double	adCoefA[4] = { 1.0, 3.0, 5.0, 12.0 };
double	adCoefB[4] = { 1.0, 3.0, 5.0, 12.0 };
int			It1, It2;

int BrRok, vpp[BR_PRED][BR_PRED];

void		InitialPosition();
double	CalcE( int *M );
double	ConfigChange();
void		AcceptNewConfig();
void		PrintConfig();
double	AverageEnergyInc();
int			CmpFunc(const void *a, const void *b);
bool		IstiTermin( int pred, int *M );

double Calc(int npredmeta, int pred[], int rp, int vpp[][BR_PRED], char *termin, int rok[][BR_ROK] );

void main( void )
{
	int		i, j, k;
	int		m, n, l;
	int		TempChangesNum = 0;
	int		PermNum = 10;
	char	ImeDat[30];
	double	dE;
	double	dTempChangeFactor;

	double	maxE=-1e30, totE=0, minE=1e30;

	hConsOut = GetStdHandle(STD_OUTPUT_HANDLE);

	FILE *fp;

//	fp = fopen("Rjesenje", "w");

/*	for( i=0; i<1000000; i++ )
	{
		InitialPosition();
		E = CalcE(&X[0][0]);

		totE += E;

		if( E > maxE )
			maxE = E;
		if( E < minE )
			minE = E;
	}
	printf("\n Max E   = %lf", maxE );
	printf("\n Min E   = %lf", minE );
	printf("\n Average = %lf", totE / 1000000 );
	
	for( i=0; i<8; i++ )
		for( k=0; k<3; k++ )
			X[i][k] = i + 6*k;
	
	PrintConfig();
	printf("\nEnergy = %lf", CalcE(&X[0][0]));
*/	
	for( It1=0; It1<4; It1++ ) 
	{
		for( It2=0; It2<4; It2++ )
		{
			memset(ImeDat, 0, 30);
			sprintf(ImeDat, "Rjesenje%02d%02d.txt", It1, It2);

			fp = fopen(ImeDat, "w");

			for( m=0; m<4; m++ )
			{
				for( n=0; n<5; n++ )
				{
					for( l=0; l<5; l++ )
					{
						// za svaku vrijednost æemo izraèunati dva puta
						fprintf(fp, "Accept  = %lf\n", adAccept[m] );
						fprintf(fp, "TempChg = %lf\n", adTempChange[n] );
						fprintf(fp, "PermNum = %d\n", anPermNum[l] );
						for( int pon=0; pon<BR_ITER; pon++ )
						{
							InitialPosition();

							dAcceptHigherProb = adAccept[m];
							dTempChangeFactor = adTempChange[n];
							E = CalcE(&X[0][0]);
							T = AverageEnergyInc() / log ( 1 / dAcceptHigherProb );
							
							TempChangesNum = 10000;
							PermNum = anPermNum[l];

							PrintConfig();
							printf("\n Iteracija : %d", pon );

							for( i=0; i<TempChangesNum; i++ )
							{
								// ukoliko je temperatura dosta pala, prekini daljnje raèunanje
								if( T < 0.000001 )
									break;

								for( j=0; j<PermNum; j++ )
								{
									dE = ConfigChange();
									if( dE < 0 )
									{
										AcceptNewConfig();
										E += dE;
									}
									else if(  (100 * exp(-dE / T)) > (rand() % 100)  )
									{
										AcceptNewConfig();
										E += dE;
									}
								}
								T = dTempChangeFactor * T;
								
								if( i % PRINT_CONFIG_AFTER_TEMP_CHANGES == 0 )
								{
									PrintConfig();
									printf("\n TempChang : %d", i );
									printf("\n Iteracija : %d", pon );
								}
							}
							PrintConfig();
							printf("\n Iteracija : %d", pon );

							fprintf(fp, "Energy  = %lf\n", E );

							for( i=0; i<BR_PRED; i++ )
							{
								for( j=0; j<BR_ROK; j++ )
									fprintf(fp, " %5d ", X[i][j]+1 );
								fprintf(fp, "\n");
							}

						}
					}
				}
			}
		}
		fclose(fp);
	}
}

void InitialPosition()
{
	int				i, j;
	clock_t		start;

	start = clock();

  srand( (unsigned) start );
//  srand( (unsigned) time(NULL) );

	i = 0;
	do
	{
		// najprije sluèajno dodijeli termine
		for( j=0; j<BR_ROK; j++ )
			X[i][j] = rand() % BR_TERMINA;

		// treba provjeriti da li su predmetu za razlièite rokove dodijeljena dva ista termina
		if( IstiTermin(i, &X[0][0]) != true )
			i++;
	}
	while(i<BR_PRED);
}

bool	IstiTermin( int pred, int *M )
{
	int		j;
	bool	bPonovo;

	// sortiraj termine rokova po danima
	qsort(&M[pred*BR_ROK], BR_ROK, sizeof(int), CmpFunc);
	
	bPonovo = false;
	// a sada æemo provjeriti da li imamo dva termina zajedno
	for( j=0; j<BR_ROK-1; j++ )
		if( M[pred*BR_ROK + j] == M[pred*BR_ROK + j+1] )
			bPonovo = true;

	return bPonovo;
}

double ConfigChange()
{
	int			pred, pomak, rok, stari_term;
	double	ret;

ponovo:
	memcpy(HelpX, X, BR_PRED * BR_ROK * sizeof(int) );

	// najprije sluèajno odaberi jedan predmet
	pred = rand() % BR_PRED;

	// zatim sluèajno odaberi jedan od termina predmeta
	rok = rand() % BR_ROK;

	// a zatim odaberi pomak tog predmeta
	pomak = rand() % 2;
	if( pomak == 0 )
		pomak = -1;
	else
		pomak = +1;

	// zapamti stari termin
	stari_term = HelpX[pred][rok];

	HelpX[pred][rok] += pomak;		// sada pomakni temrin

	// ukoliko smo ga makli previše "nazad"
	if( HelpX[pred][rok] < 0 )
		HelpX[pred][rok] = BR_TERMINA - 1;			// stavi termin na kraj
	
	// ako smo ga makli previše "naprijed"
	if( HelpX[pred][rok] >= BR_TERMINA )
		HelpX[pred][rok] = 0;									// stavi ga na poèetak

	if( IstiTermin(pred, &HelpX[0][0]) == true )
	{
		HelpX[pred][rok] = stari_term;
		goto ponovo;
	}

	ret = CalcE(&HelpX[0][0]);

	return ret - E;;
}

void AcceptNewConfig()
{
	memcpy(X, HelpX, BR_PRED * BR_ROK * sizeof(int) );
	for( int i=0; i<BR_PRED; i++ )
		qsort(X[i], BR_ROK, sizeof(int), CmpFunc);
}

int _cdecl CmpFunc(const void *a, const void *b)
{
	return ( *(int *)a > *(int *)b );
}

double AverageEnergyInc()
{
	double	dTotEnergy, dE;
	int		i, nNum;

	dTotEnergy=0;
	nNum=0;
	for( i=0; i<100; i++ )
	{
		dE = ConfigChange();
		if( dE > 0 )
		{
			dTotEnergy += dE;
			nNum++;
		}
	}
	return (dTotEnergy/nNum);
}

void PrintConfig()
{
	int		i, j, k;
//	bool	bFlag;

	COORD	coord;
	coord.X = 0;
	coord.Y = 0;

	SetConsoleCursorPosition(hConsOut, coord);

	printf("        |");
	for( j=0; j<BR_TERMINA; j++ )
		printf("  %2d ", j+1 );
	printf("\n------------------------------------------------------------------------------------------------------------");
	
	for( i=0; i<BR_PRED; i++ )
	{
		printf("\n PRED%01d  | ", i+1);
		printf("                                                                                                  ");
		for( j=0; j<BR_TERMINA; j++ )
		{

//			bFlag = false;
			
			for( k=0; k<BR_ROK; k++ )
			{
				coord.X = 12 + X[i][k] * 5;
				coord.Y = 2*i + 2;

				SetConsoleCursorPosition(hConsOut, coord);
				printf("*");
			}
/*				if( X[i][k] == j )
				{
					printf("  *  ");
					bFlag = true;
				}
			
			if( bFlag != true )
				printf("     ");
*/
		}
		printf("\n------------------------------------------------------------------------------------------------------------");
	}
	printf("\n                                                                                                            ");
	printf("\n                                                                                                            ");
	printf("\n Energy = %lf", E );

	printf("\n Temp   = %lf", T );
	printf("\n                                                                                                            ");

	for( i=0; i<BR_PRED; i++ )
	{
		printf("\n");
		for( j=0; j<BR_ROK; j++ )
			printf(" %5d ", X[i][j]+1 );
	}
}

double CalcE( int *M )
{
	int			i, j, k;
	double	ret = 0;

	// najprije za sve predmete zbroji udaljenost izmeðu dva termina za ispit
	for( i=0; i<BR_PRED; i++ )
		for( j=0; j<BR_ROK-1; j++ )
			ret += adCoefA[It1] * fabs( pow(M[i*BR_ROK+j+1] - M[i*BR_ROK+j], EXPONENT)); // * (M[x*RP+j]i][0] - M[x*RP+j]i][1]);
	
	// a ovdje æemo kazniti blizinu termina za predmete 1 i 2
/*
	ret += pow(fabs(M[0*BR_ROK+0] - M[1*BR_ROK+0]), 0.5);
	for( i=1; i<BR_ROK-1; i++ )
		ret += 15 * pow(fabs(M[0*BR_ROK+i] - M[1*BR_ROK+i-1]), 0.5) + pow(fabs(M[1*BR_ROK+i] - M[0*BR_ROK+i]), 0.5);
*/	
//	for( i=0; i<BR_ROK; i++ )
//			ret += fabs(M[0*BR_ROK+i] - M[1*BR_ROK+i]);

	// a sada æemo opæenito kazniti meðusobnu blizinu bilo koja dva predmeta
	for( i=0; i<BR_PRED; i++ )
		for( j=0; j<BR_PRED; j++ )
		{
			if( i != j )
			{
				ret += pow(fabs(M[i*BR_ROK+0] - M[j*BR_ROK+0]), EXPONENT);
				for( k=1; k<BR_ROK-1; k++ )
					ret += adCoefB[It2] * pow(fabs(M[i*BR_ROK+k] - M[j*BR_ROK+k-1]), EXPONENT) + pow(fabs(M[j*BR_ROK+k] - M[i*BR_ROK+k]), EXPONENT);
			}
		}

	return -ret;
}

int fakt ( int n) {
	int i, f;
	f = 1;
	for (i = 1; i <= n; i++) f  *= i;
	return f;
}

int mn (int m, int n) {
	int mpn;
	mpn = fakt (m) / fakt (n) / fakt (m-n);
	return mpn;
}

double Calc(int npredmeta, int pred[], int br_rok, int vpp[][BR_PRED], char *termin, int rok[][BR_ROK] )
{
	int	i, j, k, l, j1, j2;
	double	tezina, ret=0;
	int	term1, term2;
	FILE *fp;

	fp = fopen("FuncCalc", "w");

	for( i=0; i<npredmeta-1; i++ )
		for( j=i+1; j<npredmeta; j++ )
			for( k=0; k<RP; k++ )
				for( l=0; l<RP; l++ )
				{
					j1 = rok[i][k];
					j2 = rok[j][l];
//					tezina = fabs ((rbr (j2, termin) - rbr (j1, termin)));
					tezina = fabs (j2 - j1);
					tezina = pow ( tezina, 0.5);
					tezina = vpp [i][j] * tezina;

					if( j1 < 10 )
						term1 = '0' + j1;
					else
						term1 = 'A' + j1 - 10;
					if( j2 < 10 )
						term2 = '0' + j2;
					else
						term2 = 'A' + j2 - 10;

					fprintf(fp, "%c%03d%c%03d    %f\n", term1, pred[i],term2 , pred[j], tezina);
					ret += tezina;
				}

	// Sami sa sobom
	for( i=0; i<npredmeta; i++ )
		for( j=0; j<RP-1; j++ )
			for( k=j+1; k<RP; k++ )
			{
				j1 = rok[i][j];
				j2 = rok[i][k];

//				tezina = fabs( rbr (j2, termin) - rbr (j1, termin));
				tezina = fabs( j2 - j1);
				tezina = pow ( tezina, 0.5);
				tezina = BrRok * BrRok / mn (BrRok, 2) * tezina;
				tezina = vpp [i][i] * tezina;

				if( j1 < 10 )
					term1 = '0' + j1;
				else
					term1 = 'A' + j1 - 10;
				if( j2 < 10 )
					term2 = '0' + j2;
				else
					term2 = 'A' + j2 - 10;

				fprintf(fp, "%c%03d%c%03d    %f\n", term1, pred[i],term2 , pred[i], tezina);
				ret += tezina;
			}

	return ret;
}
