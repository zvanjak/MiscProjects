#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<conio.h>

#include	"jezpro1.h"

void main( void )
{
	if( !Initialize() )
	{
		puts("Doslo je do greske prilikom inicijalizacije !!!");
		exit(2);
	}
	
	if( !LexAnalyse() )
	{
		puts("Doslo je do greske prilikom leksicke analize !!!");
		exit(1);
	}
}

