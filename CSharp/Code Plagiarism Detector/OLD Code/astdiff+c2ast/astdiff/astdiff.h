#ifndef _ASTDIFF_
#define _ASTDIFF_

#include <ast.h>

class AST_node2 : public AST_anode {
	public:
		unsigned int ID;
		int TotalNKids;

		AST_ALLOCATOR(AST_node2);

		AST_node2() : AST_anode(ASTnt_undefined) {}
		AST_node2(const AST_ncore &an) : AST_anode(an) {}

		void Dump(int level = 0) const;

		unsigned int SetIDs(unsigned int t);
		int SetTotalNKids();
		int GetTotalNKids();
};

#endif
