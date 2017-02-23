#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<conio.h>

#include	"jezpro1.h"


//	Globalne varijable
int		TransitionTable[12][7]= { 2, 1, -1, 2, -1, -1, COND_SPACE,
			-1, 1, COND_INT_CONST, 5, 3, COND_INT_CONST, COND_INT_CONST,
			2, 2, COND_IDENTIF, 2, COND_IDENTIF, COND_IDENTIF, COND_IDENTIF,
			-1, 4, -1, -1, -1, -1, -1,
			-1, 4, COND_REAL_CONST, 5, COND_REAL_CONST, COND_REAL_CONST, COND_REAL_CONST,
			-1, 7, -1, -1, -1, 6, -1,
			-1, 7, -1, -1, -1, -1, -1,
			-1, 7, COND_REAL_CONST, -1, COND_REAL_CONST, COND_REAL_CONST, COND_REAL_CONST,
			2, 1, COND_SPACE, 2, COND_SPACE, COND_SPACE, COND_SPACE,
			2, 1, COND_SPACE, 2, COND_SPACE, COND_SPACE, COND_SPACE,
			2, 1, COND_SPACE, 2, COND_SPACE, COND_SPACE, COND_SPACE,
			2, 1, COND_SPACE, 2, COND_SPACE, COND_SPACE, COND_SPACE };

char*	ReservedWords[RES_WORDS_NUM] = { "program", "kraj", "konstanta", "tip",
			"varijabla", "procedura", "pocetak", "ako", "tada", "inace",
			"dok", "radi", "ponovi", "svedo", "od", "do" };

char*	Operators = "+-*/()<>;.,=:";


ZAVRSNI_SIMBOL		ZSTable[ZS_SIMBOL_NUM] = 
		{	"program", 0 , "kraj", 0,"konstanta", 0, "tip", 0, 
			"varijabla", 0, "procedura", 0, "pocetak", 0, "ako", 0, 
			"tada", 0, "inace", 0, "dok", 0, "radi", 0, "ponovi", 0, 
			"svedo", 0, "od", 0, "do", 0,
			"+", 1, "-", 1, "*", 1, "/", 1, "(", 1, ")", 1,"<", 1,
			">", 1, ";", 1, ",", 1, ".", 1, "=", 1, ":", 1 };

UNIFORMNI_SIMBOL	**USTable;
IDENTIFIKATOR			**IDNTable;
LITERAL						**LITTable;

long		USNum, IDNNum, LITNum;
long		MaxUSNum, MaxIDNNum, MaxLITNum;

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

