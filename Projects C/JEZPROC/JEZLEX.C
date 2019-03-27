#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<conio.h>
#include	<math.h>

#include	"jezpro.h"

int		TransitionTable[COND_NUM][INPUT_SYM_NUM]= 
/* stanje \ ul.znak */
                /* slovo, broj, oper., E, +/-, pr.znak */
/* S */			{ 2, 1, -1, 2, -1, COND_SIGN, COND_SPACE,
/* 1 */			-1, 1, COND_INT_CONST, 5, 3, COND_INT_CONST, COND_INT_CONST,
/* 2 */			2, 2, COND_IDENTIF, 2, COND_IDENTIF, COND_IDENTIF, COND_IDENTIF,
/* 3 */			-1, 4, -1, -1, -1, -1, -1,
/* 4 */			-1, 4, COND_REAL_CONST, 5, COND_REAL_CONST, COND_REAL_CONST, COND_REAL_CONST,
/* 5 */			-1, 7, -1, -1, -1, 6, -1,
/* 6 */			-1, 7, -1, -1, -1, -1, -1,
/* 7 */			-1, 7, COND_REAL_CONST, -1, COND_REAL_CONST, COND_REAL_CONST, COND_REAL_CONST,
/* IDN */		2, 1, COND_OPER, 2, COND_OPER, COND_OPER, COND_SPACE,
/* INT */		2, 1, COND_OPER, 2, COND_OPER, COND_OPER, COND_SPACE,
/* REAL */	2, 1, COND_OPER, 2, COND_OPER, COND_OPER, COND_SPACE,
/* MED */		2, 1, COND_OPER, 2, COND_OPER, COND_OPER, COND_SPACE, 
/* PR.ZNAK */		2, 1, COND_OPER, 2, COND_OPER, COND_SIGN, COND_SPACE,
/* SIGN */	-1, 1, -1, -1, -1, -1, -1 };

char*	ReservedWords[RES_WORDS_NUM] = { "program", "kraj", "konstanta", "tip",
            "varijabla", "procedura", "pocetak", "ako", "tada", "inace",
            "dok", "radi", "ponovi", "svedo", "za", "do" };

char*	Operators = "+-*/()<>;,.=:";

extern ZAVRSNI_SIMBOL			ZSTable[ZS_SIMBOL_NUM];
extern UNIFORMNI_SIMBOL		**USTable;
extern IDENTIFIKATOR			**IDNTable;
extern LITERAL						**LITTable;

extern INTER_RES		**IRESTable;
extern CONST				**CONSTTable;

extern long		USNum, IDNNum, LITNum, IRESNum, CONSTNum, LineNum;
extern long		MaxUSNum, MaxIDNNum, MaxLITNum, MaxIRESNum, MaxCONSTNum;
extern int		LineStartsWithSymNum[MAX_LINES];

extern FILE		*fp, *fpReport, *fpAsm;

int	Initialize( void )
{
    int		i;

    MaxUSNum = 500;
    USTable	= (UNIFORMNI_SIMBOL **)	malloc(MaxUSNum * sizeof(UNIFORMNI_SIMBOL *) );
    for( i=0; i<MaxUSNum; i++ )
        if( (USTable[i] = (UNIFORMNI_SIMBOL *) malloc(sizeof(UNIFORMNI_SIMBOL)) ) == NULL )
        {
            puts("Nema memorije za US!!!");
            return(1);
        }

    MaxIDNNum = 100;
    IDNTable = (IDENTIFIKATOR **) malloc(MaxIDNNum * sizeof(IDENTIFIKATOR *) );
    for( i=0; i<MaxIDNNum; i++ )
        if( (IDNTable[i] = (IDENTIFIKATOR *) malloc( sizeof(IDENTIFIKATOR)) ) == NULL )
        {
            puts("Nema memorije za IDN!!!");
            return(1);
        }

    MaxLITNum = 100;
    LITTable = (LITERAL **) malloc(MaxLITNum * sizeof(LITERAL *) );
    for( i=0; i<MaxLITNum; i++ )
        if( (LITTable[i] = (LITERAL *) malloc( sizeof(LITERAL)) ) == NULL )
        {
            puts("Nema memorije za LIT!!!");
            return(1);
        }

    MaxIRESNum = 100;
    IRESTable = (INTER_RES **) malloc(MaxIRESNum * sizeof(INTER_RES *) );
    for( i=0; i<MaxIRESNum; i++ )
        if( (IRESTable[i] = (INTER_RES *) malloc( sizeof(INTER_RES)) ) == NULL )
        {
            puts("Nema memorije za tablicu medjurezultata!!!");
            return(1);
        }
    MaxCONSTNum = 100;
    CONSTTable = (CONST **) malloc(MaxCONSTNum * sizeof(CONST *) );
    for( i=0; i<MaxCONSTNum; i++ )
        if( (CONSTTable[i] = (CONST *) malloc( sizeof(CONST)) ) == NULL )
        {
            puts("Nema memorije za tablicu konstanti !!!");
            return(1);
        }

    USNum = LITNum = IDNNum = IRESNum = CONSTNum = 0;
    LineNum = 1;

    return(0);
}


int		LexAnalyse( void )
{
    char	strCurrString[80], chCharacter;
    char 	*strTemp, *strTemp2;
    int		nCurrCond = COND_S, nOperIndex;
    int		nNextCond, nCounter=0, nResWordFleg = 0;
    size_t		j;
    long			i;
    int line=1;

    strTemp = (char *) calloc(100,1);
    strTemp2 = (char *) calloc(100,1);


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

        case	COND_OPER:
            nOperIndex = Find(strCurrString[0], Operators, OPER_NUM);
            strCurrString[1] = 0;
            nCounter = 0;
//			printf("\n Unesen prekidni znak : %s", strCurrString );
            
            InsertUniformSymbol(TRM, RES_WORDS_NUM + nOperIndex );
            break;
        
        case	COND_IDENTIF :
            if( strCurrString[nCounter-1] != ' ' && strCurrString[nCounter-1] != '\n' )
                fseek(fp, -1, SEEK_CUR);

            strCurrString[nCounter-1] = 0;
            nCounter = 0;

            for( j=0; j<RES_WORDS_NUM; j++ )
                if( strcmp( strCurrString, ReservedWords[j] ) == 0 )
                {
//					printf("\n   Unesena rezervirana rijec : %s", ReservedWords[j] );
                    InsertUniformSymbol( TRM, j );
                    nResWordFleg = 1;
                    break;
                }
            if( nResWordFleg != 1 )
            {
//				printf("\n   Unesena varijabla imena : %s", strCurrString );
                InsertIdentificator( strCurrString );
            }
            nResWordFleg = 0;

            break;
        
        case	COND_REAL_CONST :
            if( strCurrString[nCounter-1] != ' ' && strCurrString[nCounter-1] != '\n' )
                fseek(fp, -1, SEEK_CUR);
            
            strCurrString[nCounter-1] = 0;
//			printf("\n   Unesena realna konstanta : %s", strCurrString );
            InsertLiteral( strCurrString, REAL );
            nCounter = 0;
            break;

        case	COND_INT_CONST :
            if( strCurrString[nCounter-1] != ' ' && strCurrString[nCounter-1] != '\n' )
                fseek(fp, -1, SEEK_CUR);

            strCurrString[nCounter-1] = 0;
//			printf("\n   Unesena cjelobrojna konstanta : %s", strCurrString );
            InsertLiteral( strCurrString, DEC );
            nCounter = 0;
            break;
        case	COND_SPACE :
            nCounter = 0;
            break;
        }
        nCurrCond = nNextCond;
        chCharacter = fgetc(fp);
    }

//	clrscr();
    puts(" TABLICA UNIFORMNIH SIMBOLA  ");
    puts("--------------------------------------------------------------------------");
    puts(" Red.broj |      Klasa               |   Indeks   |        Simbol  ");
    printf("--------------------------------------------------------------------------");
    for( i=0; i<USNum; i++ )
    {
        switch(USTable[i]->nClass )
        {
            case	IDN	:
                {
                    strcpy(strTemp, "Identifikator");
                    strcpy(strTemp2, IDNTable[USTable[i]->lIndex]->strName );

                    break;
                }
            case	LIT	:
                {
                        strcpy(strTemp, "Literal");
                        strcpy(strTemp2, LITTable[USTable[i]->lIndex]->strLiteral );

                        break;
                }
            case	TRM	:
                {
                        strcpy(strTemp, "Zavrsni simbol" );
                        strcpy(strTemp2, ZSTable[USTable[i]->lIndex].strName );
                        break;
                }
        }
        printf("\n  %3d   ", i+1 );
        printf("      %-20s   ", strTemp );
        printf("      %2d  ", USTable[i]->lIndex );
        printf("%18s  ", strTemp2 );
    
        if( LineStartsWithSymNum[line] < i )
            line++;

        if( i%20 == 0 && i != 0 )
        {
            getch();

//			clrscr();
            puts(" TABLICA UNIFORMNIH SIMBOLA  ");
            puts("--------------------------------------------------------------------------");
            puts(" Red.broj |      Klasa               |   Indeks   |        Simbol  ");
            printf("--------------------------------------------------------------------------");
        }
    }
    getch();

//	clrscr();
    puts(" TABLICA LITERALA ");
    puts("------------------------------------------------------------------------------");
    puts("      Literal         |      Baza     |    Skala   |  Preciznost   |   Adresa  ");
    puts("------------------------------------------------------------------------------");
    for( i=0; i<LITNum; i++ )
    {
        printf("\n %18s   |", LITTable[i]->strLiteral );
        if( LITTable[i]->nBase == DEC )
            printf("   decimalna   |");
        else
            printf("     realna    |");
        if( LITTable[i]->nScale == FIX )
            printf("   fiksna   | ");
        else
            printf(" promjenjiva|");

        printf("  %5d   ",LITTable[i]->nPrec );

        if( i%20==0 && i!= 0 )
        {
            getch();

    //	clrscr();
            puts(" TABLICA LITERALA ");
            puts("------------------------------------------------------------------------------");
            puts("      Literal         |      Baza     |    Skala   |  Preciznost   |   Adresa  ");
            puts("------------------------------------------------------------------------------");
        }
    }
    getch();

//	clrscr();
    puts(" TABLICA INDETIFIKATORA");
    puts("------------------------------------------------------------------------------");

    for( i=0; i<IDNNum; i++ )
    {
        printf("\n Identifikator : %s", IDNTable[i]->strName );

        if( i%20==0 && i!= 0 )
        {
            getch();
            
    //	clrscr();
            puts(" TABLICA INDETIFIKATORA");
            puts("------------------------------------------------------------------------------");
        }
    }

    getch();
//	clrscr();

    return(0);
}


int	GetNextCondition( int	nCurrCond, char	nChar )
{
    if( tolower(nChar) == 'e' )
        {
            return	TransitionTable[nCurrCond][INPUT_E];
        }
    else	if( nChar == ' ' || nChar == '\n' || nChar == '\r' || nChar == '\t' )
    {
        if( nChar == '\n' )
            LineStartsWithSymNum[LineNum++] = USNum + 1;

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
    else	if( Find(nChar, Operators, OPER_NUM) != -1 )
        {
            return	TransitionTable[nCurrCond][INPUT_OPER];
        }
    else
        {
            printf("\n   Nepoznat ulazni znak !!!");
            return	ERROR_CODE;
        }
}

int	Find( char nChar, char *List, int nListLen )
{
    int	ret = -1,i;

    for( i=0; i<nListLen; i++ )
        if( List[i] == nChar )
            ret = i;

    return	ret;
}

void	InsertUniformSymbol( enum KLASA nClass, int nIndex )
{
    int i;

    if( USNum == MaxUSNum )
    {
        USTable	= (UNIFORMNI_SIMBOL **)	realloc(USTable, 2 * MaxUSNum * sizeof(UNIFORMNI_SIMBOL *) );
        for( i=MaxUSNum; i<2*MaxUSNum; i++ )
        if( (USTable[i] = (UNIFORMNI_SIMBOL *) malloc(sizeof(UNIFORMNI_SIMBOL)) ) == NULL )
        {
            puts("Nema memorije za tablicu uniformnih simbola!!!");
            exit(1);
        }
        MaxUSNum *= 2;
    }

    USTable[USNum]->nClass = nClass;
    USTable[USNum++]->lIndex = nIndex;
}

void	InsertIdentificator( char	*strName )
{
    long	i;
    int		Find = 0, FindAtPos=-1;

    if( IDNNum == MaxIDNNum )
    {
        IDNTable = (IDENTIFIKATOR **) realloc(IDNTable, 2 * MaxIDNNum * sizeof(IDENTIFIKATOR *) );
        for( i=MaxIDNNum; i<2*MaxIDNNum; i++ )
            if( (IDNTable[i] = (IDENTIFIKATOR *) malloc( sizeof(IDENTIFIKATOR)) ) == NULL )
            {
                puts("Nema memorije za IDN!!!");
            }
        MaxIDNNum *= 2;
    }

    for( i=0; i<IDNNum; i++ )
        if( strcmp( IDNTable[i]->strName, strName) == 0 )
        {
            FindAtPos = i;
            Find = 1;
        }

    if( Find == 0 )
    {
        strcpy( IDNTable[IDNNum]->strName, strName );
        
        IDNTable[IDNNum]->bDeclared   = FALSE;
        IDNTable[IDNNum]->bAssociated = FALSE;
        IDNTable[IDNNum]->nClass = NOTDEFINED;
        IDNTable[IDNNum]->nType  = NOTDEFINED;

        FindAtPos = IDNNum++;
    }
    InsertUniformSymbol( IDN, FindAtPos );
}

void	InsertLiteral( char *strName, enum BASE nBase )
{
    int			i;
    double	x, mantisa, exp=0;

    if( LITNum == MaxLITNum )
    {
        LITTable = (LITERAL **) realloc(LITTable, 2 * MaxLITNum * sizeof(LITERAL *) );
        for( i=MaxLITNum; i<2*MaxLITNum; i++ )
            if( (LITTable[i] = (LITERAL *) malloc( sizeof(LITERAL)) ) == NULL )
            {
                puts("Nema memorije za LIT!!!");
            }
        MaxLITNum *= 2;
    }

    strcpy( LITTable[LITNum]->strLiteral, strName );
    LITTable[LITNum]->nBase = nBase;
    
    if( nBase == DEC )
    {
        LITTable[LITNum]->nType = INTEGER;
        LITTable[LITNum]->nLitVal = atoi(strName);
    }
    else
    {
        LITTable[LITNum]->nType = REAL;
    
        x		= atof(strName);
        exp = floor(log10(fabs(x)));
        mantisa = x / pow(10,exp);		/* normalizirana mantisa, sa jednom znamenkom ispred toèke */

        if( fabs(mantisa) > 3.2764 )
        {
            LITTable[LITNum]->nLitVal = (int) (mantisa*1000);
            LITTable[LITNum]->nExpVal = (int) (exp - 3);
        }
        else
        {
            LITTable[LITNum]->nLitVal = (int) (mantisa*10000);
            LITTable[LITNum]->nExpVal = (int) (exp - 4);
        }
    }
    sprintf(LITTable[LITNum]->strExp, "%d", LITTable[LITNum]->nExpVal );
    
    LITTable[LITNum]->nScale = FIX;
    LITTable[LITNum]->nPrec = strlen(strName);

    InsertUniformSymbol( LIT, LITNum++ );
}

INTER_RES*	InsertInterRes( void )
{
    int		i;
    char	strName[15];

    if( IRESNum == MaxIRESNum )
    {
        IRESTable = (INTER_RES **) realloc(IRESTable, 2 * MaxIRESNum * sizeof(INTER_RES *) );
        for( i=MaxIRESNum; i<2*MaxIRESNum; i++ )
            if( (IRESTable[i] = (INTER_RES *) malloc( sizeof(INTER_RES)) ) == NULL )
            {
                puts("Nema memorije za realociranje tablice medjurezultata!!!");
            }
        MaxIRESNum *= 2;
    }

    sprintf(strName, "MDREZ%d", IRESNum );
    strcpy( IRESTable[IRESNum]->strName, strName );
    IRESNum++;

    return IRESTable[IRESNum-1];
}

CONST*	InsertConstant( void )
{
    int		i;
    char	strName[15];

    if( CONSTNum == MaxCONSTNum )
    {
        CONSTTable = (CONST **) realloc(CONSTTable, 2 * MaxCONSTNum * sizeof(CONST *) );
        for( i=MaxCONSTNum; i<2*MaxCONSTNum; i++ )
            if( (CONSTTable[i] = (CONST *) malloc( sizeof(CONST)) ) == NULL )
            {
                puts("Nema memorije za realociranje tablice konstanti!!!");
            }
        MaxCONSTNum *= 2;
    }

    sprintf(strName, "CONST%d", CONSTNum );
    strcpy( CONSTTable[CONSTNum]->strName, strName );
    CONSTNum++;

    return	CONSTTable[CONSTNum-1];
}
