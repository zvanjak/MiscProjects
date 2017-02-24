#include "StdAfx.h"
#include "FileListEnumerator.h"

SimpleFileListEnumerator::SimpleFileListEnumerator(void)
{
	_DirName = "C:\\";
	_SearchSubDir = false;
}

SimpleFileListEnumerator::~SimpleFileListEnumerator(void)
{
}

void		SimpleFileListEnumerator::SetDirectory(string inDirName)
{
	_DirName = inDirName;
}
void	SimpleFileListEnumerator::SetSearchSubDir(bool inOnOff)
{
	_SearchSubDir = inOnOff;
}

void	SimpleFileListEnumerator::Enumerate(list<string> &listFiles)
{
	HANDLE						hFind;
	WIN32_FIND_DATA		fd;

	string		strFileName, strFilePath;
	string		strSearch = _DirName + "\\*.*";

	CA2W		str(strSearch.c_str());

	hFind = ::FindFirstFileW(str, &fd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				// radi se o direktoriju
				CW2A		temp(fd.cFileName);
				strFileName = temp;
				strFilePath = _DirName + "\\" + strFileName;

				if( strFileName != "." && strFileName != ".." )
					EnumerateRecursive(strFilePath, listFiles);
			}
			else 
			{ 
				CW2A		temp(fd.cFileName);
				strFileName = temp;
				strFilePath = _DirName + "\\" + strFileName;

				listFiles.push_back(strFilePath);
			}
		}while(::FindNextFile(hFind, &fd));
	}
}

void		SimpleFileListEnumerator::EnumerateRecursive(string CurrDir, list<string> &listFiles)
{
	HANDLE						hFind;
	WIN32_FIND_DATA		fd;

	string		strFileName, strFilePath;
	string		strSearch = CurrDir + "\\*.*";

	CA2W		str(strSearch.c_str());

	hFind = ::FindFirstFileW(str, &fd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				// radi se o direktoriju
				CW2A		temp(fd.cFileName);
				strFileName = temp;
				strFilePath = CurrDir + "\\" + strFileName ;

				if( strFileName != "." && strFileName != ".." )
					EnumerateRecursive(strFileName, listFiles);
			}
			else 
			{ 
				CW2A		temp(fd.cFileName);
				strFileName = temp;
				strFilePath = CurrDir + "\\" + strFileName;

				listFiles.push_back(strFilePath);
			}
		}while(::FindNextFile(hFind, &fd));
	}
}
