#include "stdafx.h"
#include "stringutils.h"

#include <string.h>
#include <fstream>

bool LoadFileToString(const string &fname, string &str) {
	ifstream ifs(fname.c_str());
	if (!ifs.good())
		return false;
	str.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
	ifs.close();
	return true;
}

bool WriteStringToFile(const string &fname, const string &str) {
	ofstream ofs(fname.c_str());
	if (!ofs.good())
		return false;
	ofs << str;
	ofs.close();
	return true;
}

void str_replace(string &inwhat, const string &what, const string &with) {
	strpos pos = 0;
	while ((pos=inwhat.find(what, pos)) != string::npos) {
		inwhat.replace(pos, what.size(), with);
		pos+=with.size();
	}
}

string implode(const string &separator, const vector<string> &list) {
	string s;
	for (vector<string>::const_iterator i=list.begin(); i!=list.end(); ++i) {
		s+=*i;
		if (i!=list.end()-1) s+=separator;
	}
	return s;
}

bool incharlist(char c, const char *chars) {
	return !!strchr(chars, c);
}

string htmlspecialchars(string s) {
	str_replace(s, "&", "&amp;");
	str_replace(s, "\"", "&quot;");
	str_replace(s, "<", "&lt;");
	str_replace(s, ">", "&gt;");
	return s;
}

// srcanje po kodu sa preskakanjem stringova...
//TODO: ne izbjegava moguce komentare...
static strpos CodeSearchEx(const string &code, strpos offset, bool (*komp)(const string &, strpos, void*), void *arg=NULL) {
	strpos i;
	for (i=offset; i < code.size(); ++i) {
		if (code[i] == '"') {	// preskoci " "
			for (++i;i<code.size();++i)
				if (code[i] == '"' && code[i-1] != '\\') break;
		} else if (code[i] == '\'') {	// preskoci ' '
			for (++i;i<code.size();++i)
				if (code[i] == '\'' && code[i-1] != '\\') break;
		} else if (komp(code, i, arg)) {
			return i;
		}
	}
	return string::npos;
}

static bool _CodeSearch1(const string &code, strpos offset, void *arg) {
	const string &what = *(const string*)arg;
	strpos j, k;
	for (j=offset, k=0; k<what.size(); ++k, ++j)
		if (code[j] != what[k])
			return false;
	return true;
}

strpos CodeSearch(const string &code, const string &what, strpos offset) {
	return CodeSearchEx(code, offset, _CodeSearch1, (void*)&what);
}

int CountChars(const string &str, char c, strpos offset, strpos length) {
	int cnt = 0;
	for (strpos i = offset; length && i < str.size(); ++i, --length) {
		cnt += str[i] == c;
	}
	return cnt;
}

int CharsInLine(const string &str, strpos pos) {
	if (str.empty()) return 0;

	strpos p = str.rfind('\n', pos);
	if (p == string::npos) return (int)(pos + 1);
	return (int)(pos - p);
}

void PutSpaces(int n) {
	while (n--) printf(" ");
}

