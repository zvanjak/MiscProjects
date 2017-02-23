#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<conio.h>

#include	"jezpro.h"


//	Globalne varijable

ZAVRSNI_SIMBOL		ZSTable[ZS_SIMBOL_NUM] = 
		{	"program", 0 , "kraj", 0,"konstanta", 0, "tip", 0, 
			"varijabla", 0, "procedura", 0, "pocetak", 0, "ako", 0, 
			"tada", 0, "inace", 0, "dok", 0, "radi", 0, "ponovi", 0, 
			"svedo", 0, "za", 0, "do", 0,
			"+", 1, "-", 1, "*", 1, "/", 1, "(", 1, ")", 1,"<", 1,
			">", 1, ";", 1, ",", 1, ".", 1, "=", 1, ":", 1 };

UNIFORMNI_SIMBOL	**USTable;
IDENTIFIKATOR		**IDNTable;
LITERAL				**LITTable;

INTER_RES			**IRESTable;
CONST				**CONSTTable;

long		USNum, IDNNum, LITNum, LineNum, IRESNum, CONSTNum;
long		MaxUSNum, MaxIDNNum, MaxLITNum, MaxIRESNum, MaxCONSTNum;
int			LineStartsWithSymNum[MAX_LINES];
int			procType=INTEL;

FILE		*fp, *fpReport, *fpAsm;

extern int		TransitionTable[12][7];
extern char*	ReservedWords[RES_WORDS_NUM];
extern char*	Operators;


void main( int argc, char *argv[] )
{
	if( argc != 4 )
	{
		printf("\n Upotreba : jez.exe proc-name source-file asm-file");
		exit(1);
	}
	else
	{
		if( strcmp(argv[1],"z80") == 0 || strcmp(argv[1],"Z80") == 0 )
		{
			procType = Z80;
		}
		else if( strcmp(argv[1],"x86") == 0 || strcmp(argv[1],"x86") == 0 )
		{
			procType = INTEL;
		}
		else
		{
			puts("Nije naznaceno ispravno ime procesora !!!");
			puts("    moguænosti : Z80 i x86");
			exit(1);
		}
		if( ( fp = fopen(argv[2], "r") ) == NULL )
		{
			puts("Datoteka tog imena ne postoji !!!");
			exit(1);
		}
		if( ( fpAsm = fopen(argv[3], "w") ) == NULL )
		{
			puts("Ne mogu otvoriti datoteku za asemblerski kod !!!");
			exit(1);
		}
		if( (fpReport = fopen("report.txt", "w") ) == NULL )
		{
			puts("Ne mogu otvoriti datoteku za izvjestaj");
			exit(1);
		}
	}
	
	if( Initialize() )
	{
		puts("Doslo je do greske prilikom inicijalizacije !!!");
		exit(1);
	}
	
	if( LexAnalyse() )
	{
		puts("Doslo je do greske prilikom leksicke analize !!!");
		exit(2);
	}

	if( SyntaxAnalyse() )
	{
		puts("Doslo je do greske prilikom sintaksne analize !!!");
		exit(3);
	}

	fclose(fp);
	fclose(fpAsm);
	fclose(fpReport);
}

