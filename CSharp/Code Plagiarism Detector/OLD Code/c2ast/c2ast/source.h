#ifndef _SOURCE_
#define _SOURCE_

#include "stdafx.h"
#include "stringutils.h"

class source {
	public:
		source();

		void clear();
		void Load(const string &fname);
		void Dump() const;
		bool empty() const;

		void RemoveComments();
		void RemovePreprocessor();

		string GetNextPToken();
		string GetCurPToken() const;
		void UnGetPToken();
		bool Processed() const;
		strpos GetPos() const;
		void SetPos(strpos p);

		string CollectExpression();
		string CollectBlock();
		string CollectBlockOrExpression();
		string CollectArrayMark();

		int PointerCount();	// uzme slijedeæi ptoken i gleda da li je pojnter i prebroji njegov stupanj

		const char *c_str() const;
		const string str() const;

		static bool IsDefaultType(const string &sfc);

		const source &operator = (const string &s);
		const string & operator += (const string &s);

	private:
		string src;
		string curptoken;

		strpos tokenpos;
		strpos lasttokenpos;

		void _init();
};

#endif
