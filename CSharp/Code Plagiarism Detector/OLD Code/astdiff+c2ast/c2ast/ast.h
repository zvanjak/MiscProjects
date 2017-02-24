#ifndef _AST_
#define _AST_

#include "stdafx.h"

#include "source.h"
#include "ast_alloc.h"

typedef enum {
	ASTnt_block = 0,
	ASTnt_function,
	ASTnt_function_code,
	ASTnt_if,
	ASTnt_if_true,
	ASTnt_if_false,
	ASTnt_for,
	ASTnt_while,
	ASTnt_do,
	ASTnt_root,
	ASTnt_switch,
	ASTnt_label,
	ASTnt_undefined
} AST_node_type;

struct c_type {
	string name;
	string type;
};

struct c_decl {
	string name;
	string type;
	source value;
};

struct c_func_data {
	string name;
	string type;
};

typedef vector<c_type> c_type_list;
typedef vector<c_decl> c_decl_list;

#define FOREACHASTCTYPE(node, itm)	for (c_type_list::iterator itm = \
						(node).types.begin(); \
						itm != (node).types.end(); \
						++itm)
#define FOREACHASTCCTYPE(node, itm)	for (c_type_list::const_iterator itm = \
						(node).types.begin(); \
						itm != (node).types.end(); \
						++itm)
#define FOREACHASTCDECL(node, itm)	for (c_decl_list::iterator irm = \
						(node).declarations.begin(); \
						itm != (node).declarations.end(); \
						++itm)
#define FOREACHASTCCDECL(node, itm)	for (c_decl_list::const_iterator itm = \
						(node).declarations.begin(); \
						itm != (node).declarations.end(); \
						++itm)

class AST_ncore {
	public:
		AST_node_type type;				///< tip cvora
		c_type_list types;				///< tipovi deklarirani u cvoru
		c_decl_list declarations;	///< deklaracije u cvoru
		c_func_data function_data;		///< podaci od funkcije ako je cvor tipa fja (name se koristi i za labelu!)

		source src;						///< sors u cvoru (blok); kod if, while, ... je to uvjet

		AST_ncore *parent;

		AST_ncore(AST_node_type type = ASTnt_undefined, AST_ncore *parent = NULL);

		void Clear();
		bool IsType(const string &sfc);

		void AddType(const c_type &ct);
		void AddDeclaration(const c_decl &cd);

		void Dump(int level = 0) const;
		string GetNodePath() const;
		void ThrowError(const string &errstr) const;

		static string TypeToString(AST_node_type type);

	friend class AST;
};

class AST_anode : public AST_ncore {
	public:
		AST_anode() {}
		AST_anode(const AST_ncore &nc) : AST_ncore(nc) {}
		AST_anode(AST_node_type t) : AST_ncore(t) {}
		virtual ~AST_anode() {}

		virtual void Dump(int level=0) const;

		void Clear();

		AST_anode& AddNode(AST_node_type t = ASTnt_undefined);

		// Ove apstraktne funkcije ispunjava AST_alloc
		virtual void ClearChildren() = 0;
		virtual AST_anode& AddNode(const AST_ncore &an) = 0;
		virtual unsigned int GetNKids() const = 0;
		virtual AST_anode& operator[] (unsigned int id) = 0;
		virtual const AST_anode& operator[] (unsigned int id) const = 0;
//		virtual bool RemoveNode(const AST_ncore &rn);
};

class AST_snode : public AST_anode {
	public:
		AST_ALLOCATOR(AST_snode);

		AST_snode() : AST_anode(ASTnt_undefined) {}
		AST_snode(const AST_ncore &an) : AST_anode(an) {}
};

class AST {
	public:
		AST_snode root;

		AST();

		void Dump() const;

		const AST & operator = (source &src);

		static void Dump(const AST_snode &root);
		static void FillCustomAST(AST_anode &root, source &src);

	private:
		static bool ProcessTypes(AST_anode &parent, source &src);
		static void ProcessRootBlock(AST_anode &root, source &src);
		static bool ProcessRootCode(AST_anode &root, source &src);
		static void ProcessBlock(AST_anode &parent, source &src);
		static void ProcessLabel(AST_anode &parent, source &src);
		static void ProcessSwitch(AST_anode &parent, source &src);
		static bool ProcessDeclarations(AST_ncore &parent, source &src, bool arguments = false, bool force = false);
		static bool GetTypeString(AST_ncore &parent, source &src, string &typestring);
		static bool GetArrayString(source &src, string &arraystring);
		static bool FindFunction(const AST_anode &root, const string &name, unsigned int *pos);
};

#endif
