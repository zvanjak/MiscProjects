#include "stdafx.h"
#include "ast.h"
#include "stringutils.h"

typedef map<string, string> args;

inline string __Tag(const string &name, const args &values, const string &inner, bool innerxml) {
	string r = '<' + name;

	for (args::const_iterator mi = values.begin(); mi != values.end(); ++mi)
		r += ' ' + mi->first + "=\"" + htmlspecialchars(mi->second) + '"';

	if (inner.empty()) {
		r += " />\n";
	} else {
		r += ">";
		r += innerxml ? inner : htmlspecialchars(inner);
		r += "</" + name + ">\n";
	}

	return r;
}

static string _Tag(const string &name, const args &values = args(), const string &inner = string()) {
	return __Tag(name, values, inner, false);
}

static string _TagParent(const string &name, const args &values, const string &inner) {
	return __Tag(name, values, inner, true);
}

static string _TagParent(const string &name, const string &inner) {
	return __Tag(name, args(), inner, true);
}

static string _Tag(const c_type &ct) {
	args a;
	a["name"] = ct.name;
	return _Tag("type", a, ct.type);
}

static string _Tag(const c_decl &cd) {
	args a;
	a["name"] = cd.name;
	a["type"] = cd.type;
	return _Tag("decl", a, cd.value.str());
}

static string _TagParent(const c_func_data &cfd, const string &xml) {
	args a;
	a["name"] = cfd.name;
	a["type"] = cfd.type;
	return _TagParent("function", a, xml);
}

static string _TagParentIf(const string &cond, const string &xml) {
	args a;
	a["condition"] = cond;
	return _TagParent("if", a, xml);
}

static string _TagParentWhile(const string &cond, const string &xml) {
	args a;
	a["condition"] = cond;
	return _TagParent("while", a, xml);
}

static string _TagParentDo(const string &cond, const string &xml) {
	args a;
	a["condition"] = cond;
	return _TagParent("do", a, xml);
}

static string _TagParentFor(const string &cond, const string &xml) {
	args a;
	a["condition"] = cond;
	return _TagParent("for", a, xml);
}

static string _ProcTypes(const AST_node &nod) {
	if (nod.types.empty()) return string();

	string r;
	for (vector<c_type>::const_iterator i=nod.types.begin(); i!=nod.types.end(); ++i)
		r+=_Tag(*i);

	return _TagParent("types", r);
}

static string _ProcDecls(const AST_node &nod) {
	if (nod.declarations.empty()) return string();

	string r;
	for (vector<c_decl>::const_iterator i=nod.declarations.begin(); i!=nod.declarations.end(); ++i)
		r+=_Tag(*i);

	return _TagParent("declarations", r);
}

#define CHILDRENPROC()	for (AST_list::const_iterator i = nod.children.begin(); i!=nod.children.end(); ++i) r+=_ast2xml(*i);


static string _ast2xml(const AST_node &nod) {
	string r;

	// default za sve:
	r  = _ProcTypes(nod);
	r += _ProcDecls(nod);

	switch (nod.type) {
		case ASTnt_root:
			CHILDRENPROC();
			r = _TagParent("root", r);
			break;

		case ASTnt_function:
			CHILDRENPROC();
			r = _TagParent(nod.function_data, r);
			break;

		case ASTnt_function_code:
			CHILDRENPROC();
			r = _TagParent("code", r);
			break;

		case ASTnt_block:	// ignorira types i decls
			r = _TagParent("block", nod.src.str());
			break;

		case ASTnt_if:
			CHILDRENPROC();
			r = _TagParentIf(nod.src.str(), r);
			break;

		case ASTnt_if_true:
			CHILDRENPROC();
			r = _TagParent("true", r);
			break;

		case ASTnt_if_false:
			CHILDRENPROC();
			r = _TagParent("false", r);
			break;

		case ASTnt_while:
			CHILDRENPROC();
			r = _TagParentWhile(nod.src.str(), r);
			break;

		case ASTnt_do:
			CHILDRENPROC();
			r = _TagParentDo(nod.src.str(), r);
			break;

		case ASTnt_for:
			CHILDRENPROC();
			r = _TagParentFor(nod.src.str(), r);
			break;

		default:
			throw "Unknown node type: " + AST_node::TypeToString(nod.type);
	}

	return r;
}

string ast2xml(const AST &ast) {
	return _ast2xml(ast.root);
}