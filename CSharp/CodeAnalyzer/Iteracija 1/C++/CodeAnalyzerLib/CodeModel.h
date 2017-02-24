#pragma once

#include <string>
#include <vector>
#include <list>

#include "AnalysisResults.h"

using std::string;
using std::vector;
using std::list;

namespace CodeAnalyzer
{
	namespace CodeModel
	{
		// forward declarations
		class Project;

		class File
		{
		public:
			File(string inName, string inFullName, Project *inRefParentProject)
				: _Name(inName), _FullName(inFullName), _refParentProject(inRefParentProject)
			{	}

			string	_Name;
			string	_FullName;

			Project *_refParentProject;

			PhysicalCodeLayout::FileAnalysisResults		_AnalysisResults;
		};

		class ProjectTypes
		{
		public:
			enum ProjectType { CPP, CPPCLI, CSharp, VBNET, Java } ;

			static vector<string>		GetProjectFileExtensions(ProjectType inType)
			{
				vector<string>		retList;
				switch(inType)
				{
					case CPP : retList.push_back("h"); retList.push_back("cpp"); break;
					case CPPCLI : retList.push_back("h"); retList.push_back("cpp"); break;
					case CSharp : retList.push_back("cs"); break;
					case VBNET : retList.push_back("vb"); break;
					case Java : retList.push_back("java"); break;
				}

				return retList;
			}
		};

		class Project
		{
		public:
			int		GetProjectTotalLines()
			{
				int		TotalLines = 0;
				for( list<File *>::iterator it = _listFiles.begin(); it != _listFiles.end(); it++ )
				{
					TotalLines += (*it)->_AnalysisResults._TotalLines;
				}
				return TotalLines;
			}

		public:
			string	_ProjectName;
			string	_ProjectDir;

			ProjectTypes::ProjectType	_ProjectType;

			list<File *> _listFiles;
		};

		class PhysicalCodeModel
		{
		public:
			void AddNewProject(Project *inProject)
			{
				_listProjects.push_back(inProject);
			}

		public:
			list<Project *>		_listProjects;
		};
	}
}