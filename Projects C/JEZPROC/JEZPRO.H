#define	TRUE		1
#define	FALSE		0

#define INTEL		1
#define	Z80			2

#define ERR1	"Ime programa mora biti jedinstveno !!! "
#define ERR2	"Konstanta vec deklarirana !!! "
#define ERR3	"Ime tipa nije jedinstveno !!! "
#define ERR4	"Nedefiniran tip (kod definiranja novog tipa mora se koristiti 'integer' ili 'real'!!!"
#define ERR5	"Varijabla vec deklarirana !!! "
#define ERR7	"Ime procedure vec deklarirano !!!"
#define ERR9	"Izraz za donju grani cu FOR petlje mora dati cjelobrojni rezultat !!! "
#define ERR10	"Izraz za gornju granicu FOR petlje mora dati cjelobrojni rezultat !!! "
#define ERR11	"Ocekujem ime procedure (ili je kriva sintaksa naredbe pridruzivanja)!!! "
#define ERR12	"Identifikator s lijeve strane := mora biti varijabla !!! "
#define ERR13	"Lijeva i desna strana izraza razlicitih tipova !!! "
#define ERR14	"Lijeva i desna strana kod usporedjivanja razlicitih tipova !!! "
#define ERR15	"Razliciti tipovi varijabli u aritmetickom izrazu !!! "
#define ERR16	"Nedeklarirana varijabla u izrazu !!! "
#define ERR17	"Varijabli u izrazu nije pridruzena vrijednost !!! "
#define ERR18	"U izrazu se mogu koristiti samo varijable i konstante !!! "
#define ERR19	"Nedeklariran identifikator (poziv procedure) !!! "
#define ERR20	"Varijabla u FOR petlji nije deklarirana !!! "
#define ERR21	"Identifikator u FOR petlji mora biti varijabla !!! "
#define ERR22	"Varijabla u FOR petlji mora biti cjelobrojnog tipa !!! "
#define ERR23	"Varijabla s lijeve strane izraza nije deklarirana !!!"

#define ERR100 "Prekoracena dozvoljena vrijednost za integer "
#define ERR101 "Prekoracena dozvoljena vrijednost za mantisu "
#define ERR102 "Prekoracena dozvoljena vrijednost za eksponent"
#define ERR103
#define ERR104 "Varijabla nedefiniranog tipa"
#define ERR105
#define ERR106
#define ERR107
#define ERR108
#define ERR109
#define ERR110

#define	ERR501	"Program mora pocinjati sa kljucnom rijecju PROGRAM !!!"
#define	ERR502	"Ocekujem identifikator"
#define ERR503	"Ocekujem ;"
#define	ERR504	"Ocekujem KRAJ"
#define ERR505	"Ocekujem ."
#define	ERR506	"Ocekujem POCETAK"
#define	ERR507	"Ocekujem TADA"
#define	ERR508	"Ocekujem INACE"
#define	ERR509	"Ocekujem RADI"
#define	ERR510	"Ocekujem SVEDO"
#define	ERR511	"Ocekujem :"
#define	ERR512	"Ocekujem ="
#define	ERR513	"Ocekujem DO"
#define	ERR514	"Ocekujem POCETAK, AKO, DOK, PONOVI, ZA ili identifikator"
#define	ERR515	"Ocekujem naredbu"
#define	ERR516	"Ocekujem KRAJ ili ;"
#define	ERR517	"Ocekujem = ili < ili >"
#define	ERR518	"Ocekujem literal"
#define	ERR519	"Ocekujem )"
#define	ERR520	"Ocekujem identifikator ili literal "
#define	ERR521
#define	ERR522
#define	ERR523
#define	ERR524
#define	ERR525
#define	ERR526
#define	ERR527
#define	ERR528
#define	ERR529
#define	ERR530
#define	ERR531

#define COND_NUM	14
#define INPUT_SYM_NUM	7

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
#define	COND_OPER			12
#define COND_SIGN			13

#define	INPUT_CHAR		0
#define	INPUT_NUM			1
#define	INPUT_OPER		2
#define	INPUT_E				3
#define	INPUT_DEC_POINT	4
#define	INPUT_SIGN		5
#define	INPUT_SPACE		6

#define	ZS_PROGRAM		0
#define	ZS_KRAJ				1
#define	ZS_KONSTANTA	2
#define	ZS_TIP				3
#define	ZS_VARIJABLA	4
#define	ZS_PROCEDURA	5
#define	ZS_POCETAK		6
#define	ZS_AKO				7
#define	ZS_TADA				8
#define	ZS_INACE			9
#define	ZS_DOK				10
#define	ZS_RADI				11
#define	ZS_PONOVI			12
#define	ZS_SVEDO			13
#define	ZS_ZA					14
#define	ZS_DO					15
#define	ZS_PLUS				16
#define	ZS_MINUS			17
#define	ZS_PUTA				18
#define	ZS_DIJELJENO	19
#define	ZS_LZAGRADA		20
#define	ZS_DZAGRADA		21
#define	ZS_MANJE			22
#define	ZS_VECE					23
#define	ZS_TOCKA_ZAREZ	24
#define	ZS_ZAREZ				25
#define	ZS_TOCKA				26
#define	ZS_JEDNAKO			27
#define	ZS_DVOTOCKA			28

#define	RES_WORDS_NUM	16
#define	OPER_NUM		14
#define	ZS_SIMBOL_NUM		30

#define	ERROR_CODE		-1
#define	MAX_LINES		1000

#define MAX_INT		32764
#define MIN_INT		-32764
#define MAX_MANT	32764
#define MIN_MANT	-32764
#define MAX_EXP		127
#define MIN_EXP		-128

enum	KLASA
{
	TRM,
	IDN,
	LIT
};

enum	BASE
{
	DEC,
	_REAL
};

enum	SCALE
{
	FIX,
	VAR
};

typedef	int	BOOL;

typedef enum { PROGRAM=1, PROCEDURE=2, VARIABLE=3, CONSTANT=4 } IDN_CLASS;
typedef enum { INTEGER=1, REAL=2, NOTDEFINED=0 } TYPE;	

typedef struct 
{
	char	strName[15];
	int		nStopSymbol;		// da = 1, ne = 0
} ZAVRSNI_SIMBOL;

typedef struct	
{
	enum	KLASA		nClass;
	int					lIndex;
} UNIFORMNI_SIMBOL;

typedef struct
{
	char			strLiteral[20];
	int				nLitVal;
	char			strExp[5];
	short int		nExpVal;

	enum BASE		nBase;
	int				nScale;
	int				nPrec;

	TYPE			nType;
} LITERAL;

typedef struct	
{
	char		strName[32];
	BOOL		bDeclared;
	BOOL		bAssociated;

	IDN_CLASS	nClass;
	TYPE		nType;
	
	LITERAL*	lPointer;
} IDENTIFIKATOR;

typedef struct
{
	char		strName[15];
	TYPE		nType;
} INTER_RES;

typedef struct
{
	char		strLabel[20];
} LABEL;

typedef struct
{
	char		strName[15];
	
	TYPE		nType;
	LITERAL*	lPointer;
} CONST;

// Funkcije

int		Initialize( void );
int		LexAnalyse( void );
int		SyntaxAnalyse( void );
int		InitSynAnalyse( void );

int		GetNextCondition( int nCurrCond, char	chCharacter );
int		Find( char nChar, char *List, int nListLen );

void	Advance(void);

void	InsertUniformSymbol( enum KLASA nClass, int nIndex );
void	InsertIdentificator( char *strName );
void	InsertLiteral( char *strLiteral, enum BASE nBase );

INTER_RES*	InsertInterRes( void );
CONST*		InsertConstant( void );

void	Production_program( void);
void	Production_blok(void);
void	Production_naredba(void);
void	Production_izraz( LABEL *l2 );
void	Production_kraj(void);
void	Production_operator( INTER_RES p1, LABEL *l2 );

void	Production_b_nar(void);
void	Production_b_tip(void);
void	Production_d_tip(void);
void	Production_d_tip_1(void);
void	Production_b_var(void);
void	Production_d_var(void);
void	Production_idn(void);
void	Production_d_var_1(void);
void	Production_d_kon(void);
void	Production_d_kon_1(void);
void	Production_b_pro(void);
void	Production_n_izraz( INTER_RES *t2 );
void	Production_e_list( INTER_RES p1, INTER_RES *t2);
void	Production_t( INTER_RES *t2 );
void	Production_t_list( INTER_RES p1, INTER_RES *t2 );
void	Production_p( INTER_RES *p2 );
void	Production_idn_lit( INTER_RES *p2 );
void	Production_pro_izr( IDENTIFIKATOR *p1 );

void	Action1( IDENTIFIKATOR *p2);
void	Action2( IDENTIFIKATOR *p2, LITERAL *q2 );
void	Action3( IDENTIFIKATOR *p2, IDENTIFIKATOR q2 );
void	Action4( IDENTIFIKATOR *p2, IDENTIFIKATOR q2 );
void	Action5( IDENTIFIKATOR *p2 );
void	Action7( INTER_RES p2, INTER_RES q2, IDENTIFIKATOR t2, LABEL *l1, LABEL *k1 );
void	Action8( IDENTIFIKATOR p2 );
void	Action9( IDENTIFIKATOR *p2, INTER_RES q2 );
void	Action10( INTER_RES p2, INTER_RES q2, LABEL	*l1 );
void	Action11( INTER_RES p2, INTER_RES q2, LABEL *l1 );
void	Action12( INTER_RES p2, INTER_RES q2, LABEL *l1 );
void	Action13( INTER_RES p2, INTER_RES q2, INTER_RES *r1 );
void	Action14( INTER_RES p2, INTER_RES q2, INTER_RES *r1 );
void	Action15( INTER_RES p2, INTER_RES q2, INTER_RES *r1 );
void	Action16( INTER_RES p2, INTER_RES q2, INTER_RES *r1 );
void	Action17( IDENTIFIKATOR p2 );
void	Action18( LITERAL *p2, CONST *r1 );
void	Action20( void );
void	Action21( void );
void	Action22( void );
void	Action23( LABEL *k1 );
void	Action24( LABEL *k1);
void	Action25( LABEL k2, LABEL l2 );
void	Action26( LABEL l2 );
void	Action27( LABEL k2 );
void	Print(int i);

void	WriteIntMul();
void	WriteIntDiv();

void	WriteRealAdd();
void	WriteRealSub();
void	WriteRealMul();
void	WriteRealDiv();

int		CheckUSTable( enum KLASA	nClass, int Index );
int		FindErrorLine( void );
void	Error( int nErrorNum, char *strErrText );