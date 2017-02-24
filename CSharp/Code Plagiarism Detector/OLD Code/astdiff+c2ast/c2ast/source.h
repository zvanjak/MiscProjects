#ifndef _SOURCE_
#define _SOURCE_

#include "stdafx.h"
#include "stringutils.h"

class code_pos {
	public:
		int x;
		int y;

		void Dump(FILE *out = stdout) const;
};

class source {
	public:
		source();
		source(const char *s);
		source(const string &s);

		void clear();
		void Load(const string &fname);
		void Dump() const;
		void DumpCodePos(FILE *out = stdout) const;
		bool empty() const;
		strpos size() const;

		void FilterCode();
		void RemoveComments();
		void RemovePreprocessor();

		void ThrowSyntaxError(string err_msg) const;

		string GetNextPToken();
		string GetCurPToken() const;
		void UnGetPToken();
		string TryGetNumber() const;
		string TryGetOperator() const;
		bool Processed() const;
		strpos GetPos() const;
		void SetPos(strpos p);
		code_pos GetCodePos() const;
		bool SkipSpaces();

		string CollectExpression(char stopat=0);	// skuplja do neceg od: ;}) (ili do 'stopat' ako je zatrazeno)
		string CollectBlock();		// skuplja od { do }
		string CollectBlockOrExpression(char stopat=0);	// kao block ili kao expression, ovisno o tome sto slijedi
		string CollectArrayMark();	// skuplja od [ do ]

		int PointerCount();	// uzme slijedeci ptoken i gleda da li je pojnter i prebroji njegov stupanj
		static bool islblchar(char c);	// da li znak moze biti znak od labele

		const char *c_str() const;
		const string str() const;

		static bool IsDefaultType(const string &sfc);

		const source& operator = (const string &s);
		const source& operator = (const char *s);
		const string& operator += (const string &s);

	private:
		string src;
		string curptoken;

		strpos tokenpos;
		strpos lasttokenpos;

		code_pos curcodepos;
		code_pos lastcodepos;

		void _init();
		void _SetLastPosData();
};

class SyntaxError {
	public:
		string error;
		code_pos position;
		
		SyntaxError(const source& src, const string &err_msg);
};

#endif
