// JIRAAnalysis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;

class Issue
{
public:
	Issue(vector<string> inVec, vector<string> &inHeader) : vecHeader(inHeader)
	{
		vecValues = inVec;
	}

public:
	vector<string> vecValues;
	vector<string> &vecHeader;
};

class DevStat
{
public:
	string _name;
	map<string, int> _mapStatusCount;

	int _timeSpent;
	int _issuesWithTime;

	int _storyPoints;
	int _issuesWithStoryPoints;
};

void printToScreen(vector<DevStat> &vecStats, vector<string> &types);
void printToFile(vector<DevStat> &vecStats, vector<string> &types);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void processHeader(const std::string &s, vector<string> &outHeader)
{
	split(s, ';', outHeader);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream inputFile;
	inputFile.open("D:\\erecruit\\Issues.csv", ios::in);

	vector<string> vecHeader;
	vector<Issue> vecIssues;

	string line;
	int cnt = 0;
	if (inputFile.is_open())
	{
		getline(inputFile, line);			// učitavamo prvu liniju s headerom
		processHeader(line, vecHeader);

		while (getline(inputFile, line) )
		{
			vector<string> vecLine;
			split(line, ';', vecLine);

			Issue newIssue(vecLine, vecHeader);
			vecIssues.push_back(newIssue);
			
			vecLine.clear();
			++cnt;
		}
	}
	else
		cout << "Error opening file!";

	vector<string> types{ "Closed", "Resolved Pending QA", "Resolved Pending Verification on Client", "Demo", "Peer Review", "Needs Test Case?", "Needs Scoping", "Needs Documentation?", "Open", "In Progress", "Reopened"  /*,  "Stors Points", "Time Spent"*/ };

	int assigneeIndex		 = std::find(vecHeader.begin(), vecHeader.end(), "Assignee") - begin(vecHeader);
	int statusIndex			 = std::find(vecHeader.begin(), vecHeader.end(), "Status") - begin(vecHeader);
	int timeSpentIndex	 = std::find(vecHeader.begin(), vecHeader.end(), "Time Spent") - begin(vecHeader);
	int storyPointsIndex = std::find(vecHeader.begin(), vecHeader.end(), "Story Points") - begin(vecHeader);

	vector<DevStat> vecStats;
	map<string, int> countIssues;

	for (const Issue &issue : vecIssues)
	{
		string assignee;
		if (issue.vecValues.size() > assigneeIndex)
		{
			assignee = issue.vecValues[assigneeIndex];

			// treba naći odgovarajući DevStat
			auto dev = find_if(begin(vecStats), end(vecStats), [&assignee](DevStat dv) { return dv._name == assignee; });
			if (dev == end(vecStats))
			{
				DevStat newDev;
				newDev._name = assignee;
				vecStats.push_back(newDev);

				dev = vecStats.end() - 1;
			}
			// i povećati mu Count za taj status
			dev->_mapStatusCount[issue.vecValues[statusIndex]]++;

			if (issue.vecValues.size() > timeSpentIndex && issue.vecValues[timeSpentIndex] != "")
			{
				dev->_timeSpent += stoi(issue.vecValues[timeSpentIndex]);
				dev->_issuesWithTime++;
			}

			if (issue.vecValues[storyPointsIndex] != "")
			{
				dev->_storyPoints += stoi(issue.vecValues[storyPointsIndex]);
				dev->_issuesWithStoryPoints++;
			}
		}
		else
			cout << "No assignee!!!" << endl;
	}

	// ajmo sortirati po Closed
	sort(begin(vecStats), end(vecStats), [](DevStat v1, DevStat v2) { return v1._mapStatusCount["Closed"] > v2._mapStatusCount["Closed"]; });
	
	printToScreen(vecStats, types);

	printToFile(vecStats, types);


	return 0;
}

void printToScreen(vector<DevStat> &vecStats, vector<string> &types)
{
	cout << setw(20) << "Developer  ";
	for (const string &s : types)
		cout << setw(15) << s.substr(0, 15) << " ";

	cout << endl;

	for (DevStat &ds : vecStats)
	{
		cout << setw(20) << ds._name;
		for (string s : types)
		{
			cout << setw(15) << ds._mapStatusCount[s] << " ";
		}

		cout << ds._storyPoints << "  " << ds._issuesWithStoryPoints << "  ";
		cout << ds._timeSpent / 3600 << "  " << ds._issuesWithTime;

		cout << endl;
	}
}
void printToFile(vector<DevStat> &vecStats, vector<string> &types)
{
	ofstream outputFile("Analysis.csv", ios::out);

	outputFile << "Developer;";
	for (const string &s : types)
		outputFile << s << ";";

	outputFile << "Story points;Total issues with story points;Time spent;Total issues with time recorded";
	outputFile << endl;

	for (DevStat &ds : vecStats)
	{
		outputFile << ds._name << ";";
		for (string s : types)
		{
			outputFile << ds._mapStatusCount[s] << ";";
		}

		outputFile << ds._storyPoints << ";" << ds._issuesWithStoryPoints << ";";
		outputFile << ds._timeSpent / 3600 << ";" << ds._issuesWithTime;

		outputFile << endl;
	}
}
