#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

namespace CodeAnalyzer
{
	namespace Analyzers
	{
		class FilePhysicalLayoutAnalyzer
		{
		public:
			static void	AnalyzeFile(CodeModel::File *refFile)
			{
				ifstream		inputFile;

				inputFile.open(refFile->_FullName.c_str());
				if( inputFile.is_open() )
				{
					char		chBuff[500];
					while(inputFile.getline(chBuff, 500))
					{
						refFile->_AnalysisResults._TotalLines++;
						if( strlen(chBuff) == 0 )
							refFile->_AnalysisResults._EmptyLines++;
					}
				}

				refFile->_AnalysisResults._CodeLines = 0;
				refFile->_AnalysisResults._CommentLines = 0;
			}
		};

		class ModelPhysicalLayoutAnalyzer
		{
		public:
			void Analyze(CodeModel::PhysicalCodeModel &refCodeModel)
			{
				cout << "ANALYSIS RESULTS" << endl;

				list<CodeModel::Project *>::iterator it = refCodeModel._listProjects.begin();
				for(; it != refCodeModel._listProjects.end(); it++ )
				{
					// i sada treba proæi kroz sve fajlove u projektu i obaviti analizu
					list<CodeModel::File *>::iterator itFile = (*it)->_listFiles.begin();
					for(; itFile != (*it)->_listFiles.end(); itFile++)
					{
						FilePhysicalLayoutAnalyzer::AnalyzeFile(*itFile);

						cout << (*itFile)->_Name << endl;
						cout << "     Total lines   = " << (*itFile)->_AnalysisResults._TotalLines << endl;
						cout << "     Empty lines   = " << (*itFile)->_AnalysisResults._EmptyLines << endl;
						cout << "     Comment lines = " << (*itFile)->_AnalysisResults._CommentLines << endl;
						cout << "     Code lines    = " << (*itFile)->_AnalysisResults._CodeLines<< endl;
					}

					cout << "Project " << (*it)->_ProjectName << " total lines: " << endl;
					cout << (*it)->GetProjectTotalLines() << endl;
				}

			}
		};
	}
}