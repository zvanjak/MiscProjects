namespace CodeAnalyzer
{
	namespace PhysicalCodeLayout
	{
		class FileAnalysisResults
		{
		public:
			FileAnalysisResults()
			{
				_TotalLines = 0;
				_CommentLines = 0;
				_CodeLines = 0;
				_EmptyLines = 0;
			}
			int		_TotalLines;
			int		_CommentLines;
			int		_CodeLines;
			int		_EmptyLines;
		};
	}
}