#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

unsigned char Divide( char *Adr, short int P);
unsigned char GetNBits( char *Adr, int Start, int N );
void	ChangeBit( char *Adr, int i );

unsigned char* strText="\"ELEKTROTEHNIKA\"\0\0";
unsigned char* strTemp="\"ELEKTROTEHNIKA\"\0\0";
unsigned char nGen = 128 + 64 + 8 + 2 + 1;

void main( void )
{
	long	DetectedNum, TotalNum;
	int		i,j,k,m,n;
  unsigned char CRC, test;
	FILE *fp;

	if( (fp = fopen("reporte.txt", "w") ) == NULL )
	{
		puts("Greska");
		exit(0);
	}

  CRC = Divide(strText, nGen);
	strText[16] = CRC;
	strTemp[16] = CRC;

	DetectedNum = TotalNum = 0;

	for( i=0; i<136; i++ )
	{
		ChangeBit(strText, i);
		
		test = Divide(strText, nGen);
		if( test != CRC )
			DetectedNum++;
		TotalNum++;
		memcpy(strText, strTemp, 17);
	}
	printf("\n 1-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );
	fprintf(fp,"\n 1-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );

	DetectedNum = TotalNum = 0;

	for( i=0; i<136; i++ )
	{
		ChangeBit(strText, i);
		for( j=0; j<136; j++ )
		{
			ChangeBit(strText, j);
			
			test = Divide(strText, nGen);
			if( test != CRC )
				DetectedNum++;
			TotalNum++;
			memcpy(strText, strTemp, 17);
		}
	}
	printf("\n 2-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );
	fprintf(fp,"\n 2-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );

	DetectedNum = TotalNum = 0;
	for( i=0; i<136; i++ )
	{
		ChangeBit(strText, i);
		for( k=i; k<136; k++ )
		{
			ChangeBit(strText, k);
			for( j=k; j<136; j++ )
			{
				ChangeBit(strText, j);
				
				test = Divide(strText, nGen);
				if( test != CRC )
					DetectedNum++;
				TotalNum++;
				memcpy(strText, strTemp, 17);
			}
		}
	}
	printf("\n 3-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );
	fprintf(fp,"\n 3-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );
	fflush(fp);

/*	DetectedNum = TotalNum = 0;
	for( i=0; i<136; i++ )
	{
		printf("\n i = %d", i );
		ChangeBit(strText, i);
		for( m=i; m<136; m++ )
		{
			ChangeBit(strText, m);
			for( k=m; k<136; k++ )
			{
				ChangeBit(strText, k);
				for( j=k; j<136; j++ )
				{
					ChangeBit(strText, j);
					
					test = Divide(strText, nGen);
					if( test != CRC )
						DetectedNum++;
					TotalNum++;
					memcpy(strText, strTemp, 17);
				}
			}
		}
	}
	printf("\n 4-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );
	fprintf(fp,"\n 4-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );
	fflush(fp);*/
	
/*	DetectedNum = TotalNum = 0;
	for( i=0; i<136; i++ )
	{
		ChangeBit(strText, i);
		for( m=0; m<136; m++ )
		{
			ChangeBit(strText, m);
			for( k=0; k<136; k++ )
			{
				ChangeBit(strText, k);
				for( n=0; n<136; n++ )
				{
					ChangeBit(strText, n);
					for( j=0; j<136; j++ )
					{
						ChangeBit(strText, j);
						
						test = Divide(strText, nGen);
						if( test != CRC )
							DetectedNum++;
						TotalNum++;
						memcpy(strText, strTemp, 17);
					}
				}
			}
		}
	}
	printf("\n 5-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );
	fprintf(fp,"\n 5-bitne greske : %ld, %ld, %lf%% ", TotalNum, DetectedNum, ((float) DetectedNum/TotalNum)*100 );
*/
	fclose(fp);
	getch();
	}

void ChangeBit( char *Adr, int i)
{
	int	Byte, BitNum, num;
	unsigned char Mask;

	Byte = i / 8;
	BitNum = i % 8;
	
	Mask = 1;
  for( num=0; num < BitNum; num++ )
    Mask *= 2;

	if ( strText[Byte] & Mask )				/* znaèi da je bit na pocetku 1 */
		strText[Byte] = strText[Byte] & (~Mask);		/* pa ga promijeni na 0 */
	else
		strText[Byte] = strText[Byte] | Mask;			/* inace ga promijeni na 1 */
}

unsigned char Divide( char *Dand, short int P )
{
  unsigned char D1, Res, Inc, Bits;
  int   StartFrom=0;

  D1 = GetNBits(Dand, StartFrom, 8);		// uzmi 8 prvih bitova
  StartFrom += 8;

  while( StartFrom < 136 )
  {
    Res = D1 ^ P;				// XOR operacija
    Inc = 0;

    while( !(Res & 64) && Inc < 8 && (StartFrom+1+Inc)!=136 )     /* shift dok krajnji desni ne postane 1 */
    {
      Res <<= 1;
      Inc++;
    }

		Res <<= 1;			/* još jedan šift, da se napravi mjesta za bitove koje spuštamo */
    Bits = GetNBits(Dand, StartFrom, 1+Inc );
    StartFrom += (1+Inc);
    D1 = Res | Bits;
  }
	
	return D1;
}

unsigned char GetNBits( char *Adr, int StartFrom, int N )
{
  int Byte, Inc, BitsNum;
  int i;
  unsigned char Contents, Contents2, Mask;

  Byte = StartFrom / 8;
  Inc = StartFrom % 8;

  Adr += Byte;

  if( 8-Inc == N )
  {
    Mask = 1;
    for( i=0; i < (8-Inc); i++ )
      Mask *= 2;
    Mask -= 1;

    Contents = *Adr & Mask;
  }
  else if( 8-Inc < N )
  {
    Mask = 1;
    for( i=0; i < (8-Inc); i++ )
      Mask *= 2;
    Mask -= 1;

    Contents = *Adr & Mask;
    if( 8-Inc < N )
    {
      Adr++;
      BitsNum = N - (8-Inc);
      Contents = Contents << BitsNum;

      Mask = 1;
      for( i=0; i < BitsNum; i++ )
        Mask *= 2;
      Mask -= 1;

      Mask = Mask << (8-BitsNum);

      Contents2 = *Adr & Mask;
      Contents = Contents | Contents2;
    }
  }
  else
    {
      Mask = 1;
      for( i=0; i < N; i++ )
        Mask *= 2;
      Mask -= 1;

      Mask = Mask << (8-Inc-N);
      Contents = (*Adr & Mask) >> (8-Inc-N);
    }

  return  Contents;
}
