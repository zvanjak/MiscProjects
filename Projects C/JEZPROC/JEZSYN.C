#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<conio.h>

#include	"jezpro.h"

extern int		TransitionTable[12][7];
extern char*	ReservedWords[RES_WORDS_NUM];
extern char*	Operators;

extern ZAVRSNI_SIMBOL			ZSTable[ZS_SIMBOL_NUM];
extern UNIFORMNI_SIMBOL		**USTable;
extern IDENTIFIKATOR			**IDNTable;
extern LITERAL						**LITTable;

extern long		USNum, IDNNum, LITNum, LineNum, IRESNum, CONSTNum;
extern long		MaxUSNum, MaxIDNNum, MaxLITNum, MaxIRESNum, MaxCONSTNum;
extern int		LineStartsWithSymNum[MAX_LINES];
extern int		procType;

extern FILE		*fpReport, *fpAsm;

extern INTER_RES		**IRESTable;
extern CONST			**CONSTTable;

long					lGlobIndex, LabelNum;
unsigned int	nROM, nRAM;

BOOL			bFirstConst, bFirstVariable, bFirstProgram;
BOOL			bIntMul, bIntDiv, bRealAdd, bRealSub, bRealMul, bRealDiv;

int	SyntaxAnalyse( void )
{
	lGlobIndex = LabelNum = 0;
	bIntMul = bIntDiv = bRealMul = bRealDiv = FALSE;

	nROM = 1000;
	nRAM = 5000;

	Production_program();

	puts("Sintaksna analiza uspjesno zavrsena (nema gresaka)");
	fputs("Nema gresaka.", fpReport);

	getch();
	return(0);
}

void	Advance()
{
	lGlobIndex++;
}

void	Production_program()
{
	IDENTIFIKATOR	*p1;

	Print(1);
	
	if( CheckUSTable( TRM, ZS_PROGRAM ) != TRUE )
		Error(501,ERR501);
	
	Advance();

	if( CheckUSTable( IDN, -1) != TRUE )
		Error(502,ERR502);
	
	p1 = IDNTable[USTable[lGlobIndex]->lIndex];

	Advance();
	Action1( p1 );

	if( CheckUSTable( TRM, ZS_TOCKA_ZAREZ) != TRUE )
		Error(503, ERR503);

	Advance();

	Production_blok();
	Action22();
	
	if( CheckUSTable(TRM, ZS_KRAJ) != TRUE )
		Error(504, ERR504);

	Advance();

	if( CheckUSTable(TRM, ZS_TOCKA) != TRUE )
		Error(505, ERR505);
}

void	Production_blok()
{
	if( CheckUSTable(TRM, ZS_KONSTANTA) == TRUE )
	{
		Print(2);

		Advance();
		Production_d_kon();
		Production_b_tip();
		Production_b_var();
		Production_b_pro();
		Production_b_nar();
	}
	else if( CheckUSTable(TRM, ZS_TIP) == TRUE )
	{
		Print(3);

		Advance();
		Production_d_tip();
		Production_b_var();
		Production_b_pro();
		Production_b_nar();
	}
	else if( CheckUSTable( TRM, ZS_VARIJABLA) == TRUE )
	{
		Print(4);

		Advance();
		Production_d_var();
		Production_b_pro();
		Production_b_nar();
	}
	else 
	{
		Print(5);

		Production_b_pro();

		if( CheckUSTable(TRM, ZS_POCETAK) != TRUE )
			Error(506, ERR506);

		Advance();

		Production_naredba();
		Production_kraj();
	}
}

void	Production_b_nar( void )
{
	Print(6);

	Action21();

	if( CheckUSTable(TRM, ZS_POCETAK) != TRUE )
		Error(506, ERR506);

	Advance();
	
	Production_naredba();
	Production_kraj();
}

void	Production_naredba()
{
	IDENTIFIKATOR	t1, *idn;
	LABEL					l1, k1;
	INTER_RES			p1, q1;

	switch(	USTable[lGlobIndex]->nClass )
	{
		case	IDN	:
		{
			Print(12);
		
			idn = IDNTable[USTable[lGlobIndex]->lIndex];

			Advance();
			Production_pro_izr(idn);
		}
		break;
		case	TRM :
		{
			switch( USTable[lGlobIndex]->lIndex )
			{
				case	ZS_POCETAK:
				{
					Print(7);

					Advance();

					Production_naredba();
					Production_kraj();
					}
				break;
				case	ZS_AKO	:
				{
					Print(8);

					Advance();
					Production_izraz(&l1);

					if( CheckUSTable(TRM, ZS_TADA) != TRUE )
						Error(507,ERR507);

					Advance();

					Production_naredba();
					Action24(&k1);

					if( CheckUSTable(TRM, ZS_INACE) != TRUE )
						Error(508,ERR508);

					Advance();
					Action26(l1);

					Production_naredba();
					Action27(k1);
					}
				break;
				case	ZS_DOK	:
				{
					Print(9);

					Advance();

					Action23(&k1);

					Production_izraz(&l1);

					if( CheckUSTable( TRM, ZS_RADI ) != TRUE )
						Error(509,ERR509);

					Advance();

					Production_naredba();
					Action25(k1,l1);
					}
				break;
				case	ZS_PONOVI	:
				{
					Print(10);

					Advance();

					Action23(&k1);

					Production_naredba();

					if( CheckUSTable(TRM, ZS_SVEDO) != TRUE )
						Error(510,ERR510);

					Advance();

					Production_izraz(&l1);
					Action25(k1,l1);
				}
				break;
				case	ZS_ZA	:
				{
					Print(11);

					Advance();
					
					if( CheckUSTable(IDN, -1) != TRUE )
						Error(502, ERR502);

					memcpy( &t1, IDNTable[USTable[lGlobIndex]->lIndex], sizeof(IDENTIFIKATOR) );
					Advance();

					if( CheckUSTable(TRM, ZS_DVOTOCKA) != TRUE )
						Error(511, ERR511);
					Advance();

					if( CheckUSTable(TRM, ZS_JEDNAKO) != TRUE )
						Error(512, ERR512);
					Advance();

					Production_n_izraz(&p1);

					if( CheckUSTable(TRM, ZS_DO) != TRUE )
						Error(513, ERR513);
					Advance();

					Production_n_izraz(&q1);
					Action7(p1,q1,t1,&k1,&l1);

					if( CheckUSTable(TRM, ZS_RADI) != TRUE )
						Error(509, ERR509);
					Advance();

					Production_naredba();
					Action25(k1,l1);
				}
				break;
				default:
					Error(514, ERR514);
			}
		}
		break;
		default	:
			Error(515, ERR515);
	}
}

void	Production_izraz( LABEL *l2 )
{
	INTER_RES	p1;

	Print(13);

	Production_n_izraz(&p1);
	Production_operator(p1,l2);
}

void	Production_kraj()
{
	if( CheckUSTable(TRM, ZS_KRAJ ) == TRUE )
	{
		Print(14);
		Advance();
	}
	else if( CheckUSTable(TRM, ZS_TOCKA_ZAREZ) == TRUE )
	{
		Print(15);

		Advance();
		Production_naredba();
		Production_kraj();
	}
	else
	{
		Error(517,ERR517);
	}
}

void	Production_operator( INTER_RES p1, LABEL *l2 )
{
	INTER_RES		q1;

	if( CheckUSTable(TRM, ZS_JEDNAKO) == TRUE )
	{
		Print(16);

		Advance();
		Production_n_izraz(&q1);

		Action10(p1,q1,l2);
	}
	else if( CheckUSTable(TRM, ZS_VECE) == TRUE )
	{
		Print(17);

		Advance();
		Production_n_izraz(&q1);

		Action11(p1,q1,l2);
	}
	else if( CheckUSTable(TRM, ZS_MANJE) == TRUE )
	{
		Print(18);

		Advance();
		Production_n_izraz(&q1);

		Action12(p1,q1,l2);
	}
	else
	{
		Error(518, ERR518);
	}
}

void	Production_b_tip()
{
	if( CheckUSTable(TRM, ZS_TIP) == TRUE )
	{
		Print(19);

		Advance();
		Production_d_tip();
	}
	else
		Print(20);
}

void	Production_d_tip()
{
	IDENTIFIKATOR		*p1, q1;

	Print(21);

	if( CheckUSTable(IDN, -1) != TRUE )
		Error(502,ERR502);

	p1 = IDNTable[USTable[lGlobIndex]->lIndex];
	Advance();
	
	if( CheckUSTable(TRM, ZS_JEDNAKO) != TRUE )
		Error(512,ERR512);
	Advance();

	if( CheckUSTable(IDN, -1) != TRUE )
		Error(502,ERR502);

	memcpy( &q1, IDNTable[USTable[lGlobIndex]->lIndex], sizeof(IDENTIFIKATOR) );
	Advance();

	Action3(p1,q1);
	Production_d_tip_1();
}

void	Production_d_tip_1()
{
	if( CheckUSTable(TRM, ZS_TOCKA_ZAREZ) == TRUE )
	{
		Print(22);

		Advance();
		Production_d_tip();
	}
	else
		Print(23);
}

void	Production_b_var()
{
	if( CheckUSTable(TRM, ZS_VARIJABLA) == TRUE)
	{
		Print(24);

		Advance();
		Production_d_var();
	}
	else
		Print(25);
}

void	Production_d_var()
{
	IDENTIFIKATOR		*p1, q1;

	Print(26);

	if( CheckUSTable(IDN, -1) != TRUE)
		Error(502,ERR502);

	p1 = IDNTable[USTable[lGlobIndex]->lIndex];
	Advance();
	
	if( CheckUSTable(TRM, ZS_DVOTOCKA) != TRUE)
		Error(511,ERR511);
	Advance();

	if( CheckUSTable(IDN, -1) != TRUE)
		Error(502,ERR502);

	memcpy( &q1, IDNTable[USTable[lGlobIndex]->lIndex], sizeof(IDENTIFIKATOR) );
	Advance();

	Action4(p1,q1);
	Production_d_var_1();
}

void	Production_d_var_1()
{
	if( CheckUSTable(TRM, ZS_TOCKA_ZAREZ) == TRUE )
	{
		Print(27);

		Advance();
		Production_d_var();
	}
	else
		Print(28);
}

void	Production_d_kon()
{
	IDENTIFIKATOR		*p1;
	LITERAL					*q1;
	
	Print(29);

	if( CheckUSTable( IDN,-1) != TRUE )
		Error(502,ERR502);

	p1 = IDNTable[USTable[lGlobIndex]->lIndex];
	Advance();

	if( CheckUSTable(TRM, ZS_JEDNAKO) != TRUE )
		Error(512,ERR512);
	Advance();

	if( CheckUSTable(LIT, -1) != TRUE )
		Error(518, ERR518);

	q1 = LITTable[USTable[lGlobIndex]->lIndex];
	Action2(p1,q1);

	Advance();
	Production_d_kon_1();
}

void	Production_d_kon_1()
{
	if( CheckUSTable(TRM, ZS_TOCKA_ZAREZ) == TRUE )
	{
		Print(30);

		Advance();
		Production_d_kon();
	}
	else
		Print(31);
}

void	Production_b_pro()
{
	IDENTIFIKATOR		*p1;

	if( CheckUSTable(TRM, ZS_PROCEDURA) == TRUE )
	{
		Print(32);

		Advance();

		if( CheckUSTable( IDN, -1) != TRUE )
			Error(502,ERR502);
		
		p1 = IDNTable[USTable[lGlobIndex]->lIndex];
		Advance();
		Action5(p1);

		if( CheckUSTable( TRM, ZS_TOCKA_ZAREZ) != TRUE )
			Error(503,ERR503);
		Advance();

		Production_b_nar();
		Action20();
		Production_b_pro();
	}
	else
		Print(33);
}

void	Production_n_izraz( INTER_RES *t2 )
{
	INTER_RES		p1;

	Print(34),

	Production_t(&p1);
	Production_e_list(p1,t2);
}

void	Production_e_list( INTER_RES p1, INTER_RES *t2)
{
	INTER_RES		q1, r1;

	if( CheckUSTable(TRM, ZS_MINUS) == TRUE )
	{
		Print(35);

		Advance();
		Production_t(&q1);

		Action14(p1,q1,&r1);

		Production_e_list(r1,t2);
	}
	else if( CheckUSTable(TRM, ZS_PLUS) == TRUE )
	{
		Print(36);
		Advance();

		Production_t(&q1);

		Action13(p1,q1,&r1);

		Production_e_list(r1,t2);
	}
	else
	{
		strcpy(t2->strName, p1.strName);
		t2->nType = p1.nType;

		Print(37);
	}
}

void	Production_t( INTER_RES *t2 )
{
	INTER_RES		p1;

	Print(38);

	Production_p(&p1);

	Production_t_list(p1,t2);
}

void	Production_t_list( INTER_RES p1, INTER_RES *t2 )
{
	INTER_RES		q1, r1;

	if( CheckUSTable(TRM, ZS_PUTA) == TRUE )
	{
		Print(39);
		Advance();

		Production_p(&q1);

		Action15(p1,q1,&r1);

		Production_t_list(r1,t2);
	}
	else if( CheckUSTable(TRM, ZS_DIJELJENO) == TRUE )
	{
		Print(40);
		Advance();

		Production_p(&q1);

		Action16(p1,q1,&r1);

		Production_t_list(r1,t2);
	}
	else
	{
		strcpy(t2->strName, p1.strName);
		t2->nType = p1.nType;

		Print(41);
	}
}

void	Production_p( INTER_RES *p2 )
{
	if( CheckUSTable(TRM, ZS_LZAGRADA) == TRUE )
	{
		Print(42);
		Advance();

		Production_n_izraz(p2);

		if( CheckUSTable(TRM, ZS_DZAGRADA) != TRUE )
			Error(519, ERR519);
		Advance();
	}
	else
	{
		Print(43);
		Production_idn_lit(p2);
	}
}

void	Production_idn_lit( INTER_RES *p2 )
{
	IDENTIFIKATOR		p1;
	LITERAL					*lit1;
	CONST						r1;

	if( CheckUSTable(IDN, -1) == TRUE )
	{
		Print(44);
		memcpy( &p1, IDNTable[USTable[lGlobIndex]->lIndex], sizeof(IDENTIFIKATOR) );
	
		Advance();

		Action17(p1);

		strcpy(p2->strName, p1.strName);
		p2->nType = p1.nType;
	}
	else if( CheckUSTable(LIT,-1) == TRUE )
	{
		Print(45);

		lit1 = LITTable[USTable[lGlobIndex]->lIndex];
		Advance();

		Action18(lit1,&r1);

		p2->nType = r1.nType;
		strcpy(p2->strName, r1.strName);
	}
	else
		Error(520, ERR520);
}

void	Production_pro_izr( IDENTIFIKATOR *p1 )
{
	INTER_RES		q1;

	if( CheckUSTable(TRM, ZS_DVOTOCKA) == TRUE)
	{
		Print(46);
		Advance();

		if( CheckUSTable(TRM, ZS_JEDNAKO) != TRUE )
			Error(512,ERR512);
		Advance();

		Production_n_izraz(&q1);
		Action9(p1,q1);
	}
	else
	{
		Print(47);

		Action8(*p1);
	}
}

void	Action1( IDENTIFIKATOR *p2)
{
	if( p2->bDeclared == TRUE )
		Error(1,ERR1);
	
	p2->bDeclared = TRUE;
	p2->nClass = PROGRAM;

	bFirstProgram = bFirstVariable = bFirstConst = TRUE;
}

void	Action2( IDENTIFIKATOR *p2, LITERAL *q2 )
{
	if( p2->bDeclared == TRUE )
		Error(2,ERR2);

	p2->bDeclared = TRUE;
	p2->nClass = CONSTANT;
	p2->nType = q2->nType;
	p2->lPointer = q2;

	if( bFirstConst == TRUE )
	{
		bFirstConst = FALSE;
		if( procType == Z80 )
		{
			fprintf(fpAsm,"\n\t`ORG\t%d\n\n", nROM);
		}
		else
		{
			fprintf(fpAsm,"\n\tORG\t%d\n\n", nROM);
		}
	}
	if( p2->nType == INTEGER )
	{
		if( q2->nLitVal > MAX_INT || q2->nLitVal < MIN_INT )
			Error(100,ERR100);

		if( procType == Z80 )
		{
			fprintf(fpAsm,"%s\t`DW\t%d\n", p2->strName, q2->nLitVal);
			nROM += 2;
		}
		else
		{
			fprintf(fpAsm,"%s\tDWORD\t%d\n", p2->strName, q2->nLitVal);
			nROM += 2;
		}
	}
	else if (p2->nType == REAL)
	{
		if( q2->nLitVal > MAX_MANT || q2->nLitVal < MIN_MANT )
			Error(101,ERR101);
		if( q2->nExpVal > MAX_EXP || q2->nExpVal < MIN_EXP )
			Error(102,ERR102);
		
		if( procType == Z80 )
		{
			fprintf(fpAsm,"%s\t`DW\t%d\n", p2->strName, q2->nLitVal );
			fprintf(fpAsm,"\t`DB\t%d\n", q2->nExpVal );
			nROM += 3;
		}
		else
		{
			fprintf(fpAsm,"%s\tREAL4\t%s\n", p2->strName, q2->strLiteral );
			nROM += 4;
		}
	}
}

void	Action3( IDENTIFIKATOR *p2, IDENTIFIKATOR q2 )
{
	if( p2->bDeclared == TRUE )
		Error(3,ERR3);
	p2->bDeclared = TRUE;

	if( q2.nType == NOTDEFINED )
	{
		if( strcmp(q2.strName, "integer") == 0 )
			q2.nType = INTEGER;
		else
			if( strcmp(q2.strName, "real") == 0 )
				q2.nType = REAL;
			else
				Error(4,ERR4);
	}

	p2->nType = q2.nType;
}

void	Action4( IDENTIFIKATOR *p2, IDENTIFIKATOR q2 )
{
	if( p2->bDeclared == TRUE )
		Error(5,ERR5);

	p2->bDeclared = TRUE;
	p2->nClass = VARIABLE;

	if( q2.nType != INTEGER && q2.nType != REAL )
	{
		if( strcmp(q2.strName, "integer") == 0 )
			q2.nType = INTEGER;
		else
			if( strcmp(q2.strName, "real") == 0 )
				q2.nType = REAL;
			else
				Error(4,ERR4);
	}
	
	p2->nType = q2.nType;

	if( bFirstVariable == TRUE )
	{
		bFirstVariable = FALSE;
		if( procType == Z80 )
		{
			fprintf(fpAsm,"\n\t`ORG\t%d\n\n", nRAM );
		}
		else
		{
			fprintf(fpAsm,"\n\tORG\t%d\n\n", nRAM );
		}
	}
	
	if( p2->nType == INTEGER )
	{
		if( procType == Z80 )
		{
			fprintf(fpAsm,"%s\t`DW\t0\n", p2->strName );
			nRAM += 2;
		}
		else
		{
			fprintf(fpAsm,"%s\tDWORD\t0\n", p2->strName );
			nRAM += 2;
		}
	}
	else if( p2->nType == REAL )
	{
		if( procType == Z80 )
		{
			fprintf(fpAsm,"%s\t`DW 0\n\t`DB 0\n", p2->strName );
			nRAM +=3;
		}
		else
		{
			fprintf(fpAsm,"%s\tREAL4\t0\n", p2->strName );
			nRAM +=4;
		}
	}
	else
		Error(104,ERR104);
}

void	Action5( IDENTIFIKATOR *p2 )
{
	if( p2->bDeclared == TRUE )
		Error(7,ERR7);

	p2->bDeclared = TRUE;
	p2->nClass = PROCEDURE;

	if( bFirstProgram == TRUE )
	{
		bFirstProgram = FALSE;
		if( procType == Z80 )
		{
			fprintf(fpAsm,"\n\t`ORG\t%d\n\n", nROM );
		}
		else
		{
			fprintf(fpAsm,"\n\tORG\t%d\n\n", nROM );
		}
	}

	if( procType == Z80 )
	{
		fprintf(fpAsm,"%s\tPUSH\tAF\n", p2->strName );
		nROM += 1;
	}
	else
	{
	}
}

void	Action7( INTER_RES p2, INTER_RES q2, IDENTIFIKATOR t2, LABEL *k1, LABEL *l1 )
{
	char				strLab[10];

	if( t2.bDeclared != TRUE )
		Error(20,ERR20);

	if( t2.nClass != VARIABLE )
		Error(21,ERR21);

	if( t2.nType != INTEGER )
		Error(22,ERR22);

	if( p2.nType != INTEGER )
		Error(9,ERR9);

	if( q2.nType != INTEGER )
		Error(10,ERR10);

	sprintf(strLab,"LAB%d", LabelNum++);
	sprintf(k1->strLabel, "K_LAB%d", LabelNum++);
	sprintf(l1->strLabel, "L_LAB%d", LabelNum++);

	if( procType == Z80 )
	{
		fprintf(fpAsm,"\tLD\tHL , (%s)\n", p2.strName );
		fprintf(fpAsm,"\tLD\t(%s) , HL\n", t2.strName );
		fprintf(fpAsm,"\tJP\t%s\n", strLab );
		fprintf(fpAsm,"%s\tLD\tHL , (%s)\n", k1->strLabel, t2.strName );
		fprintf(fpAsm,"\tLD\tDE, 1\n" );
		fprintf(fpAsm,"\tADD\tHL, DE\n");
		fprintf(fpAsm,"\tLD\t(%s) , HL\n", t2.strName );
		fprintf(fpAsm,"%s\tLD\tDE, (%s)\n", strLab, q2.strName );
		fprintf(fpAsm,"\tXOR\tA\n");
		fprintf(fpAsm,"\tSBC\tHL, DE\n");
		fprintf(fpAsm,"\tJP\tNC, %s\n", l1->strLabel );
		nROM += 27;
	}
	else
	{
		fprintf(fpAsm, "\tmov\tax, %s\n", p2.strName );
		fprintf(fpAsm, "\tmov\t%s, ax\n", t2.strName );
		fprintf(fpAsm, "\tjmp\t%s\n", strLab );
		fprintf(fpAsm, "%s\tmov\tax, %s\n", k1->strLabel, t2.strName );
		fprintf(fpAsm, "\tadd\tax, 1\n");
		fprintf(fpAsm, "\tmov\t%s, ax\n", t2.strName );
		fprintf(fpAsm, "%s\tmov\tcx, %s\n", strLab, q2.strName );
		fprintf(fpAsm, "\tsub\tax, cx\n");
		fprintf(fpAsm, "\tjnc\t%s\n", l1->strLabel );
	}
}

void	Action8( IDENTIFIKATOR p2 )
{
	if( p2.bDeclared != TRUE )
		Error(19,ERR19);

	if( p2.nClass != PROCEDURE )
		Error(11,ERR11);

	if( procType == Z80 )
	{
		fprintf(fpAsm,"\tCALL\t%s", p2.strName );
		nROM += 3;
	}
	else
	{
		fprintf(fpAsm,"\tCALL\t%s", p2.strName );
		nROM += 3;
	}
}

void	Action9( IDENTIFIKATOR *p2, INTER_RES q2 )
{
	if( p2->bDeclared != TRUE )
		Error(23,ERR23);

	if( p2->nClass != VARIABLE )
		Error(12,ERR12);

	if( q2.nType != p2->nType )
		Error(13,ERR13);

	p2->bAssociated = TRUE;

	if( procType == Z80 )
	{
		fprintf(fpAsm,"\tLD\tHL , (%s)\n", q2.strName );
		fprintf(fpAsm, "\tLD\t(%s) , HL\n", p2->strName );
		nROM += 6;
	}
	else
	{
		fprintf(fpAsm, "\tmov\tax, %s\n", q2.strName );
		fprintf(fpAsm, "\tmov\t%s, ax\n", p2->strName );
	}
}

void	Action10( INTER_RES p2, INTER_RES q2, LABEL *l1 )
{
	if( p2.nType != q2.nType )
		Error(14,ERR14);

	sprintf(l1->strLabel, "LAB%d", LabelNum++);

	if( procType == Z80 )
	{
		fprintf(fpAsm, "\tLD\tHL, (%s)\n", p2.strName );
		fprintf(fpAsm, "\tLD\tDE, (%s)\n", q2.strName );
		fprintf(fpAsm, "\tXOR\tA\n");
		fprintf(fpAsm, "\tSBC\tHL, DE\n");
		fprintf(fpAsm, "\tJP\tNZ, %s\n", l1->strLabel );
		nROM += 11;
	}
	else
	{
		fprintf(fpAsm, "\tmov\tax, %s\n", p2.strName );
		fprintf(fpAsm, "\tcmp\tax, %s\n", q2.strName );
		fprintf(fpAsm, "\tjne\t%s\n", l1->strLabel );
	}
}

void	Action11( INTER_RES p2, INTER_RES q2, LABEL *l1 )
{
	if( p2.nType != q2.nType )
		Error(14,ERR14);

	sprintf(l1->strLabel, "LAB%d", LabelNum++);

	if( procType == Z80 )
	{
		fprintf(fpAsm, "\tLD\tHL , (%s)\n", q2.strName );
		fprintf(fpAsm, "\tLD\tDE , (%s)\n", p2.strName );
		fprintf(fpAsm, "\tXOR\tA\n");
		fprintf(fpAsm, "\tSBC\tHL, DE\n");
		fprintf(fpAsm, "\tJP\tNC , %s\n", l1->strLabel );
		nROM += 11;
	}
	else
	{
		fprintf(fpAsm, "\tmov\tax, %s\n", p2.strName );
		fprintf(fpAsm, "\tcmp\tax, %s\n", q2.strName );
		fprintf(fpAsm, "\tjle\t%s\n", l1->strLabel );
	}
}

void	Action12( INTER_RES p2, INTER_RES q2, LABEL *l1 )
{
	if( p2.nType != q2.nType )
		Error(14,ERR14);

	sprintf(l1->strLabel, "LAB%d", LabelNum++);

	if( procType == Z80 )
	{
		fprintf(fpAsm, "\tLD\tHL , (%s)\n", p2.strName );
		fprintf(fpAsm, "\tLD\tDE , (%s)\n", q2.strName );
		fprintf(fpAsm, "\tXOR\tA\n");
		fprintf(fpAsm, "\tSBC\tHL , DE\n");
		fprintf(fpAsm, "\tJP\tNC , %s\n", l1->strLabel );
		nROM += 11;
	}
	else
	{
		fprintf(fpAsm, "\tmov\tax, %s\n", p2.strName );
		fprintf(fpAsm, "\tcmp\tax, %s\n", q2.strName );
		fprintf(fpAsm, "\tjge\t%s\n", l1->strLabel );
	}
}

void	Action13( INTER_RES p2, INTER_RES q2, INTER_RES *r1 )
{
	INTER_RES		*Adr;

	if( p2.nType != q2.nType )
		Error(15,ERR15);

	/*	PROŠIRI TABLICU MEDJUREZULTATA */
	Adr = InsertInterRes();
	
	strcpy(r1->strName, Adr->strName);
	r1->nType = Adr->nType = p2.nType;

	if( p2.nType == INTEGER )
	{
		if( procType == Z80 )
		{
			fprintf(fpAsm, "\tLD\tHL, (%s)\n", p2.strName );
			fprintf(fpAsm, "\tLD\tDE , (%s)\n", q2.strName );
			fprintf(fpAsm, "\tADD\tHL , DE\n");
			fprintf(fpAsm, "\tLD\t(%s) , HL\n", r1->strName );
		}
		else
		{
			fprintf(fpAsm, "\tmov\tax, %s\n", p2.strName );
			fprintf(fpAsm, "\tadd\tax, %s\n", q2.strName );
			fprintf(fpAsm, "\tmov\t%s, ax\n", r1->strName );
		}
	}
	else if( p2.nType == REAL )
	{
		bRealAdd = TRUE;
		if( procType == INTEL)
		{
			fprintf(fpAsm, "\tfld\t%s\n", p2.strName );
			fprintf(fpAsm, "\tfld\t%s\n", q2.strName );
			fprintf(fpAsm, "\tfadd\n");
			fprintf(fpAsm, "\tfstp\t%s\n", r1->strName );
		}
	}
}

void	Action14( INTER_RES p2, INTER_RES q2, INTER_RES *r1 )
{
	INTER_RES		*Adr;
	
	if( p2.nType != q2.nType )
		Error(15,ERR15);

	/*	PROŠIRI TABLICU MEDJUREZULTATA */
	Adr = InsertInterRes();
	
	strcpy(r1->strName, Adr->strName);
	r1->nType = Adr->nType = p2.nType;

	if( p2.nType == INTEGER )
	{
		if( procType == Z80 )
		{
			fprintf(fpAsm, "\tLD\tHL , (%s)\n", p2.strName );
			fprintf(fpAsm, "\tLD\tDE , (%s)\n", q2.strName );
			fprintf(fpAsm, "\tXOR\tA\n");
			fprintf(fpAsm, "\tSBC\tHL , DE\n");
			fprintf(fpAsm, "\tLD\t(%s) , HL\n", r1->strName );
		}
		else
		{
			fprintf(fpAsm, "\tmov\tax, %s\n", p2.strName );
			fprintf(fpAsm, "\tsub\tax, %s\n", q2.strName );
			fprintf(fpAsm, "\tmov\t%s, ax\n", r1->strName );
		}
	}
	else if( p2.nType == REAL )
	{
		bRealSub = TRUE;
		if( procType == INTEL)
		{
			fprintf(fpAsm, "\tfld\t%s\n", p2.strName );
			fprintf(fpAsm, "\tfld\t%s\n", q2.strName );
			fprintf(fpAsm, "\tfsub\n");
			fprintf(fpAsm, "\tfstp\t%s\n", r1->strName );
		}
	}
}

void	Action15( INTER_RES p2, INTER_RES q2, INTER_RES *r1 )
{
	INTER_RES		*Adr;

	if( p2.nType != q2.nType )
		Error(15,ERR15);

	/*	PROŠIRI TABLICU MEDJUREZULTATA */
	Adr = InsertInterRes();
	
	strcpy(r1->strName, Adr->strName);
	r1->nType = Adr->nType = p2.nType;

	if( p2.nType == INTEGER )
	{
		bIntMul = TRUE;

		if( procType == Z80 )
		{
			fprintf(fpAsm, "\tLD\tHL, (%s)", p2.strName );
			fprintf(fpAsm, "\tLD\tDE, (%s)", q2.strName );
			fprintf(fpAsm, "\tCALL\tMULINT");
			fprintf(fpAsm, "\tLD\t(%s) , HL", r1->strName );
		}
		else
		{
			fprintf(fpAsm, "\tmov\tax, %s\n", p2.strName );
			fprintf(fpAsm, "\timul\tax, %s\n", q2.strName );
			fprintf(fpAsm, "\tmov\t%s, ax\n", r1->strName );
		}
	}
	else if( p2.nType == REAL )
	{
		bRealMul = TRUE;
		if( procType == INTEL)
		{
			fprintf(fpAsm, "\tfld\t%s\n", p2.strName );
			fprintf(fpAsm, "\tfld\t%s\n", q2.strName );
			fprintf(fpAsm, "\tfmul\n");
			fprintf(fpAsm, "\tfstp\t%s\n", r1->strName );
		}
	}
}

void	Action16( INTER_RES p2, INTER_RES q2, INTER_RES *r1 )
{
	INTER_RES		*Adr;

	if( p2.nType != q2.nType )
		Error(15,ERR15);

	/*	PROŠIRI TABLICU MEDJUREZULTATA */
	Adr = InsertInterRes();
	
	strcpy(r1->strName, Adr->strName);
	r1->nType = Adr->nType = p2.nType;

	if( p2.nType == INTEGER )
	{
		bIntDiv = TRUE;

		if( procType == Z80 )
		{
			fprintf(fpAsm, "\tLD\tHL, (%s)", p2.strName );
			fprintf(fpAsm, "\tLD\tDE, (%s)", q2.strName );
			fprintf(fpAsm, "\tCALL\tDIVINT");
			fprintf(fpAsm, "\tLD\t(%s) , HL", r1->strName );
		}
		else
		{
			fprintf(fpAsm, "\tmov\tax, %s\n", p2.strName );
			fprintf(fpAsm, "\tidiv\tax, %s\n", q2.strName );
			fprintf(fpAsm, "\tmov\t%s, ax\n", r1->strName );
		}
	}
	else if( p2.nType == REAL )
	{
		bRealDiv = TRUE;
		if( procType == INTEL)
		{
			fprintf(fpAsm, "\tfld\t%s\n", p2.strName );
			fprintf(fpAsm, "\tfld\t%s\n", q2.strName );
			fprintf(fpAsm, "\tfdiv\n");
			fprintf(fpAsm, "\tfstp\t%s\n", r1->strName );
		}
	}
}

void	Action17( IDENTIFIKATOR p2 )
{
	if( p2.bDeclared != TRUE )
		Error(16,ERR16);

	if( p2.nClass == VARIABLE )
	{
		if( p2.bAssociated != TRUE )
			Error(17,ERR17);
	}
	else if( p2.nClass != CONSTANT )
		Error(18,ERR18);
}

void	Action18( LITERAL *p2, CONST *r1 )
{
	CONST*	Adr;

	if( p2->nType == INTEGER )
	{
		if( p2->nLitVal > MAX_INT || p2->nLitVal < MIN_INT )
			Error(100,ERR100);
	}
	else if( p2->nType == REAL )
	{
		if( p2->nLitVal > MAX_MANT || p2->nLitVal < MIN_MANT )
			Error(101,ERR101);
		if( p2->nExpVal > MAX_EXP || p2->nExpVal < MIN_EXP )
			Error(102,ERR102);
	}
	
	/* PROŠIRI TABLICU KONSTANTI */
	Adr = InsertConstant();

	Adr->lPointer = p2;

	strcpy(r1->strName, Adr->strName);
	r1->nType = Adr->nType = p2->nType;
}

void	Action20( void )
{
	if( procType == Z80 )
	{
		fprintf(fpAsm,"\tPOP\tAF\n");
		fprintf(fpAsm,"\tRET\n\n");
		nROM += 2;
	}
	else
	{
	}
}

void	Action21( void )
{
	if( bFirstProgram == TRUE )
	{
		bFirstProgram = FALSE;
	
		if( procType == Z80 )
		{
			fprintf(fpAsm,"\n\t`ORG\t%d\n\n", nROM );
		}
		else
		{
			fprintf(fpAsm,"\n\tORG\t%d\n\n", nROM );
		}
	}
}

void	Action22( void )
{
	int		i;

	if( bIntMul != FALSE )
		WriteIntMul();
	if( bIntDiv != FALSE )
		WriteIntDiv();
	
	if( bRealAdd != FALSE )
		WriteRealAdd();
	if( bRealSub != FALSE )
		WriteRealSub();
	
	if( bRealMul != FALSE )
		WriteRealMul();
	if( bRealDiv != FALSE )
		WriteRealDiv();

	if( procType == Z80 )
	{
		fprintf(fpAsm, "\n\t`ORG\t%d\n\n", nRAM );
	}
	else
	{
		fprintf(fpAsm, "\n\tORG\t%d\n\n", nRAM );
	}
	
	for( i=0; i<IRESNum; i++ )
		if( IRESTable[i]->nType == INTEGER )
		{
			if( procType == Z80 )
			{
				fprintf(fpAsm,"%s\t`DW\t0\n", IRESTable[i]->strName );
				nRAM += 2;
			}
			else
			{
				fprintf(fpAsm,"%s\tDWORD\t0\n", IRESTable[i]->strName );
				nRAM += 2;
			}
		}
		else if( IRESTable[i]->nType == REAL )
		{
			if( procType == Z80 )
			{
				fprintf(fpAsm, "%s\t`DW\t0\n", IRESTable[i]->strName );
				fprintf(fpAsm, "\t\t`DB\t0\n");
				nRAM += 3;
			}
			else
			{
				fprintf(fpAsm, "%s\tREAL4\t0\n", IRESTable[i]->strName );
				nRAM += 4;
			}
		}

	fprintf(fpAsm, "\n\t`ORG\t%d\n\n", nROM );
	for( i=0; i<CONSTNum; i++ )
		if( CONSTTable[i]->nType == INTEGER )
		{
			if( procType == Z80 )
			{
				fprintf(fpAsm, "%s\t`DW\t%d\n", CONSTTable[i]->strName, (CONSTTable[i]->lPointer)->nLitVal );
				nROM += 2;
			}
			else
			{
				fprintf(fpAsm, "%s\tDWORD\t%d\n", CONSTTable[i]->strName, (CONSTTable[i]->lPointer)->nLitVal );
				nROM += 2;
			}
		}
		else if( CONSTTable[i]->nType == REAL )
		{
			if( procType == Z80 )
			{
				fprintf(fpAsm, "%s\t`DW\t%d\n", CONSTTable[i]->strName, (CONSTTable[i]->lPointer)->nLitVal );
				fprintf(fpAsm, "\t\t`DB\t%d\n", (CONSTTable[i]->lPointer)->nExpVal );
				nROM += 3;
			}
			else
			{
				fprintf(fpAsm, "%s\tREAL4\t%d\n", CONSTTable[i]->strName, (CONSTTable[i]->lPointer)->strLiteral );
				nROM += 4;
			}
		}
}

void	Action23( LABEL *k1 )
{
	sprintf(k1->strLabel, "LAB%d", LabelNum++);

	if( procType == Z80 )
	{
		fprintf(fpAsm,"%s\tNOP\n", k1->strLabel );
		nROM++;
	}
	else
	{
		fprintf(fpAsm,"%s\tnop\n", k1->strLabel );
		nROM++;
	}
}

void	Action24( LABEL *k1)
{
	sprintf(k1->strLabel, "LAB%d", LabelNum++);

	if( procType == Z80 )
	{
		fprintf(fpAsm, "\tJP\t%s\n", k1->strLabel );
		nROM += 3;
	}
	else
	{
		fprintf(fpAsm, "\tjmp\t%s\n", k1->strLabel );
		nROM += 6;
	}
}

void	Action25( LABEL k2, LABEL l2 )
{
	if( procType == Z80 )
	{
		fprintf(fpAsm, "\tJP\t%s\n", k2.strLabel );
		fprintf(fpAsm, "%s\tNOP\n", l2.strLabel );
		nROM += 4;
	}
	else
	{
		fprintf(fpAsm, "\tjmp\t%s\n", k2.strLabel );
		fprintf(fpAsm, "%s\tnop\n", l2.strLabel );
		nROM += 7;
	}
}

void	Action26( LABEL l2 )
{
	if( procType == Z80 )
	{
		fprintf(fpAsm, "%s\tNOP\n", l2.strLabel );
		nROM++;
	}
	else
	{
		fprintf(fpAsm, "%s\tnop\n", l2.strLabel );
		nROM++;
	}
}

void	Action27( LABEL k2 )
{
	if( procType == Z80 )
	{
		fprintf(fpAsm, "%s\tNOP\n", k2.strLabel );
		nROM++;
	}
	else
	{
		fprintf(fpAsm, "%s\tnop\n", k2.strLabel );
		nROM++;
	}
}

void	WriteIntMul()
{
	if( procType == Z80 )
	{
		fprintf(fpAsm, "MULINT\n");
		fprintf(fpAsm, "\tLD\tC , L\n");
		fprintf(fpAsm, "\tLD\tB , H\n");
		fprintf(fpAsm, "\tLD\tHL , 0\n");
		fprintf(fpAsm, "\tLD\tA , 15\n");
		fprintf(fpAsm, "MLP\tSLA\tE\n");
		fprintf(fpAsm, "\tRL\tD\n");
		fprintf(fpAsm, "\tJR\tNC , MLP1\n");
		fprintf(fpAsm, "\tADD\tHL , BC\n");
		fprintf(fpAsm, "MLP1\tADD\tHL , HL\n");
		fprintf(fpAsm, "\tDEC\tA\n");
		fprintf(fpAsm, "\tJR\tNZ , MLP\n");
		fprintf(fpAsm, "\tOR\tD\n");
		fprintf(fpAsm, "\tRET\tP\n");
		fprintf(fpAsm, "\tADD\tHL , BC\n");
		fprintf(fpAsm, "\tRET\n\n");
	}
	else
	{
	}
}

void	WriteIntDiv()
{
	if( procType == Z80 )
	{
		fprintf(fpAsm, "DIVINT\n");
		fprintf(fpAsm, "\tLD\tA, E\n");
		fprintf(fpAsm, "\tOR\tD\n");
		fprintf(fpAsm, "\tJR\tNZ, DIJELI\n");
		fprintf(fpAsm, "\tLD\tHL, 0\n");
		fprintf(fpAsm, "\tLD\tD, H\n");
		fprintf(fpAsm, "\tLD\tE, L\n");
		fprintf(fpAsm, "\tSCF\n");
		fprintf(fpAsm, "\tRET\n");
		fprintf(fpAsm, "DIJELI\tLD\tC, L\n");
		fprintf(fpAsm, "\tLD\tA, H\n");
		fprintf(fpAsm, "\tLD\tHL, 0\n");
		fprintf(fpAsm, "\tLD\tB, 16\n");
		fprintf(fpAsm, "\tOR\tA\n");
		fprintf(fpAsm, "PETLJE\tRL\tC\n");
		fprintf(fpAsm, "\tRLA\n");
		fprintf(fpAsm, "\tRL\tL\n");
		fprintf(fpAsm, "\tRL\tH\n");
		fprintf(fpAsm, "\tPUSH\tHL\n");
		fprintf(fpAsm, "\tSBC\tHL, DE\n");
		fprintf(fpAsm, "\tCCF\n");
		fprintf(fpAsm, "\tJR\tC, DROP\n");
		fprintf(fpAsm, "\tEX\t(SP), HL\n");
		fprintf(fpAsm, "\tDROP\tINC\tSP\n");
		fprintf(fpAsm, "\tINC\tSP\n");
		fprintf(fpAsm, "\tDJNZ\tPETLJA\n");
		fprintf(fpAsm, "\tEX\tDE, HL\n");
		fprintf(fpAsm, "\tRL\tC\n");
		fprintf(fpAsm, "\tLD\tL, C\n");
		fprintf(fpAsm, "\tRLA\n");
		fprintf(fpAsm, "\tLD\tH, L\n");
		fprintf(fpAsm, "\tLD\tH, A\n");
		fprintf(fpAsm, "\tOR\tA\n");
		fprintf(fpAsm, "\tRET\n");
	}
	else
	{
	}
}

void	WriteRealAdd()
{
}

void	WriteRealSub()
{
}

void	WriteRealMul()
{
}

void	WriteRealDiv()
{
}

void	Print( int i )
{
	printf("Produkcija broj  : %d ,   index : %ld \n",i, lGlobIndex );
	fprintf(fpReport, "Produkcija broj  : %d ,   index : %ld \n",i, lGlobIndex );
}

int	CheckUSTable( enum KLASA nClass, int Index )
{
	int		ret = TRUE;

	if( Index >= 0 )
	{
		if( !(USTable[lGlobIndex]->nClass == nClass && USTable[lGlobIndex]->lIndex == Index) )
			ret = FALSE;
	}
	else
		if( USTable[lGlobIndex]->nClass != nClass )
			ret = FALSE;

	return	ret;
}

int	FindErrorLine( void )
{
	int i;

	for(i=0; i<LineNum; i++ )
		if( lGlobIndex > LineStartsWithSymNum[i] && lGlobIndex <= LineStartsWithSymNum[i+1] )
			return (i+1);
	return(0);
}

void	Error( int nErrorNum, char *strErrorText )
{
		printf("Greska u liniji : %d \n%s", FindErrorLine(), strErrorText );
		fprintf(fpReport, "Greska u liniji : %d \n%s", FindErrorLine(), strErrorText );
		
		exit(nErrorNum);
}
