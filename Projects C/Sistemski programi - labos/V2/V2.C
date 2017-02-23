#include <stdio.h>
#include <sys/types.h>
/* Dekkerov algoritam */

#include <sys/ipc.h>
#include <sys/shm.h>

#define	N	3
#define	M	5

int		*Pravo;
int		*Zastavica;

void proces( int i )
{
	int j,k,m;
	
	for( k=1; k<=5; k++ )
	{
		Zastavica[i] = 1;
		for( j=0; j<N; j++ )
			if( Zastavica[j] != 0 )
			{
				if( *Pravo == j )
				{
					Zastavica[i] = 0;
					while( *Pravo == j )
						;
					Zastavica[i] = 1;
				}
			}
		for( m=1; m<=M; m++ )
		{
			printf("\n Proces : %d   korak : %d  -  %d", i, k, m );
			sleep(1);
		}
		*Pravo = j;
		Zastavica[i] = 0;
		printf("\n    Zavrsio s korakom %d, procesa %d", k, i );
	}
	printf("\n ZAVRSIO PROCES  :  %d \n", i );
}

int main( void )
{
	int i;
	int	Id1, Id2;
	
	Id1 = shmget(IPC_PRIVATE, sizeof(int), 0600 );
	Id2 = shmget(IPC_PRIVATE, sizeof(int) * N, 0600 );
	
	if( Id1 == -1 | Id2 == -1 )
		exit(1);
		
	Pravo = (int *) shmat(Id1, NULL, 0);
	Zastavica = (int *) shmat(Id2, NULL, 0);
	
	for( i=0; i<N; i++ )
		if( fork() == 0 )
		{
			printf("\n Pokrenut proces : %d", i );
			proces(i);
			exit(0);
		}
	for( i=0; i<N; i++ )
		(void) wait(NULL);
		
	(void) shmdt( (char *) Pravo );
	(void) shmctl( Id1, IPC_RMID, NULL );
	
	(void) shmdt( (char *) Zastavica );
	(void) shmctl( Id2, IPC_RMID, NULL );

	exit(0);
}