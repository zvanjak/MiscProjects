#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <values.h>

int main( void )
{
	int i;
	for( i=1; i<MAXSHORT; i++ )
	{
		if( shmctl(i, IPC_RMID, NULL) != -1 )
			printf("\n Obrisao zajednicku memoriju %d", i );
		if( semctl(i, 0, IPC_RMID, 0) != -1 )
			printf("\n Obrisao skup semafora %d", i );
		if( msgctl(i, IPC_RMID, NULL ) != -1 )
			printf("\n Obrisao red poruka %d", i );
	}
	return 0;
}