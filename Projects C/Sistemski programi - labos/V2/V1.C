#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define	N	3
#define	M	4

void proces( int i )
{
	int k,m;
	
	for( k=1; k<=5; k++ )
	{
		for( m=1; m<=M; m++ )
		{
			printf("\n Proces : %d,   korak : %d  -  %d", i, k, m );
			sleep(1);
		}
		printf("\n    Zavrsio s korakom %d,   procesa %d ", k, i );
	}
	printf("\n  ZAVRSIO PROCES  :  %d\n", i );
}

int main( void )
{
	int i;
	
	for( i=0; i<N; i++ )
		if( fork() == 0 )
		{
			printf("\n Pokrenut proces : %d", i );
			proces(i);
			exit(0);
		}
	for( i=0; i<N; i++ )
		(void) wait(NULL);

	exit(0);
}