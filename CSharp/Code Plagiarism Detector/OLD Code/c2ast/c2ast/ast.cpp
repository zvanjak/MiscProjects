#include "stdafx.h"
#include "ast.h"

AST::AST() {
	root.type = ASTnt_root;
}

void AST::Dump() const {
	root.Dump(0);
}

/* procesiranje typedef-ova */
bool AST::ProcessTypes(AST_node &parent, source &src) {
	bool ok = false;

	while (src.GetNextPToken() == "typedef") {
		c_type ct;

		if (!GetTypeString(parent, src, ct.type))
			goto cterr;

		if (int n = src.PointerCount()) {
			while (n--) ct.type += "*";
		}

		ct.name = src.GetNextPToken();
		if (ct.name == ";") goto cterr;

		while (src.GetNextPToken() == "[") {
			string addt;
			src.UnGetPToken();
			GetArrayString(src, addt);
			ct.type+=addt;
		}
		
		if (src.GetCurPToken() != ";") goto cterr;

		parent.AddType(ct);

		ok = true;
	}

	src.UnGetPToken();

	return ok;

cterr:
	throw "Syntax error near typedef";
}

bool AST::GetArrayString(source &src, string &arraystring) {
	bool ima = false;
	arraystring.clear();
	while (src.GetNextPToken() == "[") {
		ima = true;
		src.UnGetPToken();
		arraystring += src.CollectArrayMark();
	}
	src.UnGetPToken();
	return ima;
}

bool AST::GetTypeString(AST_node &parent, source &src, string &typestring) {
	string pt = src.GetNextPToken();

	if (pt != "struct" && pt != "enum" && pt != "union" && !parent.IsType(pt)) {
		src.UnGetPToken();
		return false;
	}

	if (pt == "struct" || pt == "enum" || pt == "union") {
		c_type ct;
		c_decl cd;

		ct.name = src.GetNextPToken();

		if (ct.name == "{" || !parent.IsType(pt + '$' + ct.name)) {
			// nije deklaracija predefinirane strukture, pa dodaje tip
			if (ct.name == "{") src.UnGetPToken();
			ct.type = src.CollectBlock();
			if (ct.name != "{") {
				ct.name = pt + '$' + ct.name;
				parent.AddType(ct);
			}
			typestring = ct.type;
		} else {
			typestring = pt + '$' + ct.name;
		}
	} else {
		typestring = src.GetCurPToken();
		while (parent.IsType(src.GetNextPToken())) {
			typestring += ' ' + src.GetCurPToken();
		}
		src.UnGetPToken();
	}

	return true;
}

bool AST::ProcessDeclarations(AST_node &parent, source &src, bool single) {
	bool ima = false;

	do {
		strpos p = src.GetPos();
		string type, tarr;

		c_decl decl;

		if (!GetTypeString(parent, src, type))
			return ima;

		do {
			decl.type = type;
			if (int n = src.PointerCount()) {
				while (n--) decl.type += '*';
			}

			decl.name = src.GetNextPToken();

			if (decl.name == ";") break;	// bezimena varijabla - pali za struct i enum

			GetArrayString(src, tarr);
			decl.type+=tarr;

			if (src.GetNextPToken() == "=") {
				decl.value = src.CollectBlockOrExpression();
				if (src.GetCurPToken() == "}") src.GetNextPToken();
			} else {
				decl.value.clear();
			}

			// Provjera da li je možda fja?
			if (src.GetCurPToken() == "(") {
				src.SetPos(p);
				return ima;
			}

			ima = true;
			parent.AddDeclaration(decl);

		} while (!single && src.GetCurPToken() == ",");
	} while (!single);

	src.UnGetPToken();

	return ima;
}

// ako je prvi ptoken == "{", onda ide do "}", inaèe ide samo do ";"
void AST::ProcessBlock(AST_node &parent, source &src) {
	// da li pocinje sa { ?
	bool multiline = src.GetNextPToken() == "{";
	if (!multiline) src.UnGetPToken();

	// prvo pokupi tajpdefe i varijable
	if (multiline)
		while (ProcessTypes(parent, src) || ProcessDeclarations(parent, src));

	// A zatim pokupi kôd
	// (Skuplja kôd ptoken po ptoken dok ne naleti na nekaj posebno...)

	string pt;
	source komad;
	bool wasspecial;

	do {
		AST_node nod;
		nod.parent = &parent;

		pt = src.GetNextPToken();
		wasspecial = true;

		if (pt == "}") {
			break;
		} else if (pt == "{") {
			src.UnGetPToken();
			nod.type = ASTnt_function_code;
			ProcessBlock(nod, src);
		} else if (pt == "if" || pt == "while") {
			if (src.GetNextPToken() != "(") throw "Syntax error in " + pt + ": missing (";
			nod.src = src.CollectExpression();
			if (src.GetCurPToken() != ")") throw "Syntax error in " + pt + ": missing )";
			
			if (pt == "if") {
				nod.type = ASTnt_if;

				AST_node &ifnod = nod.AddNewNode(ASTnt_if_true);
				
				ProcessBlock(ifnod, src);

				if (src.GetNextPToken() == "else") {
					AST_node &elsenode = nod.AddNewNode(ASTnt_if_false);
					ProcessBlock(elsenode, src);
				} else {
					src.UnGetPToken();
				}
			} else {
				nod.type = ASTnt_while;
				ProcessBlock(nod, src);
			}
		} else if (pt == "for") {
			source forstuff;
			if (src.GetNextPToken() != "(") throw "Syntax error in for: missing (";
			forstuff = src.CollectExpression();
			if (src.GetCurPToken() != ";") throw "Missing second part of for";
			forstuff += ' ' + src.CollectExpression();
			if (src.GetCurPToken() != ";") throw "Missing third part of for";
			forstuff += ' ' + src.CollectExpression();
			if (src.GetCurPToken() != ")") throw "Syntax error in for: missing )";

			nod.type = ASTnt_for;
			nod.src = forstuff;
			ProcessBlock(nod, src);
		} else if (pt == "do") {
			nod.type = ASTnt_do;
			ProcessBlock(nod, src);
			if (src.GetNextPToken() != "while") throw "Invalid use of \"do\"";
			if (src.GetNextPToken() != "(") throw "Syntax error in do: missing (";
			nod.src = src.CollectExpression();
			if (src.GetCurPToken() != ")") throw "Syntax error in do: missing )";
			if (src.GetNextPToken() != ";") throw "Syntax error after do: missing ;";
		} else if (pt == "switch") {
			//TODO: switch
			throw "switch blok nepodrzan";
		} else if (pt == "typedef") {
			src.UnGetPToken();
			ProcessTypes(parent, src);
			continue;	// preskoèi dodavanje
		} else {
			wasspecial = false;
		}

		if (wasspecial) {
			if (!komad.empty()) {
				AST_node &bnod = parent.AddNewNode(ASTnt_block);
				bnod.src = komad;
				komad.clear();
			}
			parent.AddNode(nod);

			if (!multiline) break;
		} else {
			if (!komad.empty()) komad += " ";
			komad += pt;
		}
	} while (multiline || pt != ";");

	if (!komad.empty()) {
		AST_node &bnod = parent.AddNewNode(ASTnt_block);
		bnod.src = komad;
	}
}

/* globalne varijable, funkcije */
bool AST::ProcessRootCode(AST_node &root, source &src) {

	if (ProcessTypes(root, src)) return true;

	if (ProcessDeclarations(root, src)) return true;

	strpos p;
	AST_node &fja = root.AddNewNode(ASTnt_function);
	string args_s, t;

	p = src.GetPos();	// da se može vratiti ako nekaj ne štima

	/* princip skupljanja fje:
		* pokupi tip
		* pokupi ime
		* provjeri (
		* sakupljanje argumenata
		* naði {
	*/

	// skupljanje tipa
	if (!GetTypeString(root, src, fja.function_data.type))
		return false;

	// skupljanje imena
	fja.function_data.name = src.GetNextPToken();

	// provjera (
	if (src.GetNextPToken() != "(") {	// nema ( iza imena fje, dakle, nije fja
		src.SetPos(p);
		return false;
	}

	// sakupljanje argumenata
	do {
		ProcessDeclarations(fja, src, true);
	} while (src.GetNextPToken() == ",");
	if (src.GetCurPToken() != ")") throw "Syntax error in function's arguments";

	// traženje {
	if (src.GetNextPToken() != "{") {
		if (src.GetCurPToken() == ";") throw "Nepodrzane predeklaracije funkcija!";
		throw "Syntax error in function declaration!";
	}


	////////// Proces fje

	src.UnGetPToken();	// vrati {

	AST_node &fcode = fja.AddNewNode(ASTnt_function_code);
	ProcessBlock(fcode, src);

	return true;
}

/* procesiranje root dijela koda */
void AST::ProcessRootBlock(AST_node &root, source &src) {
	while (!src.Processed()) {
		if (!ProcessRootCode(root, src))
			throw "Syntax error in root code";
	}
}

const AST & AST::operator = (source &src) {

	root.Clear();

	ProcessRootBlock(root, src);

	return *this;
}


/********************
 *  AST_node        *
 ********************/
AST_node::AST_node(AST_node_type _type) {
	parent = NULL;
	type = _type;
}

void AST_node::Clear() {
	children.clear();
	types.clear();
	declarations.clear();
}

bool AST_node::IsType(const string &sfc) {
	if (source::IsDefaultType(sfc)) return true;

	for (vector<c_type>::const_iterator i=types.begin(); i!=types.end(); ++i) {
		if (i->name == sfc) return true;
	}

	if (parent) return parent->IsType(sfc);
	return false;
}

void AST_node::AddType(const c_type &ct) {
	types.push_back(ct);
}

void AST_node::AddDeclaration(const c_decl &cd) {
	declarations.push_back(cd);
}

AST_node & AST_node::AddNewNode(AST_node_type t) {
	AST_node nn(t);
	nn.parent = this;
	children.push_back(nn);
	return *(children.end()-1);
}

void AST_node::AddNode(const AST_node &an) {
	children.push_back(an);
	(children.end()-1)->parent = this;
}

string AST_node::TypeToString(AST_node_type type) {
	switch (type) {
		case ASTnt_block:		return "block";
		case ASTnt_function:	return "function";
		case ASTnt_function_code: return "function code";
		case ASTnt_if:			return "if";
		case ASTnt_if_true:		return "if -> true";
		case ASTnt_if_false:	return "if -> false";
		case ASTnt_for:			return "for";
		case ASTnt_while:		return "while";
		case ASTnt_do:			return "do";
		case ASTnt_root:		return "root";
		case ASTnt_undefined:	return "UNDEFINED";
	}
	return "???";
}

static void _spcs(int n) {
	while (n--) printf(" ");
}

void AST_node::Dump(int level) const {
	_spcs(level); printf("Tip: %s\n", TypeToString(type).c_str());

	if (type == ASTnt_function) {
		_spcs(level); printf("Ime fje: %s\n", function_data.name.c_str());
		//TODO: argumenti fje, tip fje
	}

	if (types.size()) {
		_spcs(level); printf("Definirani tipovi:\n");
		for (vector<c_type>::const_iterator cti = types.begin(); cti != types.end(); ++cti) {
			_spcs(level); printf("+ %s = %s\n", cti->name.c_str(), cti->type.c_str());
		}
	}

	if (declarations.size()) {
		_spcs(level); printf("Deklarirane varijable:\n");
		for (vector<c_decl>::const_iterator cdi = declarations.begin(); cdi != declarations.end(); ++cdi) {
			_spcs(level); printf("+ %s %s = %s\n", cdi->type.c_str(), cdi->name.c_str(), cdi->value.c_str());
		}
	}

	if (type != ASTnt_block) {
		_spcs(level); printf("Blokovi:\n");
		for (vector<AST_node>::const_iterator cai = children.begin(); cai != children.end(); ++cai) {
			cai->Dump(level+1);
		}
	} else {
		_spcs(level); printf("Kod: %s\n", src.c_str());
	}

	printf("\n");
}
