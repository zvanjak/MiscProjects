#ifndef _STRINGUTILS_
#define _STRINGUTILS_

#include "stdafx.h"

typedef string::size_type strpos;

bool LoadFileToString(const string &fname, string &str);
bool WriteStringToFile(const string &fname, const string &str);
void str_replace(string &inwhat, const string &what, const string &with);
string implode(const string &separator, const vector<string> &list);
bool incharlist(char c, const char *chars);
string htmlspecialchars(string s);
strpos CodeSearch(const string &code, const string &what, strpos offset);

#endif
