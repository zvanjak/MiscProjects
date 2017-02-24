#pragma once

#include <list>
#include <string>

using std::list;
using std::string;

namespace CodeAnalyzer
{
	class IAnalysisInputCreator
	{

	};

	class IFileListEnumerator
	{
	public:
		virtual	void	Enumerate(list<string> &listFiles) = 0;
	};

	class IFileAnalyzer
	{

	public:
		IFileAnalyzer() {

		}

		virtual ~IFileAnalyzer() {

		}
		virtual void Analyze(string FileName) =0;

	};

}
