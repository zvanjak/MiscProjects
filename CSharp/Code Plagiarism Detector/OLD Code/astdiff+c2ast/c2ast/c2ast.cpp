#include "stdafx.h"

#include "source.h"
#include "ast.h"
#include "ast2xml.h"

int main(int argc, char *argv[]) {
	string fname, ofname;
	bool dodump = false;
	bool doxml = false;
	source sors;
	AST ast;

	// procesiranje argumenata
	for (int i = 1; i < argc; ++i) {
		if (*argv[i] != '-') {
			fname = argv[i];
			continue;
		}

		switch (argv[i][1]) {
			case 's':
				dodump = true;
				break;

			case 'x':
				doxml = true;
				ofname = argv[i] + 2;
				break;

			default:
				fprintf(stderr, "Nepoznat argument: %c\n", argv[i][1]);
				return 1;
		}
	}

	if (fname.empty()) {
		fprintf(stderr, "Prazan filename!\n");
		return 1;
	}

	try {

		// ucita source
		sors.Load(fname);

		// koverta sors u AST
		ast = sors;

		if (dodump) ast.Dump();
		if (doxml && !WriteStringToFile(ofname, ast2xml(ast))) {
			throw "Ne mogu spremit XML";
		}

	} catch (const string &err_str) {
		fprintf(stderr, "Greska: %s!\n", err_str.c_str());
		if (!sors.Processed()) sors.DumpCodePos(stderr);
		return 1;
	} catch (const char *err_cstr) {
		fprintf(stderr, "Greska: %s!\n", err_cstr);
		if (!sors.Processed()) sors.DumpCodePos(stderr);
		return 1;
	} catch (const SyntaxError &synerr) {
		fprintf(stderr, "Syntax error: %s!\n", synerr.error.c_str());
		synerr.position.Dump(stderr);
		return 1;
	} catch (...) {
		fprintf(stderr, "Unknown error!\n");
		return 1;
	}

	return 0;
}
