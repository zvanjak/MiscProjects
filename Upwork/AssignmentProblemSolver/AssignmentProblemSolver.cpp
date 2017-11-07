// AssignmentProblemSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>

class Project
{
public:
	std::string _name;
	std::string _priority;
	std::string _role;
	int			_level;
	int			_weekTime[66];
};

int main()
{
	std::vector<Project> _listProjects;

	std::ifstream inFile("Projects.csv");
	if (!inFile.bad())
	{
		std::vector<std::string>   result;
		std::string                line;

		std::stringstream          lineStream;
		std::string                cell;

		// reading first two lines with headers
		std::getline(inFile, line);
		std::getline(inFile, line);

		while (std::getline(inFile, line))
		{
			int		tokenCount = 0;
			Project	newProject;

			std::istringstream iss(line);
			std::string token;
			while (std::getline(iss, token, ','))
			{
				switch (tokenCount)
				{
				case 0: newProject._name = token; break;
				case 1: newProject._priority = token; break;
				case 2: newProject._role = token; break;
				case 3: newProject._level = atoi(token.c_str()); break;
				default:
					int weekNum = tokenCount - 4;
					newProject._weekTime[weekNum] = atoi(token.c_str());
					break;
				}

				tokenCount++;
			}
			_listProjects.push_back(newProject);
		}

		for (auto p = begin(_listProjects); p != end(_listProjects); p++)
		{
			std::cout << p->_name << " " << p->_role << std::endl;
		}
	}

	return 0;
}

