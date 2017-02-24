#include "stdafx.h"
#include "ast.h"

#define _spcs(x) PutSpaces(x)

/********************
 *  AST             *
 ********************/
AST::AST() {
	root.type = ASTnt_root;
}

void AST::Dump() const {
	Dump(root);
}

void AST::Dump(const AST_snode &root) {
	root.Dump(0);
}

/* procesiranje typedef-ova */
bool AST::ProcessTypes(AST_anode &parent, source &src) {
	bool ok = false;

	while (src.GetNextPToken() == "typedef") {
		c_type ct;

		if (!GetTypeString(parent, src, ct.type)) {
			src.ThrowSyntaxError("Expecting type after typedef");
			return false;
		}

		if (int n = src.PointerCount()) {
			while (n--) ct.type += '*';
		}

		ct.name = src.GetNextPToken();
		if (ct.name == ";") {
			src.ThrowSyntaxError("Expecting type name");
			return false;
		}

		while (src.GetNextPToken() == "[") {
			string addt;
			src.UnGetPToken();
			GetArrayString(src, addt);
			ct.type+=addt;
		}
		
		if (src.GetCurPToken() != ";") {
			src.ThrowSyntaxError("Expecting ;");
			return false;
		}

		parent.AddType(ct);

		ok = true;
	}

	src.UnGetPToken();

	return ok;
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

bool AST::GetTypeString(AST_ncore &parent, source &src, string &typestring) {
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

bool AST::ProcessDeclarations(AST_ncore &parent, source &src, bool single, bool force) {
	bool ima = false;

	do {
		strpos p = src.GetPos();
		string type, tarr;

		c_decl decl;

		if (!GetTypeString(parent, src, type)) {
			if (force) type = "int";	// ako je beztipna deklaracija u rutu, defaultira na int
			else return ima;
		}

		bool biozarez = false;
		do {
			decl.type = type;
			if (int n = src.PointerCount()) {
				while (n--) decl.type += '*';
			}

			decl.name = src.GetNextPToken();

			if (decl.name == ";") {	// bezimena varijabla - pali za struct, union i enum
				if (biozarez)
					src.ThrowSyntaxError("Expecting variable name");
				break;
			}

			GetArrayString(src, tarr);
			decl.type += tarr;

			if (src.GetNextPToken() == "=") {
				decl.value = src.CollectBlockOrExpression(',');
				if (src.GetCurPToken() == "}") src.GetNextPToken();
			} else {
				decl.value.clear();
			}

			// Provjera da li je mozda fja?
			if (src.GetCurPToken() == "(") {
				src.SetPos(p);
				return ima;
			}

			ima = true;
			parent.AddDeclaration(decl);

			biozarez = true;
		} while (!single && src.GetCurPToken() == ",");

		if (!single && src.GetCurPToken() != ";")
			src.ThrowSyntaxError("Expecting ';'");
	} while (!single);

	src.UnGetPToken();

	return ima;
}

void AST::ProcessLabel(AST_anode &parent, source &src) {
	strpos p = src.GetPos();
	string pt, name;

	pt = src.GetNextPToken();

	// ako prvoskupljeno nije nesto sto lici na label, mora van!
	if (pt.empty() || !source::islblchar(pt[0])) {
		src.UnGetPToken();
		return;
	}

	if (pt == "case") {				// case
		if (parent.type != ASTnt_switch)
			src.ThrowSyntaxError("\"case\" outside \"switch\"");

		name = "case$" + src.CollectExpression(':');
		if (src.GetCurPToken() != ":")
			src.ThrowSyntaxError("Expecting ':' after \"case...\"");
	} else if (pt == "default") {			// default
		if (parent.type != ASTnt_switch)
			src.ThrowSyntaxError("\"default\" outside \"switch\"");

		name = "default";
		if (src.GetNextPToken() != ":")
			src.ThrowSyntaxError("Expecting ':' after \"default\"");
	} else if (src.GetNextPToken() == ":") {	// obican label
		name = pt;
	} else {					// nista
		src.SetPos(p);
		return;
	}

	AST_anode &lbl = parent.AddNode(ASTnt_label);
	lbl.function_data.name = name;
}

void AST::ProcessSwitch(AST_anode &parent, source &src) {
	string pt;

	// skupi uvjet
	if (src.GetNextPToken() != "(")
		src.ThrowSyntaxError("Expecting '(' after \"switch\"");
	parent.src = src.CollectExpression();
	if (src.GetCurPToken() != ")")
		src.ThrowSyntaxError("Expecting ')' after \"switch (...\"");

	ProcessBlock(parent, src);
}

// ako je prvi ptoken == "{", onda ide do "}", inace ide samo do ";"
void AST::ProcessBlock(AST_anode &parent, source &src) {
	// da li pocinje sa { ?
	bool multiline = src.GetNextPToken() == "{";
	if (!multiline) src.UnGetPToken();

	// prvo pokupi tajpdefe i varijable
	if (multiline)
		while (ProcessTypes(parent, src) || ProcessDeclarations(parent, src));

	// A zatim pokupi kôd
	// (Skuplja kôd ptoken po ptoken dok ne naleti na nekaj posebno...)

	string pt;

	do {
		// pogleda ima li labelu:
		ProcessLabel(parent, src);

		// pogleda koji je slijedeci ptoken
		pt = src.GetNextPToken();

		// da li je neki poseban, tj. kada se ne dodaje kao dijete
		if (pt == "}") {
			break;
		} else if (pt == "typedef") {
			src.UnGetPToken();
			ProcessTypes(parent, src);
			continue;	// preskoci dodavanje
		}

		// doda novi nod (gore je osigurano da ce sigurno trebati)
		AST_anode &nod = parent.AddNode();

		if (pt == "{") {
			src.UnGetPToken();
			nod.type = ASTnt_function_code;
			ProcessBlock(nod, src);
		} else if (pt == "if" || pt == "while") {
			if (src.GetNextPToken() != "(")
				src.ThrowSyntaxError("missing '('");
			nod.src = src.CollectExpression();
			if (src.GetCurPToken() != ")")
				src.ThrowSyntaxError("missing ')'");
			
			if (pt == "if") {
				nod.type = ASTnt_if;

				AST_anode &ifnod = nod.AddNode(ASTnt_if_true);
				
				ProcessBlock(ifnod, src);

				if (src.GetNextPToken() == "else") {
					AST_anode &elsenode = nod.AddNode(ASTnt_if_false);
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
			if (src.GetNextPToken() != "(")
				src.ThrowSyntaxError("missing '('");
			forstuff = src.CollectExpression();
			if (src.GetCurPToken() != ";")
				src.ThrowSyntaxError("Missing second part of \"for\"");
			forstuff += ' ' + src.CollectExpression();
			if (src.GetCurPToken() != ";")
				src.ThrowSyntaxError("Missing third part of \"for\"");
			forstuff += ' ' + src.CollectExpression();
			if (src.GetCurPToken() != ")")
				src.ThrowSyntaxError("missing ')'");

			nod.type = ASTnt_for;
			nod.src = forstuff;
			ProcessBlock(nod, src);
		} else if (pt == "do") {
			nod.type = ASTnt_do;
			ProcessBlock(nod, src);
			if (src.GetNextPToken() != "while")
				src.ThrowSyntaxError("Invalid use of \"do\"");
			if (src.GetNextPToken() != "(")
				src.ThrowSyntaxError("missing '('");
			nod.src = src.CollectExpression();
			if (src.GetCurPToken() != ")")
				src.ThrowSyntaxError("missing ')'");
			if (src.GetNextPToken() != ";")
				src.ThrowSyntaxError("Expecting ';' after \"do\"'s \"while\"");
		} else if (pt == "switch") {
			nod.type = ASTnt_switch;
			ProcessSwitch(nod, src);
		} else {
			nod.type = ASTnt_block;

			if (parent.IsType(src.GetCurPToken()))
				src.ThrowSyntaxError("Declaration in code");

			src.UnGetPToken();

			nod.src = src.CollectExpression();
			if (src.GetCurPToken() != ";")
				src.ThrowSyntaxError("Expecting ';' after expression");
		}
	} while (multiline);
}

/* globalne varijable, funkcije */
bool AST::ProcessRootCode(AST_anode &root, source &src) {

	if (ProcessTypes(root, src)) return true;

	if (ProcessDeclarations(root, src, false, true)) return true;

	strpos p;
	AST_ncore fja(ASTnt_function, &root);
	string args_s, t;

	p = src.GetPos();	// da se moze vratiti ako nekaj ne stima

	/* princip skupljanja fje:
		* pokupi tip
		* pokupi ime
		* provjeri (
		* sakupljanje argumenata
		* nadji {
	*/

	// skupljanje tipa
	if (!GetTypeString(root, src, fja.function_data.type)) {
		// ako nema tipa, po defaultu je int
		fja.function_data.type = "int";
	}

	// skupljanje imena
	fja.function_data.name = src.GetNextPToken();

	// provjera (
	if (src.GetNextPToken() != "(") {	// nema ( iza imena fje, dakle, nije fja
		src.SetPos(p);
		goto notfunc;
	}

	// sakupljanje argumenata
	do {
		if (src.GetNextPToken() == "...") {	// ignor argumenta "..."
			if (src.GetNextPToken() != ")")
				src.ThrowSyntaxError("Expecting ')' after '...'");
			break;
		}
		src.UnGetPToken();
		if (!ProcessDeclarations(fja, src, true)) {
			src.GetNextPToken();
			break;
		}
	} while (src.GetNextPToken() == ",");

	if (src.GetCurPToken() != ")")
		src.ThrowSyntaxError("Expecting ')'");

	// trazenje {
	if (src.GetNextPToken() != "{") {
		// TODO: predeklaracija fje moze biti bilo gdje
		if (src.GetCurPToken() == ";")
			src.ThrowSyntaxError("Nepodrzane predeklaracije funkcija");
		src.ThrowSyntaxError("in function declaration");
		goto notfunc;
	}

	////////// Proces fje
	{

	src.UnGetPToken();	// vrati {

	// da li je vec ima?
	if (FindFunction(root, fja.function_data.name, NULL)) {
		throw "Function \"" + fja.function_data.name + "\" already defined";
	}

	AST_anode &afja = root.AddNode(fja);	// doda fju u root
	AST_anode &fcode = afja.AddNode(ASTnt_function_code);
	ProcessBlock(fcode, src);

	return true;

	}

notfunc:
	return false;
}

/* procesiranje root dijela koda */
void AST::ProcessRootBlock(AST_anode &root, source &src) {
	while (!src.Processed()) {
		if (!ProcessRootCode(root, src))
			src.ThrowSyntaxError("in root code");
	}
}

const AST& AST::operator = (source &src) {
	root.Clear();
	ProcessRootBlock(root, src);
	return *this;
}

void AST::FillCustomAST(AST_anode &root, source &src) {
	root.Clear();
	root.type = ASTnt_root;
	ProcessRootBlock(root, src);
}

bool AST::FindFunction(const AST_anode &root, const string &name, unsigned int *pos) {
	if (root.type != ASTnt_root) throw "AST root expected in FindFunction";

	for (unsigned int i=0; i < root.GetNKids(); ++i) {
		if (root[i].type == ASTnt_function &&	/* root bi se trebao sastojati samo od ASTnt_function, ali sigurnosti radi... */
		    root[i].function_data.name == name) {
			if (pos) *pos = i;
			return true;
		}
	}
	
	if (pos) *pos = -1U;
	return false;
}


/********************
 *  AST_ncore       *
 ********************/
AST_ncore::AST_ncore(AST_node_type _type, AST_ncore *_parent) {
	parent = _parent;
	type = _type;
}

void AST_ncore::Clear() {
	types.clear();
	declarations.clear();
}

void AST_ncore::ThrowError(const string &str) const {
	throw str;
}

bool AST_ncore::IsType(const string &sfc) {
	if (source::IsDefaultType(sfc)) return true;

	FOREACHASTCCTYPE(*this, i)
		if (i->name == sfc) return true;

	if (parent) return parent->IsType(sfc);
	return false;
}

void AST_ncore::AddType(const c_type &ct) {
	types.push_back(ct);
}

void AST_ncore::AddDeclaration(const c_decl &cd) {
	// provjera da li vec neka postoji:
	FOREACHASTCCDECL(*this, i) {
		if (i->name == cd.name) {
			string err;
			err = "Varijabla \"" + i->name + "\" ";
			if (i->type == cd.type) err += "(istog tipa)";
			else err += "(razlicitog tipa)";
			err += " vec postoji u " + GetNodePath();
			ThrowError(err);
		}
	}

	// doda deklaraciju
	declarations.push_back(cd);
}

string AST_ncore::TypeToString(AST_node_type type) {
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
		case ASTnt_switch:		return "switch";
		case ASTnt_label:		return "label";
		case ASTnt_undefined:	return "UNDEFINED";
	}
	return "???";
}

void AST_ncore::Dump(int level) const {
	_spcs(level); printf("Tip: %s\n", TypeToString(type).c_str());

	if (type == ASTnt_function) {
		_spcs(level);
		printf("Ime fje: %s\n", function_data.name.c_str());
		_spcs(level);
		printf("Vraca: %s\n", function_data.type.c_str());
	}

	if (types.size()) {
		_spcs(level); printf("Definirani tipovi:\n");
		FOREACHASTCCTYPE(*this, cti) {
			_spcs(level); printf("+ %s = %s\n", cti->name.c_str(), cti->type.c_str());
		}
	}

	if (declarations.size()) {
		if (type != ASTnt_function) {
			_spcs(level); printf("Deklarirane varijable:\n");
		} else {
			_spcs(level); printf("Argumenti:\n");
		}
		FOREACHASTCCDECL(*this, cdi) {
			_spcs(level); printf("+ %s %s", cdi->type.c_str(), cdi->name.c_str());
			if (cdi->value.size())
				printf(" = %s", cdi->value.c_str());
			printf("\n");
		}
	}
}

string AST_ncore::GetNodePath() const {
	string name;

	if (type == ASTnt_function) name = function_data.name;
	else name = TypeToString(type);

	if (parent) return parent->GetNodePath() + "->" + name;
	return name;
}


/********************
 *  AST_anode       *
 ********************/
AST_anode& AST_anode::AddNode(AST_node_type t) {
	return AddNode(AST_ncore(t, this));
}

void AST_anode::Clear() {
	ClearChildren();
	AST_ncore::Clear();
}

void AST_anode::Dump(int level) const {
	AST_ncore::Dump(level);

	if (type != ASTnt_block) {
		_spcs(level); printf("Blokovi (%u):\n", GetNKids());
		for (unsigned int cai = 0; cai < GetNKids(); ++cai) {
			(*this)[cai].Dump(level+1);
		}
	} else {
		_spcs(level); printf("Kod: %s\n", src.c_str());
	}

	printf("\n");
}

