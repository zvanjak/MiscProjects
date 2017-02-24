#pragma once

#include "CodeAnalyzerInterfaces.h"

#include <list>
#include <string>

using std::list;
using std::string;
using std::wstring;

using namespace CodeAnalyzer;

/*
	Objekt koji u skladu za zadanim kriterijima kreira listu fajlova za analizu
	- moguænosti zadavanja kriterija:
		- analizira sadržaj direktorija
		- analizira sadržaj direktorija i poddirektorija
		- moguænost match-inga imena (wildcards - npr. "Data*.cpp"
		- zadavanje ekstenzije

*/
class SimpleFileListEnumerator : public IFileListEnumerator
{
public:
	SimpleFileListEnumerator(void);
	~SimpleFileListEnumerator(void);

	void		SetDirectory(string inDirName);
	void		SetSearchSubDir(bool inOnOff);

	virtual	void	Enumerate(list<string> &listFiles);

	void		EnumerateRecursive(string Dir, list<string> &listFiles);

private:
	string		_DirName;
	bool			_SearchSubDir;
	int a;
};
