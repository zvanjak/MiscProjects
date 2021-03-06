/*  Lamportov algoritam */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define	N	3
#define	M	4

int		*Trazim;
int		*Broj;

void proces( int i )
{
	int j,k,m, MaxBroj;
	
	for( k=1; k<=5; k++ )
	{
		Trazim[i] = 1;

		MaxBroj = Broj[0];
		for( j=0; j<N; j++ )
			if( Broj[j] > MaxBroj )
				MaxBroj = Broj[j];

		Broj[i] = MaxBroj + 1;
		Trazim[i] = 0;
		
		for( j=0; j<N; j++ )
		{
			while( Trazim[j] != 0 )
				;
			while( Broj[j] != 0 && ( (Broj[j]<Broj[i]) || (Broj[j]==Broj[i] && j<i) ) )
				;
		}
		for( m=1; m<=M; m++ )
		{
			printf("\n Proces : %d   korak : %d  -  %d", i, k, m );
			sleep(1);
		}
		printf("\n    Zavrsio s korakom %d, procesa %d", k, i );
		Broj[i] = 0;
	}
	printf("\n  ZAVRSIO PROCES  :  %d\n", i );
}

int main( void )
{
	int i;
	int	Id1, Id2;
	
	Id1 = shmget(IPC_PRIVATE, sizeof(int) * N, 0600 );
	Id2 = shmget(IPC_PRIVATE, sizeof(int) * N, 0600 );
	
	if( Id1 == -1 | Id2 == -1 )
		exit(1);
		
	Trazim = (int *) shmat(Id1, NULL, 0);
	Broj = (int *) shmat(Id2, NULL, 0);
	
	for( i=0; i<N; i++ )
		if( fork() == 0 )
		{
			printf("\n Pokrenut proces : %d", i );
			proces(i);
			exit(0);
		}
	for( i=0; i<N; i++ )
		(void) wait(NULL);

	(void) shmdt( (char *) Trazim );
	(void) shmctl( Id1, IPC_RMID, NULL );

	(void) shmdt( (char *) Broj );
	(void) shmctl( Id2, IPC_RMID, NULL );
	
	exit(0);
}