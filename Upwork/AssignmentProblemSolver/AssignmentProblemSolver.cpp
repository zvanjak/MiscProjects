// AssignmentProblemSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>


int main()
{
	FILE *fp;
	fopen_s(&fp, "Data/Projects.csv", "r");
	char buff[501];
	char project[50];

	int line = 0;
	while(fgets(buff, 500, fp) )
	{
	//	printf("%s", buff);

		if( line > 1 )		// first two lines are header related
		{
			sscanf_s(buff, "%[^,]s", project, 50);
			printf("%s\n", project);
		}

		++line;
	}
    return 0;
}

