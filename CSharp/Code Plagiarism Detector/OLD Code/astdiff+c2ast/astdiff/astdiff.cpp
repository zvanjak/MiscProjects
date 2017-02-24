#include <stdio.h>
#include <stdarg.h>

#include <map>
#include <utility>
#include <vector>

#include <ast.h>
#include "astdiff.h"

#define WARN	"Warning: "

using namespace std;


bool verbose = false;
bool human = true;

#ifdef DEBUG
bool debug = false;
#endif

void help(const char *myfname = "astdiff") {
	printf("Usage: %s file1.c file2.c [flags]\n", myfname);
	puts("Flags:");
	puts(" -v = verbose");
#ifdef DEBUG
	puts(" -d = print debug information");
#endif
	puts(" -i = toggle human interface (default: true)");
	puts(" -h = this help");
	puts("");
}

void errprintf(const char *msg, ...) {
	va_list vl;
	va_start(vl, msg);
	vfprintf(stderr, msg, vl);
	va_end(vl);
}

inline void vprintf(const char *msg, ...) {
	if (verbose) {
		va_list vl;
		va_start(vl, msg);
		vprintf(msg, vl);
		va_end(vl);
	}
}

#ifdef DEBUG
inline void dprintf(const char *msg, ...) {
	if (debug) {
		va_list vl;
		va_start(vl, msg);
		vprintf(msg, vl);
		va_end(vl);
	}
}
#else
#	define dprintf(...)
#endif


void AST_node2::Dump(int level) const {
	PutSpaces(level);
	printf("ID: %u\n", ID);
	AST_anode::Dump(level);
}

unsigned int AST_node2::SetIDs(unsigned int t) {
	ID = t++;
	for (unsigned int i=0; i < GetNKids(); ++i) {
		t = (*this)[i].SetIDs(t);
	}
	return t;
}

int AST_node2::SetTotalNKids(){
	int tmp = GetNKids();
	for (unsigned int i=0; i < GetNKids(); ++i) {
		tmp += (*this)[i].SetTotalNKids();
	}	
	return TotalNKids = tmp;
}

// koverta c u AST_node2 stablo i hendla errore
bool proc_code(AST_node2 &kod, source &src, const char *title) {
	try {
		AST::FillCustomAST(kod, src);
		return true;
	} catch (const string &err_str) {
		errprintf("Greska: %s!\n", err_str.c_str());
		if (!src.Processed()) src.DumpCodePos(stderr);
	} catch (const char *err_cstr) {
		errprintf("Greska: %s!\n", err_cstr);
		if (!src.Processed()) src.DumpCodePos(stderr);
	} catch (const SyntaxError &synerr) {
		errprintf("Syntax error: %s!\n", synerr.error.c_str());
		synerr.position.Dump(stderr);
	} catch (...) {
		errprintf("Unknown error!\n");
	}

	errprintf("Greska u %s kodu!\n", title);

	return false;
}

// louda sors i hendla errore
bool load_source(source &s1, const char *fn1, const char *title) {
	try {
		s1.Load(fn1);
		return true;

	} catch (const char *cs) {
		errprintf("Greska kod ucitavanja %s koda: %s\n", title, cs);
	} catch (const string &s) {
		errprintf("Greska kod ucitavanja %s koda: %s\n", title, s.c_str());
	} catch (...) {
		errprintf("Unknown error!\n");
	}
	return false;
}


map<pair<int, int>, int> memoo;

int CompareNodes(const AST_node2 &a, const AST_node2 &b) {
	dprintf("CompareNodes: %d, %d\n", a.ID, b.ID);
	dprintf(" type: %d ?= %d: %d\n", a.type, b.type, (int)(a.type==b.type));
	dprintf(" src: \"%s\" ?= \"%s\": %d\n", a.src.c_str(), b.src.c_str(), (int)(a.src.str() == b.src.str()));
	if (a.type == ASTnt_function && b.type == ASTnt_function)
		dprintf(" funcname: \"%s\" ?= \"%s\": %d\n", a.function_data.name.c_str(), b.function_data.name.c_str(), (int)(a.function_data.name == b.function_data.name));

	if ( a.type != b.type ) return 1;
	if ( a.src.str() != b.src.str() ) return 1;
	if ( a.type == ASTnt_function &&
		a.function_data.name != b.function_data.name) return 1;
	return 0;
}


// Izracunava AST Edit Distance, O(N ^ 4 log N), ali ovo nije minimalni O.
// Preciznije je O(N ^ 2 log N * max(drvo A svaki cvor GetNKids) * max(drvo B svaki cvor GetNKids))
int ASTEditDistance(const AST_node2 &a, const AST_node2 &b){
	// Memooizacija
	map<pair<int, int>, int>::iterator it = memoo.find(make_pair(a.ID, b.ID));
	if ( it != memoo.end() ) return it->second;

	vprintf("Usporedjujem : %s(%d) %s(%d)\n", a.TypeToString(a.type).c_str(), a.GetNKids(), b.TypeToString(b.type).c_str(), b.GetNKids() );
	
	vector<vector<int> > child_ed;
	child_ed.resize(a.GetNKids() + 1);
	child_ed[0].resize(b.GetNKids() + 1);
	for (unsigned int i = 0; i <= b.GetNKids(); i++)
		child_ed[0][i] = i;
	
	for (unsigned int i = 1; i <= a.GetNKids(); i++){
		child_ed[i].resize(b.GetNKids() + 1);
		child_ed[i][0] = i;
		for (unsigned int j = 1; j <= b.GetNKids(); j++){
			// Dodavanje djeteta b[j]
			child_ed[i][j] = child_ed[i][j - 1] + b[j - 1].TotalNKids + 1;
			// Dodavanje djeteta a[i]
			if ( child_ed[i][j] > child_ed[i - 1][j] + a[i - 1].TotalNKids + 1 )
					child_ed[i][j] = child_ed[i - 1][j] + a[i - 1].TotalNKids + 1;
			// Izmjena
			int tmp = ASTEditDistance(a[i - 1], b[j - 1]);
			if ( child_ed[i][j] > child_ed[i - 1][j - 1] + tmp )
				child_ed[i][j] = child_ed[i - 1][j - 1] + tmp;
		}
	}
	
	int cn_ab = CompareNodes(a, b);	// komparirajmo samo jednom da bude manje smeca u debug ispisu

	vprintf("Usporedio: %s %s i mislim: %d (%d)\n", a.TypeToString(a.type).c_str(), b.TypeToString(b.type).c_str(), child_ed[a.GetNKids()][b.GetNKids()] + cn_ab, cn_ab);
	
	return child_ed[a.GetNKids()][b.GetNKids()] + cn_ab;
}





int main(int argn, char *argv[]) {
	source src1, src2;
	AST_node2 kod1, kod2;

	if (argn < 3) {
		help(argv[0]);
		return 1;
	}

	// procesira argumente
	for (int i = 3; i < argn; ++i) {
		if (*argv[i] != '-') {
			errprintf("Not an argument: %s\n", argv[i]);
			return 1;
		}

		switch(argv[i][1]) {
			case 'v':
				verbose = true;
				printf("Verbose is on!\n");
				break;

			case 'd':
#ifdef DEBUG
				debug = true;
				printf("Debugging is on!\n");
				if (!verbose) {
					verbose = true;
					printf("Verbose turned on!\n");
				}
#else
				errprintf(WARN "Not compiled with debug output support!\n");
#endif
				break;

			case 'i':
				human = !human;
				vprintf("Human interface mode is %s\n", human ? "enabled" : "disabled");
				break;

			case 'h':
				help();
				break;

			default:
				errprintf("Unknown argument: %c\n", argv[i][1]);
				return 1;
		}
	}

	// ucitava sorsove
	if (!load_source(src1, argv[1], "prvog") ||
	    !load_source(src2, argv[2], "drugog"))
		return 1;

	// prosecira (konverta) u AST
	if (!proc_code(kod1, src1, "prvom") ||
	    !proc_code(kod2, src2, "drugom"))
		return 1;

	// ID-jizira
	kod1.SetIDs(0);
	kod2.SetIDs(0);
	kod1.SetTotalNKids();
	kod2.SetTotalNKids();

	// kompar
	int ast_ed = ASTEditDistance(kod1, kod2);
	if (human) printf("Abstract Syntax Tree Edit Distance je: ");
	printf("%d\n", ast_ed);

	return 0;
}
