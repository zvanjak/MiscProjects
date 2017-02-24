#pragma once 

#include <string>
#include <list>

#include "CodeAnalyzerInterfaces.h"
#include "CodeModel.h"

using std::string;
using std::list;

namespace CodeAnalyzer
{
	class InputFileDescription
	{
	public:
		string		_Name;
		string		_FullName;
	};

	class InputProjectDescription
	{
	public:
		string	_ProjectName;
		string	_ProjectDir;
		bool		_bIncludeSubdirectories;

		CodeModel::ProjectTypes::ProjectType	_ProjectType;

		list<InputFileDescription> _listExplicitFiles;
	};

	/*
	- ovo je objekt preko kojega se zadaju kriteriji
	- nad njime direktno operira forma (dijalog) iz GUI su�elja
	- ako bi htjeli posve op�enito, mora mo�i reprezentirati odabir:
		- konkretnog skupa datoteka (direktno kroz OpenFileDialog)
		- jednog (ili vi�e) direktorija (zajedno sa ili bez poddirektorija)
	- name�e se koncept Projekta kao koncepta koji definira skup povezanih datoteka
		- pa ulazni skup datoteka definiramo preko skupa projekata koji su definirani preko direktorija u kojima se nalaze
	- mogu� i koncept Solution-a koji sadr�i vi�e projekata, svaki u svom direktoriju

	*/
	class AnalysisInput
	{
	public:

		void		AddProject(string inProjectName, string inDirPath, bool inIncludeSubdir, CodeModel::ProjectTypes::ProjectType inProjectType)
		{
			InputProjectDescription	newProj;

			newProj._ProjectName = inProjectName;
			newProj._ProjectDir = inDirPath;
			newProj._bIncludeSubdirectories = inIncludeSubdir;

			newProj._ProjectType = inProjectType;

			_listDefinedProjects.push_back(newProj);
		}

		// u listu fajlova za projekt eksplicitno dodaje dani fajl
		void	AddExplicitProjectFile(string inProjectName, string inFilePath)
		{

		}

	public:
		list<InputProjectDescription>		_listDefinedProjects;
	};
}