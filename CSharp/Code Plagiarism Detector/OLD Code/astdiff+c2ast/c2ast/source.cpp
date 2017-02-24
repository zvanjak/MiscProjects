#include "stdafx.h"
#include "source.h"
#include "stringutils.h"
#include <ctype.h>

source::source() {
	_init();
}

source::source(const char *s) {
	*this = s;
}

source::source(const string &s) {
	*this = s;
}

void source::_init() {
	tokenpos = 0;
	lasttokenpos = string::npos;
	curptoken.clear();

	curcodepos.x = curcodepos.y = 1;
	lastcodepos.x = lastcodepos.y = 0;
}

void source::Dump() const {
	puts(src.c_str());
}

void source::DumpCodePos(FILE *out) const {
	curcodepos.Dump(out);
}

void source::clear() {
	src.clear();
	_init();
}

bool source::empty() const {
	return src.empty();
}

strpos source::size() const {
	return src.size();
}

void source::Load(const string &fname) {
	// Ucita fajl
	if (!LoadFileToString(fname, src))
		throw "Ne mogu ucitat fajl!";

	// Malo ga prepravi... (i automatski napravi _init())
	FilterCode();
}

void source::FilterCode() {
	// * Izbaci svaki \\\n 
	str_replace(src, "\\\n", "");	//FIXME: kod prvog isspace treba ubacit \n, jer inace se ne moze vise snac pomocu onog "greska je u redu tom i tom"

	// makne komentare
	RemoveComments();
	RemovePreprocessor();

	// mora is pocetka nakon svega ovoga...
	_init();
}

// FIXME: treba ostavljat prazne redove da se je moguce snac pomocu onog "greska je u redu tom i tom"
void source::RemoveComments() {
	strpos k1, k2, l = 0;

	while (((k1 = CodeSearch(src, "/*", l)) != string::npos) | ((k2 = CodeSearch(src, "//", l)) != string::npos)) {
		if (k1 == string::npos) goto makni2;
		else if (k2 == string::npos) goto makni1;
		else if (k1 > k2) goto makni2;
		
makni1:
		k2 = src.find("*/", k1);
		if (k2 == string::npos) {
			src.erase(k1);
			break;
		}
		src.erase(k1, k2-k1+2);
		l=k1;
		continue;

makni2:
		k1 = src.find("\n", k2);
		if (k1 == string::npos) {
			src.erase(k2);
			break;
		}
		src.erase(k2, k1-k2);
		l=k2;
	}
}

// Mice preprocesorske linije, ali tako da ostavi \n na mjestu, tako da se mogu nac onda greske prema "u retku tom i tom"
void source::RemovePreprocessor() {
	strpos p, l;
	for (l=0;(p=src.find('#', l)) != string::npos;l=p) {
		if (!p || src[p-1] == '\n') {
			strpos e = src.find('\n', p);
			if (e != string::npos) {
				src.erase(p, e-p);
			} else {
				src.erase(p);
				break;
			}
		} else {
			++p;
		}
	}
}

const source & source::operator = (const char *s) {
	src = s;
	FilterCode();
	return *this;
}

const source & source::operator = (const string &s) {
	src = s;
	FilterCode();
	return *this;
}

const string & source::operator += (const string &s) {
	src += s;
	FilterCode();
	return src;
}

void source::ThrowSyntaxError(string err_msg) const {
	throw SyntaxError(*this, err_msg);
}

bool source::islblchar(char c) {
	return isalnum(c) || c=='_';
}

void source::UnGetPToken() {
	if (lasttokenpos == string::npos)
		throw "UnGetPToken() can be called only once";

	tokenpos = lasttokenpos;
	curcodepos = lastcodepos;
	curptoken.clear();

	lasttokenpos = string::npos;	// nema "jos nazad"
}

bool source::Processed() const {
	if (tokenpos >= src.size()) return true;

	const char *c = src.c_str() + tokenpos;
	for (;*c && isspace(*c);++c);
	return !*c;
}

static char NumFLUAttrib(char c) {
	if (incharlist(toupper(c), "FLU"))
		return c;
	return 0;
}

string source::TryGetNumber() const {
	const char *c = src.c_str() + tokenpos;
	string rez;

	if (tokenpos > src.size()-2) return string();

	if (*c == '0' && *(c+1) == 'x') {	// hex?
		rez="0x";
		for (c+=2; incharlist(toupper(*c), "0123456789ABCDEF"); ++c)
			rez+=*c;
	} else if (*c == '0') {			// oct?
		rez="0";
		for (++c; incharlist(*c, "01234567"); ++c)
			rez+=*c;
	} else if (isdigit(*c) || (*c == '.' && isdigit(*(c+1)))) {	// float ili nekaj obicnog?
		bool imatocku = *c == '.';
		bool imae = false;

		for (;;) {
			rez+=*c;
			++c;
			if (*c == '.') {
				if (imatocku)
					ThrowSyntaxError("Visak tocaka u decimalnom broju");
				imatocku = true;
				continue;
			}
			if (toupper(*c) == 'E') {
				if (imae)
					ThrowSyntaxError("Visak E-ova u broju");
				imae = true;
				continue;
			}
			if (!isdigit(*c)) break;
		}
	} else {				// nije broj
		return string();
	}

	if (NumFLUAttrib(*c)) rez+=*c;	// nastavak na broj?

	return rez;
}

bool source::SkipSpaces() {
	if (tokenpos >= src.size()) return false;
	while (isspace(src[tokenpos])) {
		curcodepos.y += src[tokenpos] == '\n';

		++tokenpos;
		if (tokenpos >= src.size()) return false;
	}
	curcodepos.x = CharsInLine(src, tokenpos);
	return true;
}

string source::TryGetOperator() const {
	static const char *bigoperators[] = {
		"++", "--", "->", "<<=", ">>=", "<<", ">>", "<=", ">=",
		"==", "!=", "&&", "||", "+=", "-=", "*=", "/=", "%=", "&=",
		"^=", "|="
	};
	static const char opchars[] = "/*-+:?%^!&|=~.><";

	const char *s = src.c_str() + tokenpos;

	// da li je veliki operator?
	for (const char **bigops = bigoperators; *bigops; ++bigops) {
		if (!strncmp(s, *bigops, strlen(*bigops)))
			return *bigops;
	}

	// a da li je mali operator?
	if (incharlist(*s, opchars)) {
		char tmpstr[] = {*s, 0};
		return tmpstr;
	}

	return string();
}

string source::GetNextPToken() {
	string tok;

	if (!SkipSpaces()) goto kraj;

	_SetLastPosData();

	// operator(i) ili broj ili labela ili zagrade i ';' i ',' ili string
	if ((tok = TryGetOperator()).size()) {
		curptoken = tok;
		tokenpos += tok.size();
	} else if ((tok = TryGetNumber()).size()) {
		curptoken = tok;
		tokenpos += tok.size();
	} else if (islblchar(src[tokenpos])) {
		while (islblchar(src[tokenpos]) && tokenpos < src.size())
			curptoken += src[tokenpos++];
	} else if (incharlist(src[tokenpos], "{}()[];,")) {
		curptoken = src[tokenpos++];
	} else if (src[tokenpos] == '\'') {
		do {
			curptoken += src[tokenpos];
			++tokenpos;
		} while (tokenpos < src.size() && (src[tokenpos] != '\'' || src[tokenpos-1] == '\\'));
		if (tokenpos >= src.size()) goto kraj;
		++tokenpos;
		curptoken += '\'';
	} else if (src[tokenpos] == '"') {
		do {
			curptoken += src[tokenpos];
			++tokenpos;
		} while (tokenpos < src.size() && (src[tokenpos] != '"' || src[tokenpos-1] == '\\'));
		if (tokenpos >= src.size()) goto kraj;
		++tokenpos;
		curptoken += '"';
	} else {
		ThrowSyntaxError(string("Unknown char: ") + src[tokenpos]);
	}

	return curptoken;

kraj:
	ThrowSyntaxError("Unexpected end of file");
	return string();
}

string source::GetCurPToken() const {
	// ne moze uzet trenutni ptoken ako je ungetano, ili je na pocetku
	if (curptoken.empty()) throw "Can't GetCurPToken";
	return curptoken;
}

code_pos source::GetCodePos() const {
	return curcodepos;
}

strpos source::GetPos() const {
	return tokenpos;
}

void source::SetPos(strpos p) {
	//_SetLastPosData();
	curptoken.clear();
	lasttokenpos = string::npos;
	lastcodepos.x = lastcodepos.y = -1;

	tokenpos = p;

	curcodepos.x = CharsInLine(src, tokenpos);
	curcodepos.y = CountChars(src, '\n', 0, tokenpos) + 1;
}

void source::_SetLastPosData() {
	lastcodepos = curcodepos;
	lasttokenpos = tokenpos;
	curptoken.clear();
}

string source::CollectExpression(char stopat) {
	char strstopat[] = {stopat, 0};
	string r;
	int z=0;
	while (GetNextPToken() != ";" && GetCurPToken() != "}" && (!stopat || GetCurPToken() != strstopat)) {
		z+=GetCurPToken() == "(";
		z-=GetCurPToken() == ")";
		if (z<0) break;
		r+=' ' + GetCurPToken();
	}
	if (z > 0)
		ThrowSyntaxError("Zagrade nebalansirane");
	if (GetCurPToken() == "}")
		ThrowSyntaxError("Expecting ;");
	r += " ;";
	return r.empty() ? string() : r.substr(1);
}

string source::CollectBlock() {
	string r;
	int v = 1;
	if (GetNextPToken() != "{")
		ThrowSyntaxError("Expecting {");
	r = "{";
	while (v) {
		v+=GetNextPToken() == "{";
		v-=GetCurPToken() == "}";
		r+=' '+GetCurPToken();
	}
	return r;
}

string source::CollectBlockOrExpression(char stopat) {
	if (GetNextPToken() == "{") {
		UnGetPToken();
		return CollectBlock();
	}
	UnGetPToken();
	return CollectExpression(stopat);
}

string source::CollectArrayMark() {
	if (GetNextPToken() != "[")
		ThrowSyntaxError("Expecting [");
	string r = "[";
	while (GetNextPToken() != "]")
		r += ' ' + GetCurPToken();
	r += " ]";
	return r;
}

const char *source::c_str() const {
	return src.c_str();
}

const string source::str() const {
	return src;
}

bool source::IsDefaultType(const string &sfc) {
	static const char *defaulttypes[] = {
		"void", "int", "char", "short", "unsigned",
		"signed", "long", "static", "extern",
		"register", "auto", "float", "double",
		NULL
	};

	for (const char **dt = defaulttypes; *dt; ++dt)
		if (*dt == sfc) return true;
	return false;
}

int source::PointerCount() {
	string ts = GetNextPToken();
	if (ts[0] != '*') {
		UnGetPToken();
		return 0;
	}
	// provjeri da li je stvarno pojnter
	for (strpos p = 0; p < ts.size(); ++p)
		if (ts[p] != '*') ThrowSyntaxError("Expecting: *");

	return PointerCount() + (int)ts.size();
}


//////////////////////
// code_pos class
//////////////////////
void code_pos::Dump(FILE *out) const {
	if (y <= 0 || x <= 0) {
		fprintf(out, "Illegal position!\n");
	} else {
		fprintf(out, "Line: %d, Col: %d\n", y, x);
	}
}

//////////////////////
// SyntaxError class
//////////////////////

SyntaxError::SyntaxError(const source& src, const string& err_msg) {
	error = err_msg;
	position = src.GetCodePos();
}
