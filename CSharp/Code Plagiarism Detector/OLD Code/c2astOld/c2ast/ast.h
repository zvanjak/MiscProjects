#ifndef _AST_
#define _AST_

#include "stdafx.h"

#include "source.h"

typedef enum {
	AST_block = 0,
	AST_function,
	AST_function_code,
	AST_if,
	AST_if_true,
	AST_if_false,
	AST_for,
	AST_while,
	AST_do,
	AST_root
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

		AST_node(AST_node *parent = NULL);

		void Clear();
		bool IsType(const string &sfc);

		void AddType(const c_type &ct);
		void AddDeclaration(const c_decl &cd);
		void AddBlock(const AST_node &an);

		void Dump(int level) const;

		static string TypeToString(AST_node_type type);

	private:
		AST_node *parent;

	friend class AST;
};

class AST {
	public:
		AST();

		void Dump() const;

		const AST & operator = (source &src);

		AST_node root;

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
