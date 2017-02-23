#define	COND_S		0
#define	COND_1		1
#define	COND_2		2
#define	COND_3		3
#define	COND_4		4
#define	COND_5		5
#define	COND_6		6
#define	COND_7		7
#define	COND_IDENTIF		8
#define	COND_INT_CONST		9
#define	COND_REAL_CONST		10
#define	COND_SPACE			11

#define	INPUT_CHAR		0
#define	INPUT_NUM		1
#define	INPUT_STOP		2
#define	INPUT_E			3
#define	INPUT_DEC_POINT	4
#define	INPUT_SIGN		5
#define	INPUT_SPACE		6

#define	RES_WORDS_NUM	16
#define	OPER_NUM		14
#define	ZS_SIMBOL_NUM		30

#define	ERROR_CODE		-1


typedef struct 
{
	char	strName[15];
	int		nStopSymbol;		// da = 1, ne = 0
} ZAVRSNI_SIMBOL;

enum	KLASA
{
	TRM,
	IDN,
	LIT
};

typedef struct	
{
	enum	KLASA		nClass;
	long					lIndex;
} UNIFORMNI_SIMBOL;

typedef struct	{
	char		strName[32];
} IDENTIFIKATOR;

typedef struct	
{
	char		strLiteral[20];
	int			nBase;
	int			nScale;
	int			nPrec;
	long		lAdr;
} LITERAL;

// Funkcije

int		Initialize( void );
int		LexAnalyse( void );

int		GetNextCondition( int nCurrCond, char	chCharacter );
int		Find( char nChar, char *List, int nListLen );

void	InsertUniformSymbol( KLASA nClass, int nIndex );
void	InsertIdentificator( char *strName );
void	InsertLiteral( char *strLiteral );


