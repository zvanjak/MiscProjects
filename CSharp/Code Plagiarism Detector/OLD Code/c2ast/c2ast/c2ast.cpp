#include "stdafx.h"

#include "source.h"
#include "ast.h"
#include "ast2xml.h"

int main(int argc, char *argv[]) {
	source sors;
	AST ast;
	string fname, ofname;
	bool dodump = false;
	bool doxml = false;

	// procesiranje argumenata
	for (int i = 0; i < argc; ++i) {
		if (*argv[i] == '-') {
			switch (argv[i][1]) {
				case 's':
					dodump = true;
					break;

				case 'x':
					doxml = true;
					ofname = argv[i] + 2;
					break;

				default:
					printf("Nepoznat argument: %c\n", argv[i][1]);
					return 1;
			}
		} else {
			fname = argv[i];
		}
	}


	try {

		sors.Load(fname);

		ast = sors;

		if (dodump) ast.Dump();
		if (doxml) {
			if (!WriteStringToFile(ofname, ast2xml(ast))) {
				printf("Ne mogu spremit XML!\n");
				return 1;
			}
		}

	} catch (const string &err_str) {
		printf("Greska: %s\n", err_str.c_str());
		return 1;
	} catch (const char *err_cstr) {
		printf("Greska: %s\n", err_cstr);
		return 1;
	}

	return 0;
}
