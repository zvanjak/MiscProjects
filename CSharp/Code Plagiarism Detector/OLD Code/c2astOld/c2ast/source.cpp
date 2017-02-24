#include "stdafx.h"
#include "source.h"
#include "stringutils.h"
#include <ctype.h>

static bool islblchar(char c) {
	return isalnum(c) || c=='_';
}

source::source() {
	_init();
}

void source::_init() {
	tokenpos = 0;
	lasttokenpos = string::npos;
	curptoken.clear();
}

void source::Dump() const {
	puts(src.c_str());
}

void source::clear() {
	src.clear();
	_init();
}

bool source::empty() const {
	return src.empty();
}

void source::Load(const string &fname) {
	// Ucita fajl
	if (!LoadFileToString(fname, src))
		throw "Ne mogu ucitat fajl!";

	// Malo ga prepravi...

	// * Izbaci svaki \\\n 
	str_replace(src, "\\\n", "");

	// makne komentare
	RemoveComments();
	RemovePreprocessor();

	// init internalija
	_init();
}

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

void source::RemovePreprocessor() {
	strpos p, l;
	for (l=0;(p=src.find('#', l)) != string::npos;l=p) {
		if (!p || src[p-1] == '\n') {
			strpos e = src.find('\n', p);
			if (e != string::npos) {
				src.erase(p, e-p+1);
			} else {
				src.erase(p);
				break;
			}
		} else {
			++p;
		}
	}
}

const source & source::operator = (const string &s) {
	src = s;
	_init();
	return *this;
}

const string & source::operator += (const string &s) {
	return src+=s;
}

void source::UnGetPToken() {
	if (lasttokenpos == string::npos)
		throw "UnGetPToken() can be called only once";
	tokenpos = lasttokenpos;
	lasttokenpos = string::npos;
	curptoken.clear();
}

bool source::Processed() const {
	return tokenpos >= src.size();
}

string source::GetNextPToken() {
	static const char opchars[] = "/*-+:?%^!&|=~.><";	// znakovi od kojih se sastoje operatori

	if (tokenpos >= src.size()) goto kraj;

	while (isspace(src[tokenpos])) {
		++tokenpos;
		if (tokenpos >= src.size()) goto kraj;
	}

	lasttokenpos = tokenpos;
	curptoken.clear();

	// operator(i) ili labela ili zagrade i ';' i ',' ili string
	if (incharlist(src[tokenpos], opchars)) {
		do {
			curptoken += src[tokenpos++];
		} while (tokenpos < src.size() && (incharlist(src[tokenpos], opchars) || src[tokenpos] == '>'));
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
		curptoken += "'";
	} else if (src[tokenpos] == '"') {
		do {
			curptoken += src[tokenpos];
			++tokenpos;
		} while (tokenpos < src.size() && (src[tokenpos] != '"' || src[tokenpos-1] == '\\'));
		if (tokenpos >= src.size()) goto kraj;
		++tokenpos;
		curptoken += "\"";
	} else {
		throw string("Unknown char: ") + src[tokenpos];
	}

	while (tokenpos < src.size() && isspace(src[tokenpos])) ++tokenpos;

	return curptoken;

kraj:
	throw "Unexpected end of file";
}

string source::GetCurPToken() const {
	// ne može uzet trenutni ptoken ako je ungetano, ili je na poèetku
	if (curptoken.empty()) throw "Can't GetCurPToken";
	return curptoken;
}

strpos source::GetPos() const {
	return tokenpos;
}

void source::SetPos(strpos p) {
	tokenpos = p;
}

string source::CollectExpression() {
	string r;
	int z=0;
	while (GetNextPToken() != ";" && GetCurPToken() != "," && GetCurPToken() != "}") {
		z+=GetCurPToken() == "(";
		z-=GetCurPToken() == ")";
		if (z<0) break;
		r+=' ' + GetCurPToken();
	}
	if (z>0) {
		throw "Zagrade nebalansirane";
	}
	if (GetCurPToken() == ";") r+= " ;";
	return r.empty() ? string() : r.substr(1);
}

string source::CollectBlock() {
	string r;
	int v=1;
	if (GetNextPToken() != "{") throw "Syntax error: expecting {";
	r="{";
	while (v) {
		v+=GetNextPToken() == "{";
		v-=GetCurPToken() == "}";
		r+=' '+GetCurPToken();
	}
	return r;
}

string source::CollectBlockOrExpression() {
	if (GetNextPToken() == "{") {
		UnGetPToken();
		return CollectBlock();
	}
	UnGetPToken();
	return CollectExpression();
}

string source::CollectArrayMark() {
	if (GetNextPToken() != "[") throw "Expecting [";
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
		if (ts[p] != '*') throw "Expecting *";

	return PointerCount() + (int)ts.size();
}
