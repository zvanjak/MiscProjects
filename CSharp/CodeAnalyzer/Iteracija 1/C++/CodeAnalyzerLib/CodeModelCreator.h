#include "StdAfx.h"

#include <string>
#include <list>
#include <algorithm>

#include "AnalysisInput.h"
#include "CodeModel.h"

using std::string;
using std::list;
using std::find;

namespace CodeAnalyzer
{
	class CodeModelCreator
	{
	public:
		void	CreatePhysicalCodeModel(AnalysisInput &inCriteria, CodeModel::PhysicalCodeModel &outModel)
		{
			// proæi kroz sve projekte u inCriteria
			list<InputProjectDescription>::const_iterator it = inCriteria._listDefinedProjects.begin();
			for(; it != inCriteria._listDefinedProjects.end(); it++)
			{
				const InputProjectDescription &projDef = *it;
				std::cout << projDef._ProjectName << std::endl;

				CodeModel::Project		*newProject = new CodeModel::Project();
				newProject->_ProjectName = projDef._ProjectName;
				newProject->_ProjectDir = projDef._ProjectDir;
				newProject->_ProjectType = projDef._ProjectType;

				outModel.AddNewProject(newProject);
				if( projDef._bIncludeSubdirectories == true )
				{
					EnumerateProjectFilesRecursively(projDef._ProjectDir, newProject);
				}
				else
				{
					EnumerateProjectFiles(projDef._ProjectDir, newProject);
				}
			}
		}

	private:
		void	EnumerateProjectFiles(string DirName, CodeModel::Project *refProject)
		{
			HANDLE						hFind;
			WIN32_FIND_DATA		fd;

			vector<string>		listExtensions = CodeModel::ProjectTypes::GetProjectFileExtensions(refProject->_ProjectType);

			for( vector<string>::iterator it=listExtensions.begin(); it != listExtensions.end(); it++ )
			{
				string		strSearch = DirName + "\\*." + (*it);
				CA2W			str(strSearch.c_str());

				hFind = ::FindFirstFileW(str, &fd);
				if(hFind != INVALID_HANDLE_VALUE) 
				{
					do {
						// ako se radi o direktoriju - ništa
						if( ! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
						{
							string strFileName = CW2A(fd.cFileName);
							string strFilePath = DirName + "\\" + strFileName;

							CodeModel::File		*newFile = new CodeModel::File(strFileName, strFilePath, refProject);
							refProject->_listFiles.push_back(newFile);

	//						std::cout << strFilePath << std::endl;
						}
					}while(::FindNextFile(hFind, &fd));
				}
			}
		}
		void	EnumerateProjectFilesRecursively(string DirName, CodeModel::Project *refProject)
		{
			HANDLE						hFind;
			WIN32_FIND_DATA		fd;

			vector<string>		listExtensions = CodeModel::ProjectTypes::GetProjectFileExtensions(refProject->_ProjectType);

			string		strFileName, strFilePath;
			string		strSearch = DirName + "\\*.*";

			CA2W		str(strSearch.c_str());

			hFind = ::FindFirstFileW(str, &fd);
			if(hFind != INVALID_HANDLE_VALUE) 
			{
				do {
					if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
					{
						// radi se o direktoriju
						strFileName = CW2A(fd.cFileName);
						strFilePath = DirName + "\\" + strFileName;

						if( strFileName != "." && strFileName != ".." )
							EnumerateProjectFilesRecursively(strFilePath, refProject);
					}
					else
					{
						// radi se o fajlu
						strFileName = CW2A(fd.cFileName);
						strFilePath = DirName + "\\" + strFileName;

						// provjeriti da li zadovoljava zadanu ekstenziju (ovisan o projektu)
						static const string::size_type npos = -1;

						string::size_type	posExt = strFileName.rfind('.');
						if( posExt != npos )
						{
							string strFileExt = strFileName.substr(posExt + 1, strFileName.length() - posExt);

							if( find(listExtensions.begin(), listExtensions.end(), strFileExt) != listExtensions.end() )
							{
								CodeModel::File		*newFile = new CodeModel::File(strFileName, strFilePath, refProject);
								refProject->_listFiles.push_back(newFile);

//							std::cout << strFilePath << std::endl;
							}
						}
					}
				}while(::FindNextFile(hFind, &fd));
			}
		}
	};
}