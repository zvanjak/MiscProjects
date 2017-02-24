#ifndef _AST_
#define _AST_

#include "stdafx.h"

#include "source.h"

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

class AST_node;

typedef vector<AST_node> AST_list;

class AST_node {
	public:
		AST_node_type type;
		AST_list children;
		vector<c_type> types;
		vector<c_decl> declarations;
		c_func_data function_data;

		source src;

		AST_node(AST_node_type type = ASTnt_undefined);

		void Clear();
		bool IsType(const string &sfc);

		void AddType(const c_type &ct);
		void AddDeclaration(const c_decl &cd);
		void AddNode(const AST_node &an);
		AST_node & AddNewNode(AST_node_type t = ASTnt_undefined);

		void Dump(int level) const;

		static string TypeToString(AST_node_type type);

	private:
		AST_node *parent;

	friend class AST;
};

class AST {
	public:
		AST_node root;

		AST();

		void Dump() const;

		const AST & operator = (source &src);


	private:
		static bool ProcessTypes(AST_node &parent, source &src);
		static void ProcessRootBlock(AST_node &root, source &src);
		static bool ProcessRootCode(AST_node &root, source &src);
		static void ProcessBlock(AST_node &parent, source &src);
		static bool ProcessDeclarations(AST_node &parent, source &src, bool arguments = false);
		static bool GetTypeString(AST_node &parent, source &src, string &typestring);
		static bool GetArrayString(source &src, string &arraystring);
};

#endif
