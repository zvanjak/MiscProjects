#include <stdio.h>
#include <signal.h>

#define  N    10


int OZNAKA_CEKANJA[N];
int PRIORITET[N];
int TEKUCI_PRIORITET=0;


void ObradaPrekida( int j)
{
  printf("Poceo sam obradu prekida %d", j );
  sleep(10);
  printf("Zavrsio sam obradu prekida %d", j);
}

void PrekidnaRutina( int sig )
{
  int i,j;

  sighold(SIGINT);

  printf("Upisi razinu prekida : ");
  scanf("%d", &i );

  OZNAKA_CEKANJA[i] = 1;

  for( j = N-1; j >= 0; j-- )
    if( OZNAKA_CEKANJA[j] != 0  &&  j > TEKUCI_PRIORITET )
      {
	OZNAKA_CEKANJA[j] = 0;
	PRIORITET[j] = TEKUCI_PRIORITET;
	TEKUCI_PRIORITET = j;
	
	sigrelse(SIGINT);
	ObradaPrekida(j);
	sighold(SIGINT);
	
	TEKUCI_PRIORITET = PRIORITET[j];
	sigrelse(SIGINT);

	break;
      }
}

int main( void )
{
  signal(SIGINT, PrekidnaRutina);
  printf("\nPoceo osnovni program !!!\n");
  sleep(10);
  printf("\n Zavrsio osnovni program \n");
}






