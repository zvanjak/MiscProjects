#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<conio.h>

#include	"jezpro1.h"

extern int		TransitionTable[12][7];
extern char*	ReservedWords[RES_WORDS_NUM];
extern char*	Operators;

extern ZAVRSNI_SIMBOL			ZSTable[ZS_SIMBOL_NUM];
extern UNIFORMNI_SIMBOL		**USTable;
extern IDENTIFIKATOR			**IDNTable;
extern LITERAL						**LITTable;

extern long		USNum, IDNNum, LITNum;
extern long		MaxUSNum, MaxIDNNum, MaxLITNum;

int	Initialize( void )
{
	int		i;

	MaxUSNum = 300;
	USTable	= (UNIFORMNI_SIMBOL **)	malloc(MaxUSNum * sizeof(UNIFORMNI_SIMBOL *) );
	for( i=0; i<MaxUSNum; i++ )
		if( (USTable[i] = (UNIFORMNI_SIMBOL *) malloc(sizeof(UNIFORMNI_SIMBOL)) ) == NULL )
		{
			puts("Nema memorije za US!!!");
			return(0);
		}

	MaxIDNNum = 100;
	IDNTable = (IDENTIFIKATOR **) malloc(MaxIDNNum * sizeof(IDENTIFIKATOR *) );
	for( i=0; i<MaxIDNNum; i++ )
		if( (IDNTable[i] = (IDENTIFIKATOR *) malloc( sizeof(IDENTIFIKATOR)) ) == NULL )
		{
			puts("Nema memorije za IDN!!!");
			return(0);
		}

	MaxLITNum = 100;
	LITTable = (LITERAL **) malloc(MaxLITNum * sizeof(LITERAL *) );
	for( i=0; i<MaxLITNum; i++ )
		if( (LITTable[i] = (LITERAL *) malloc( sizeof(LITERAL)) ) == NULL )
		{
			puts("Nema memorije za LIT!!!");
			return(0);
		}

	USNum = LITNum = IDNNum = 0;
	return(1);
}


int		LexAnalyse( void )
{
	FILE	*fp;
	char	strCurrString[80], strFileName[100], chCharacter;
	int		nCurrCond = COND_S;
	int		nNextCond, nCounter=0, nResWordFleg = 0;
	size_t		j;
	long			i;

	printf("\n Unesi ime datoteke koju zelis analizirati : " );
	scanf("%[^\n]", strFileName );

	if( ( fp = fopen(strFileName, "r") ) == NULL )
	{
		puts("Datoteka tog imena ne postoji !!!");
		return(0);
	}

	chCharacter = fgetc(fp);
	while( !feof( fp ) )
	{
		strCurrString[nCounter++] = chCharacter;

		nNextCond = GetNextCondition( nCurrCond, chCharacter );
		switch(nNextCond)
		{
		case	ERROR_CODE :
			printf("\n	Greska u ulaznom stringu !!!");
			exit(0);
			break;
		
		case	COND_IDENTIF :
			strCurrString[nCounter-1] = 0;
			nCounter = 0;

			for( j=0; j<RES_WORDS_NUM; j++ )
				if( strcmp( strCurrString, ReservedWords[j] ) == 0 )
				{
					printf("\n   Unesena rezervirana rijec : %s", ReservedWords[j] );
					InsertUniformSymbol( TRM, j );
					nResWordFleg = 1;
					break;
				}
			if( nResWordFleg != 1 )
			{
				printf("\n   Unesena varijabla imena : %s", strCurrString );
				InsertIdentificator( strCurrString );
			}
			nResWordFleg = 0;

			break;
		
		case	COND_REAL_CONST :
			strCurrString[nCounter-1] = 0;
			printf("\n   Unesena realna konstanta : %s", strCurrString );
			InsertLiteral( strCurrString );
			nCounter = 0;
			break;
		
		case	COND_INT_CONST :
			strCurrString[nCounter-1] = 0;
			printf("\n   Unesena cjelobrojna konstanta : %s", strCurrString );
			InsertLiteral( strCurrString );
			nCounter = 0;
			break;
		case	COND_SPACE :
			nCounter = 0;
			break;
		}
		nCurrCond = nNextCond;
		chCharacter = fgetc(fp);
	} 

	printf("\n Uniformni simboli : ");
	for( i=0; i<USNum; i++ )
		printf("\n Klasa %d  -  index %d", USTable[i]->nClass, USTable[i]->lIndex );
	getch();

	for( i=0; i<LITNum; i++ )
		printf("\n Iznos konstante : %s", LITTable[i]->strLiteral );
	getch();

	for( i=0; i<IDNNum; i++ )
		printf("\n Identifikator : %s", IDNTable[i]->strName );
	getch();

	return(1);
}


int	GetNextCondition( int	nCurrCond, char	nChar )
{
	if( tolower(nChar) == 'e' )
		{
			return	TransitionTable[nCurrCond][INPUT_E];
		}
	else	if( nChar == ' ' || nChar == '\n' || nChar == '\r' || nChar == '\t' )
	{
		return	TransitionTable[nCurrCond][INPUT_SPACE];
	}
  	else	if( nChar == '+' || nChar == '-' )
		{
			return	TransitionTable[nCurrCond][INPUT_SIGN];
		}
	else	if( nChar == '.' )
		{
			return	TransitionTable[nCurrCond][INPUT_DEC_POINT];
		}
	else	if( isdigit(nChar) )
		{
			return	TransitionTable[nCurrCond][INPUT_NUM];
		}
	else	if( isalpha(nChar) )
		{
			return	TransitionTable[nCurrCond][INPUT_CHAR];
		}
	else	if( Find(nChar, Operators, OPER_NUM) != 0 )
		{
			return	TransitionTable[nCurrCond][INPUT_STOP];
		}
	else
		{
			printf("\n   Nepoznat ulazni znak !!!");
			return	ERROR_CODE;
		}
}

int	Find( char nChar, char *List, int nListLen )
{
	int	ret = 0,i;

	for( i=0; i<nListLen; i++ )
		if( List[i] == nChar )
			ret = 1;

	return	ret;
}

void	InsertUniformSymbol( KLASA nClass, int nIndex )
{
	if( USNum == MaxUSNum )
		{
		}
	else
		{
			USTable[USNum]->nClass = nClass;
			USTable[USNum++]->lIndex = nIndex;
		}
}

void	InsertIdentificator( char	*strName )
{
	long	i;
	int		Find = 0, FindAtPos=-1;

	if( IDNNum == MaxIDNNum )
		{
		}
	else
		{
			for( i=0; i<IDNNum; i++ )
				if( strcmp( IDNTable[i]->strName, strName) == 0 )
				{
					FindAtPos = i;
					Find = 1;
				}
			
			if( Find == 0 )
			{
				strcpy( IDNTable[IDNNum]->strName, strName );
				FindAtPos = IDNNum++;
			}
			InsertUniformSymbol( IDN, FindAtPos );
		}
}

void	InsertLiteral( char *strName )
{
	if( LITNum == MaxLITNum )
		{
		}
	else
		{
			strcpy( LITTable[LITNum]->strLiteral, strName );
			InsertUniformSymbol( LIT, LITNum++ );
		}
}